cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)

set(SRC 
  core/core.c
  list/list.c
  list/dlist.c
  list/clist.c
  linear/queue.c
  linear/stack.c
  linear/set.c
  hash/hashtable.c
  tree/btree.c
  main.c)

set(INCLUDE_DIR
  core
  linear
  list
  hash
  tree)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE_DIR})

