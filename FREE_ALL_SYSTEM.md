# Free All System - Implementation Guide

## Overview

The miniRT project implements a comprehensive memory management system using `free_all()` that tracks all allocations and ensures complete cleanup on program exit.

## Architecture

### 1. Allocation Tracking

Only **persistent** allocations are tracked via a linked list:

```c
typedef struct s_allocation
{
    t_alloc_type         type;      // Type of allocation
    void                 *ptr;      // Pointer to allocated memory
    struct s_allocation  *next;     // Next allocation in list
} t_allocation;
```

### 2. Safe Malloc Function

```c
void *safe_malloc(size_t size, t_alloc_type type)
```

**What it does:**
- Allocates memory of the requested size
- Creates an allocation tracking node
- Adds to the head of the allocation list
- Returns the allocated pointer

**Usage (for persistent allocations only):**
```c
t_scene *world = safe_malloc(sizeof(t_scene), ALLOC_TYPE_SCENE);
t_object *sphere = safe_malloc(sizeof(t_object), ALLOC_TYPE_OBJECT);
t_light *light = safe_malloc(sizeof(t_light), ALLOC_TYPE_LIGHT);
```

**IMPORTANT:** Do NOT use `safe_malloc()` for temporary allocations that are freed during runtime (matrices, intersection lists, etc.). Use regular `malloc()` for those.

### 3. Free All Function

```c
void free_all(void)
```

**What it does:**
- Iterates through all tracked allocations
- Calls appropriate free function based on type
- Clears the allocation list

**Call Order:**
1. Called from `main()` before exit
2. Called from `parse_error()` on errors
3. Called from `print_error()` on critical errors

## Free Functions

### free_matrix()
```c
void free_matrix(t_matrix *m)
```
- Frees each row array
- Frees the matrix array
- Frees the matrix structure

**Used for:**
- Transform matrices
- Inverse transform matrices
- Transpose inverse matrices

### free_object()
```c
void free_object(void *obj_ptr)
```
- Frees object's transform matrix
- Frees object's inverse_transform matrix  
- Frees object's transpose_inverse_transform matrix
- Frees the object structure

**Used for:**
- Spheres
- Planes
- Cylinders

### free_light()
```c
void free_light(void *light_ptr)
```
- Simple free (lights have no sub-allocations)

**Used for:**
- Point lights

### free_scene()
```c
void free_scene(t_scene *scene)
```
- Frees camera transform matrix
- Clears lights list with `ft_lstclear(..., free_light)`
- Clears objects list with `ft_lstclear(..., free_object)`
- Destroys MLX image
- Destroys MLX window
- Destroys MLX display
- Frees MLX pointer
- Frees scene structure

**Used for:**
- Main scene structure

## Allocation Types

```c
typedef enum e_alloc_type
{
    ALLOC_TYPE_GENERIC,   // Use: Persistent generic data (rarely used)
    ALLOC_TYPE_MTX,       // DEPRECATED: Matrices now use malloc()
    ALLOC_TYPE_STRING,    // Use: Persistent strings (if needed)
    ALLOC_TYPE_OBJECT,    // Use: Spheres, planes, cylinders (tracked)
    ALLOC_TYPE_SCENE,     // Use: Main scene structure (tracked)
    ALLOC_TYPE_LIGHT      // Use: Light structures (tracked)
} t_alloc_type;
```

**Note:** Most temporary allocations (matrices, intersection lists) are NOT tracked and use regular `malloc()` for performance.

## Runtime vs Exit Cleanup

### Runtime Cleanup (Immediate - NOT tracked)
These are allocated with regular `malloc()` and freed immediately after use:

**1. Temporary Matrices**
```c
// In keyhooks.c, object_parser.c, camera.c
// Allocated with malloc() via create_matrix()
t_matrix *temp = translation(x, y, z);
// ... use temp ...
free_matrix(temp);  // Freed immediately - NOT tracked
```

**2. Intersection Lists**
```c
// In render.c, colors.c, hit.c
// Allocated with malloc() directly
intersections = intersect_world(scene, ray);
// ... use intersections ...
free(intersections.intersections);  // Freed immediately - NOT tracked
```

**3. All Matrix Operations**
```c
// In camera.c - ray_for_pixel()
// Allocated with malloc() via inverse_matrix()
inv_transform = inverse_matrix(camera->transform);
// ... use inv_transform ...
free_matrix(inv_transform);  // Freed immediately - NOT tracked
```

**Why NOT tracked?**
These allocations happen thousands of times per frame. Tracking them would:
- Slow down the program significantly
- Grow the allocation list infinitely
- Risk double-free when free_all() is called
- Waste memory on tracking nodes

### Exit Cleanup (via free_all - TRACKED)
These are allocated with `safe_malloc()` and tracked for cleanup on exit:

**1. Scene Structure** (ALLOC_TYPE_SCENE)
- Created in `create_world()` with `safe_malloc()`
- Freed via `free_scene()` which handles all sub-structures
- Sub-structures (camera transform, MLX) are freed within `free_scene()`

**2. Objects** (ALLOC_TYPE_OBJECT)
- Created in `parse_sphere()`, `parse_plane()`, `parse_cylinder()` with `safe_malloc()`
- Freed via `free_object()` which handles transform matrices
- Transform matrices are allocated with `malloc()` (NOT tracked individually)

**3. Lights** (ALLOC_TYPE_LIGHT)
- Created in `parse_light()` with `safe_malloc()`
- Freed via `free_light()`

**Why tracked?**
These are persistent allocations that exist for the lifetime of the program:
- Created once during initialization
- Used throughout the program
- Only freed on exit or error

## Code Flow

```
Program Start
    ↓
create_world() → safe_malloc(ALLOC_TYPE_SCENE)
    ↓
parse_scene()
    ├─→ parse_sphere() → safe_malloc(ALLOC_TYPE_OBJECT)
    │       └─→ set_transform() → safe_malloc(ALLOC_TYPE_MTX)
    ├─→ parse_light() → safe_malloc(ALLOC_TYPE_LIGHT)
    └─→ parse_camera() → view_transform() → safe_malloc(ALLOC_TYPE_MTX)
    ↓
render_scene()
    └─→ process_pixel()
        ├─→ intersect_world() → malloc() [NOT tracked, freed immediately]
        └─→ free(intersections.intersections) [Immediate cleanup]
    ↓
Program Exit / Error
    ↓
free_all()
    ├─→ free_scene()
    │   ├─→ free_matrix(camera.transform)
    │   ├─→ ft_lstclear(lights, free_light)
    │   ├─→ ft_lstclear(objects, free_object)
    │   │       └─→ free_matrix(transform, inverse, transpose)
    │   └─→ MLX cleanup
    └─→ Clear allocation list
```
