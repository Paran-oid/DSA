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
  src/stack.c
  src/lstack.c
  src/logs.c
  src/queue.c
  src/lqueue.c
  src/array.c
  src/tree.c
  src/dict.c
  )

set(INCLUDE 
  include
)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE})

# These are really important to be sure that I am writing safe and robust code

target_compile_options(DSA PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  -Werror
  -O2
)

add_custom_target(RUN ALL
COMMAND echo
COMMAND "./DSA" 
COMMAND echo)