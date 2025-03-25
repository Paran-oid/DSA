cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fstack-protector -g -fno-omit-frame-pointer -O2 -D_FORTIFY_SOURCE=2")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} O3 -DNDEBUG")
endif()


set(SRC 
  core/core.c
  list/list.c
  list/dlist.c
  list/clist.c
  linear/queue.c
  linear/stack.c
  linear/set.c
  hash/hashtable.c
  hash/pair.c
  tree/btree.c
  tree/bistree.c
  tree/heap.c
  tree/pqueue.c
  graph/graph.c
  graph/graph_traversal.c
  main.c)

set(INCLUDE_DIR
  core
  linear
  list
  hash
  tree
  graph)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE_DIR})

