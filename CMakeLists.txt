cmake_minimum_required(VERSION 3.28.3)
project(DSA)
set(CMAKE_C_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

set(SRC
  main.c
  src/bits.c
  src/matrix.c
  src/funcs.c
  src/linked.c
  src/sorting.c
  src/stack.c
  src/lstack.c
  src/logs.c
  src/queue.c
  src/lqueue.c
  )

set(INCLUDE 
  include
)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE})

add_custom_target(RUN ALL
COMMAND echo
COMMAND "./DSA" 
COMMAND echo)