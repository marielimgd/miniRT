# Free All System - Implementation Guide

## Overview

The miniRT project implements a comprehensive memory management system using `free_all()` that tracks all allocations and ensures complete cleanup on program exit.

## Architecture

### 1. Allocation Tracking

Every allocation is tracked via a linked list:

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

**Usage:**
```c
t_scene *world = safe_malloc(sizeof(t_scene), ALLOC_TYPE_SCENE);
t_matrix *m = safe_malloc(sizeof(t_matrix), ALLOC_TYPE_MTX);
```

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
    ALLOC_TYPE_GENERIC,   // Use: Intersection lists, temporary data
    ALLOC_TYPE_MTX,       // Use: All matrix structures
    ALLOC_TYPE_STRING,    // Use: Dynamically allocated strings
    ALLOC_TYPE_OBJECT,    // Use: Spheres, planes, cylinders
    ALLOC_TYPE_SCENE,     // Use: Main scene structure
    ALLOC_TYPE_LIGHT      // Use: Light structures
} t_alloc_type;
```

## Runtime vs Exit Cleanup

### Runtime Cleanup (Immediate)
These are freed immediately after use:

**1. Temporary Matrices**
```c
// In keyhooks.c, object_parser.c, camera.c
t_matrix *temp = translation(x, y, z);
// ... use temp ...
free_matrix(temp);  // Freed immediately
```

**2. Intersection Lists**
```c
// In render.c, colors.c, hit.c
intersections = intersect_world(scene, ray);
// ... use intersections ...
free(intersections.intersections);  // Freed immediately
```

**3. Inverse Transform Matrices**
```c
// In camera.c - ray_for_pixel()
inv_transform = inverse_matrix(camera->transform);
// ... use inv_transform ...
free_matrix(inv_transform);  // Freed immediately
```

### Exit Cleanup (via free_all)
These are tracked and freed on program exit:

**1. Scene Structure** (ALLOC_TYPE_SCENE)
- Created in `create_world()`
- Freed via `free_scene()` which handles all sub-structures

**2. Objects** (ALLOC_TYPE_OBJECT)
- Created in `parse_sphere()`, `parse_plane()`, `parse_cylinder()`
- Freed via `free_object()` which handles transform matrices

**3. Lights** (ALLOC_TYPE_LIGHT)
- Created in `parse_light()`
- Freed via `free_light()`

**4. Persistent Matrices** (ALLOC_TYPE_MTX)
- Object transform matrices
- Object inverse matrices
- Camera transform matrix
- Freed via `free_matrix()`

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

## Error Handling

### On Parse Error
```c
void parse_error(int line, char *msg)
{
    // Print error message
    free_all();  // Clean up all allocations
    exit(1);
}
```

### On Runtime Error
```c
void print_error(char *msg)
{
    // Print error message
    free_all();  // Clean up all allocations
    exit(1);
}
```

### On Normal Exit
```c
int main(int argc, char **argv)
{
    // ... program logic ...
    free_all();  // Clean up before exit
    return (0);
}
```

## Memory Leak Testing

### Run Valgrind
```bash
# Quick 2-second test
make valgrind-quick SCENE=scenes/your_scene.rt

# Full test with log file
make valgrind SCENE=scenes/your_scene.rt
cat valgrind-out.txt
```
