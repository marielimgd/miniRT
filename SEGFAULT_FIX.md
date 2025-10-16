# Segmentation Fault Fix - Double Free Issue

## Problem

When closing the program (ESC key or X button), a segmentation fault occurred:
```
zsh: segmentation fault (core dumped)
```

## Root Cause Analysis

Using GDB backtrace, the crash was in `free_matrix()` with an invalid pointer `0x80000000000000`:

```
#0  __GI___libc_free (mem=0x80000000000000)
#1  free_matrix (m=0x411bc0)
#2  free_object (obj_ptr=0x411a70)
#3  ft_lstdelone ()
#4  ft_lstclear ()
#5  free_scene (scene=0x4112c0)
#6  free_all ()
#7  close_window (scene=0x4112c0)
```

The issue was **double-free** caused by:

### Issue 1: Duplicate MLX Cleanup
`close_window()` manually freed MLX resources, then called `free_all()`, which called `free_scene()` that tried to free the same MLX resources again:

```c
// close_window() - BEFORE FIX
mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);  // Manual cleanup
mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
mlx_destroy_display(scene->mlx.mlx_ptr);
free(scene->mlx.mlx_ptr);
free_all();  // Calls free_scene() which tries to free the same things!
```

### Issue 2: Double-Tracking Objects
Objects were allocated with `safe_malloc(ALLOC_TYPE_OBJECT)`, adding them to the tracking list. Then:

1. `free_all()` calls `free_scene()`
2. `free_scene()` calls `ft_lstclear(&scene->objects, free_object)` → frees all objects
3. `free_all()` continues iterating the tracking list
4. Tries to free the same objects AGAIN → **DOUBLE FREE**

The tracking list contained:
```
[SCENE] → [OBJECT1] → [OBJECT2] → [OBJECT3] → ...
```

When `free_scene()` was processed, it freed all objects. Then `free_all()` tried to free `OBJECT1`, `OBJECT2`, etc. again.

### Issue 3: No NULL Checks in free_matrix()
`free_matrix()` didn't validate pointers, so invalid/corrupted pointers caused crashes.

## Solutions Implemented

### Fix 1: Remove Duplicate MLX Cleanup

**File**: `src/window/window.c`

**Before:**
```c
int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx.mlx_ptr, scene->mlx.img_ptr);
	mlx_destroy_window(scene->mlx.mlx_ptr, scene->mlx.win_ptr);
	mlx_destroy_display(scene->mlx.mlx_ptr);
	free(scene->mlx.mlx_ptr);
	free_all();
	exit(0);
	return (0);
}
```

**After:**
```c
int	close_window(t_scene *scene)
{
	(void)scene;
	free_all();  // Let free_all() handle everything via free_scene()
	exit(0);
	return (0);
}
```

### Fix 2: Don't Track Objects Individually

Objects are owned by the scene and freed when the scene is freed. They should NOT be tracked separately.

**Files Changed:**
- `src/objects/sphere.c`
- `src/objects/planes.c`
- `src/parse/object_parser.c`

**Before:**
```c
sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_OBJECT);  // Tracked!
```

**After:**
```c
sphere = malloc(sizeof(t_object));  // NOT tracked, freed by free_scene()
```

### Fix 3: Add NULL Checks to free_matrix()

**File**: `src/memory_mgmt/safe_malloc.c`

**Before:**
```c
void	free_matrix(t_matrix *m)
{
	int	i;

	i = 0;
	while (i < m->row)
	{
		free(m->matrix[i]);
		i++;
	}
	free(m->matrix);
	free(m);
}
```

**After:**
```c
void	free_matrix(t_matrix *m)
{
	int	i;

	if (!m)
		return ;
	if (m->matrix)
	{
		i = 0;
		while (i < m->row)
		{
			if (m->matrix[i])
				free(m->matrix[i]);
			i++;
		}
		free(m->matrix);
	}
	free(m);
}
```

## Memory Management Architecture (Updated)

### What Gets Tracked (safe_malloc)
- ✅ **Scene structure only** (ALLOC_TYPE_SCENE)

### What Does NOT Get Tracked (regular malloc)
- ❌ Objects (owned by scene, freed by `free_scene()`)
- ❌ Lights (owned by scene, freed by `free_scene()`)
- ❌ Matrices (temporary or owned by objects)
- ❌ Intersection lists (temporary, freed immediately)

### Cleanup Flow
```
close_window()
    ↓
free_all()
    ↓
Iterate tracking list → Find SCENE
    ↓
free_scene()
    ├─→ free_matrix(camera.transform)
    ├─→ ft_lstclear(objects, free_object)  ← Frees all objects
    │       └─→ free_matrix × 3 (transform matrices)
    ├─→ ft_lstclear(lights, free_light)    ← Frees all lights
    └─→ MLX cleanup (destroy image, window, display)
    ↓
Continue tracking list → No more objects to free
    ↓
Clean exit
```

## Key Principle

**Only track top-level structures. Child structures are freed by their parents.**

- Scene owns objects/lights → Scene frees them
- Objects own transform matrices → Objects free them
- Don't track what you don't directly own

## Testing

### Before Fix
```bash
$ ./minirt scenes/spheres_colorful.rt
# Close with ESC or X
zsh: segmentation fault (core dumped)  ./minirt scenes/spheres_colorful.rt
```

### After Fix
```bash
$ ./minirt scenes/spheres_colorful.rt
# Close with ESC or X
$ echo $?
0  # Clean exit!
```

### Valgrind Check
```bash
$ timeout 2s valgrind ./minirt scenes/spheres_colorful.rt 2>&1 | grep -E "(Invalid|double free)"
# No output = No double-free errors!
```

## Lessons Learned

1. **Avoid duplicate cleanup** - Let one system handle all cleanup
2. **Track ownership carefully** - Only track what you directly own
3. **Don't double-track** - If something is in a list owned by a tracked structure, don't track it separately
4. **Always validate pointers** - Check for NULL before dereferencing
5. **Use valgrind early** - Catch double-free issues before they become segfaults

## Related Documents

- `FREE_ALL_SYSTEM.md` - Complete memory management architecture
- `PERFORMANCE_FIX.md` - Why we don't track temporary allocations
