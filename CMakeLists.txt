cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)

set(SRC 
  core/core.c
  list/list.c
  list/dlist.c
  list/clist.c
  main.c)

set(INCLUDE_DIR
  Core
  list)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE_DIR})

