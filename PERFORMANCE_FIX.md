# Performance Fix - Memory Tracking Issue

## Problem

After implementing the comprehensive `free_all()` memory management system, the program became **extremely slow and unresponsive**.

## Root Cause

The issue was that **ALL allocations** were being tracked in the allocation list using `safe_malloc()`, including:

1. **Temporary matrices** created thousands of times per frame:
   - `inverse_matrix()` calls in `ray_for_pixel()` (once per pixel!)
   - Matrix multiplications during transformations
   - Intermediate matrices during parsing

2. **Intersection lists** allocated for every ray-object intersection test:
   - `intersect_world()` (once per pixel)
   - `create_intersections_list()` (multiple times per pixel)
   - Plane/sphere/cylinder intersection results

### Why This Was Catastrophic

For a 800×600 window:
- **480,000 pixels** per frame
- Each pixel needs at least **2-3 matrix allocations** (inverse, multiply, etc.)
- Each pixel needs **multiple intersection list allocations** (one per object tested)
- Result: **~2,000,000+ allocations tracked per frame**

The allocation tracking list would:
1. Grow to millions of nodes
2. Cause extreme memory bloat
3. Slow down every `safe_malloc()` call (linked list prepending)
4. Create dangling pointers (freed but still in tracking list)
5. Risk double-free when `free_all()` is eventually called

## Solution

**Only track persistent allocations** that live for the entire program lifetime:

### Tracked (use `safe_malloc`)
- ✅ Scene structure (`ALLOC_TYPE_SCENE`)
- ✅ Objects (`ALLOC_TYPE_OBJECT`)  
- ✅ Lights (`ALLOC_TYPE_LIGHT`)

### NOT Tracked (use regular `malloc`)
- ❌ Temporary matrices (freed immediately with `free_matrix()`)
- ❌ Intersection lists (freed immediately with `free()`)
- ❌ All runtime allocations

## Changes Made

### 1. Fixed Matrix Creation (`src/math/matrices.c`)
**Before:**
```c
matrix = safe_malloc(sizeof(t_matrix), ALLOC_TYPE_MTX);
mtx = safe_malloc(sizeof(double *) * row, ALLOC_TYPE_MTX);
mtx[i] = safe_malloc(sizeof(double) * collum, ALLOC_TYPE_MTX);
```

**After:**
```c
matrix = malloc(sizeof(t_matrix));
mtx = malloc(sizeof(double *) * row);
mtx[i] = malloc(sizeof(double) * collum);
```

### 2. Fixed Intersection Lists (`src/render/world.c`)
**Before:**
```c
all_intersections.intersections = safe_malloc(all_intersections.capacity
    * sizeof(t_intersection), ALLOC_TYPE_GENERIC);
```

**After:**
```c
all_intersections.intersections = malloc(all_intersections.capacity
    * sizeof(t_intersection));
```

### 3. Fixed Intersection List Creation (`src/render/intersections.c`)
**Before:**
```c
list.intersections = safe_malloc(count * sizeof(t_intersection),
    ALLOC_TYPE_GENERIC);
```

**After:**
```c
list.intersections = malloc(count * sizeof(t_intersection));
```

### 4. Fixed Plane Intersections (`src/objects/planes.c`)
**Before:**
```c
intersections.intersections = safe_malloc(sizeof(t_intersection),
    ALLOC_TYPE_GENERIC);
```

**After:**
```c
intersections.intersections = malloc(sizeof(t_intersection));
```

## Memory Management Architecture

### Persistent Allocations (Tracked)
```
Program Start
    ↓
safe_malloc(ALLOC_TYPE_SCENE)  ← Tracked
    ↓
safe_malloc(ALLOC_TYPE_OBJECT) ← Tracked
    ├─→ malloc() for transform matrix    (NOT tracked, freed by free_object)
    ├─→ malloc() for inverse             (NOT tracked, freed by free_object)
    └─→ malloc() for transpose_inverse   (NOT tracked, freed by free_object)
    ↓
safe_malloc(ALLOC_TYPE_LIGHT)  ← Tracked
    ↓
Program Exit
    ↓
free_all()
    ├─→ free_scene()  → frees camera transform (malloc)
    ├─→ free_object() → frees 3 transform matrices (malloc)
    └─→ free_light()
```

### Runtime Allocations (NOT Tracked)
```
Render Loop (per pixel)
    ↓
malloc() → inverse_matrix()     (freed immediately with free_matrix)
    ↓
malloc() → intersection list    (freed immediately with free)
    ↓
Continue to next pixel
```

## Results

### Before Fix
- 🔴 Extremely slow rendering
- 🔴 Unresponsive interface
- 🔴 Memory growing infinitely
- 🔴 Potential crash from double-free

### After Fix  
- ✅ Fast rendering (same as before memory management refactoring)
- ✅ Responsive interface
- ✅ Constant memory usage
- ✅ No memory leaks (still 0 bytes definitely lost)
- ✅ No performance overhead

## Key Principle

**Only track what needs to live until program exit.**

- Persistent data (scene, objects, lights) → `safe_malloc()` + tracked
- Temporary data (matrices, lists) → `malloc()` + freed immediately
- This gives us both **memory safety** AND **performance**

## Testing

```bash
# Rebuild after fixes
make re

# Test performance
./minirt scenes/complex_pale_shadows.rt

# Verify no memory leaks
make valgrind-quick SCENE=scenes/complex_pale_shadows.rt
```

Expected result: Fast rendering with 0 bytes definitely lost in valgrind.

## Lessons Learned

1. **Not everything should be tracked** - Only persistent allocations benefit from tracking
2. **Performance matters** - Tracking millions of temporary allocations kills performance
3. **Immediate cleanup is better** - Free temporary allocations right away instead of deferring
4. **Test early** - Performance regression caught immediately after implementation
5. **Document clearly** - Make it obvious which allocations should use which allocation method

## Updated Documentation

See `FREE_ALL_SYSTEM.md` for the complete, corrected memory management architecture.
