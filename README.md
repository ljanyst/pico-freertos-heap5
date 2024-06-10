
pico-freertos-heap5
===================

The code in this repository wraps the `malloc`, `calloc`, `realloc`, and `free`
calls and redirects them to their FreeRTOS counterparts. The `_sbrk` symbol that
is used by the default newlib allocator is redefined to panic. This is to make
sure that the system is not using two competing heap managers. The heap
boundaries are set on first use by calling `vPortDefineHeapRegions` with the
values computed by the linker such that the entire free RAM is used.

Usage
-----

In your master `CMakeLists.txt` disable the default pico malloc by placing the
following declaration before the call to `pico_sdk_init`:

```cmake
set(SKIP_PICO_MALLOC 1)
```

Make sure to set the FreeRTOS allocator to `heap5`:

```cmake
set(FREERTOS_HEAP 5)
```

Point to the source, ie.:

```cmake
add_subdirectory(lib/pico-freertos-heap5/src)
```

And link your final binary with the `pico_freertos_heap5` lib.
