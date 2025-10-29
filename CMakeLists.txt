
project(corkel)
add_library(corkel STATIC source/lib/mman.c source/lib/setjmp.c source/dlmalloc/src/dlmalloc.c source/lib/setjmp_core_${CMAKE_SYSTEM_PROCESSOR}.S)
target_include_directories(corkel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/include)
            