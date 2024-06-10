
pico_add_library(pico_freertos_heap5)

target_sources(
  pico_freertos_heap5
  INTERFACE
  memory.c
)

pico_wrap_function(pico_freertos_heap5 malloc)
pico_wrap_function(pico_freertos_heap5 calloc)
pico_wrap_function(pico_freertos_heap5 realloc)
pico_wrap_function(pico_freertos_heap5 free)
