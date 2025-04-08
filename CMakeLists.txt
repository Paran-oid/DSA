cmake_minimum_required(VERSION 3.10.0)
project(DSA VERSION 0.1.0 LANGUAGES C)

set(SRC 
  core/core.c
  "linked list/list/list.c"
  "linked list/clist/clist.c"
  "linked list/dlist/dlist.c"
  linear/queue/queue.c
  linear/stack/stack.c
  linear/set/set.c
  linear/vector/vector.c
  hash/hashtable/hashtable.c
  tree/btree/btree.c
  tree/bistree/bistree.c
  tree/heap/heap.c
  graph/graph.c
  algorithms/graph_traversal.c
  algorithms/graph_algorithms.c
  algorithms/sorting.c
  hash/dictionary/dictionary.c
  main.c
  )

set(INCLUDE_DIR
  core
  linear/queue
  linear/set
  linear/stack
  linear/vector
  "linked list/list"
  "linked list/clist"
  "linked list/dlist"
  hash/hashtable
  tree/bistree
  tree/btree
  tree/heap
  hash/dictionary
  algorithms
  graph)

add_executable(DSA ${SRC})

target_include_directories(DSA PUBLIC ${INCLUDE_DIR})


target_link_libraries(DSA PRIVATE m)

