cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -fstack-protector -g -fno-omit-frame-pointer -O2 -D_FORTIFY_SOURCE=2")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} O3 -DNDEBUG")
endif()


set(SRC 
  core/core.c
  "linked list/list/list.c"
  "linked list/clist/clist.c"
  "linked list/dlist/dlist.c"
  linear/queue/queue.c
  linear/stack/stack.c
  linear/set/set.c
  hash/hashtable/hashtable.c
  hash/pair/pair.c
  tree/btree/btree.c
  tree/bistree/bistree.c
  tree/heap/heap.c
  graph/graph.c
  graph/graph_traversal.c
  algorithms/sorting.c
  main.c
  )

set(INCLUDE_DIR
  core
  linear/queue
  linear/set
  linear/stack
  "linked list/list"
  "linked list/clist"
  "linked list/dlist"
  hash/hashtable
  tree/bistree
  tree/btree
  tree/heap
  hash/pair
  algorithms
  graph)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE_DIR})

