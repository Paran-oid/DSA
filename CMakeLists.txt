cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)

set(SRC 
  Core/core.c
  List/list.c
  List/dlist.c
  List/clist.c
  main.c)

set(INCLUDE_DIR
  Core
  List)

add_executable(DSA ${SRC})

target_include_directories(DSA PRIVATE ${INCLUDE_DIR})

