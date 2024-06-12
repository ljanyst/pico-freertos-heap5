// Copyright 2024 Lukasz Janyst <lukasz@jany.st>
// Licensed under the MIT license, see the LICENSE file for details.

#include <stddef.h>
#include <stdint.h>

typedef struct HeapRegion {
    uint8_t *pucStartAddress;
    size_t xSizeInBytes;
} HeapRegion_t;

#define portPOINTER_SIZE_TYPE uint32_t

extern void vPortDefineHeapRegions(const HeapRegion_t *const pxHeapRegions);
extern void *pvPortMalloc(size_t xWantedSize);
extern void *pvPortCalloc(size_t xNum, size_t xSize);
extern void vPortFree(void *pv);
extern void panic(const char *msg);

static HeapRegion_t heap_regions[] = { { NULL, 0 }, { NULL, 0 } };

void freertos_init_heap5()
{
    // Set by linker
    extern uint8_t __StackLimit;
    extern uint8_t end;

    heap_regions[0].pucStartAddress = &end;
    heap_regions[0].xSizeInBytes = &__StackLimit - &end;

    vPortDefineHeapRegions(heap_regions);
}

void vApplicationGetRandomHeapCanary(portPOINTER_SIZE_TYPE *pxHeapCanary)
{
    if (pxHeapCanary != NULL) {
        *pxHeapCanary = 0xb293f121;
    }
}

void *_sbrk(int incr)
{
    panic("sbrk should not be called with heap5 memory");
    return NULL;
}

void *__wrap_malloc(size_t size)
{
    if (heap_regions[0].pucStartAddress == NULL) {
        freertos_init_heap5();
    }

    return pvPortMalloc(size);
}

void *__wrap_calloc(size_t count, size_t size)
{
    if (heap_regions[0].pucStartAddress == NULL) {
        freertos_init_heap5();
    }

    return pvPortCalloc(count, size);
}

void *__wrap_realloc(void *mem, size_t size)
{
    if (heap_regions[0].pucStartAddress == NULL) {
        freertos_init_heap5();
    }

    vPortFree(mem);
    return pvPortMalloc(size);
}

void __wrap_free(void *mem)
{
    vPortFree(mem);
}
