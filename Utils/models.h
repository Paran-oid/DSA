#pragma once

#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

// ####################################################################################################################################
/*
  Core Section
*/
// ####################################################################################################################################

typedef enum {
  DATATYPE_CHAR,
  DATATYPE_INT,
  DATATYPE_FLOAT,
  DATATYPE_DOUBLE,
  DATATYPE_STRING,
  DATATYPE_PAIR,
  DATATYPE_NODE,
  DataType_TREENODE,
  DATATYPE_COUNT,
} DataType;

typedef struct {
  void *first;
  void *second;
  size_t element_size;
  DataType type;
} Pair;

// ####################################################################################################################################
/*
  Logger Section
*/
// ####################################################################################################################################

typedef struct {
  FILE *file;
  pthread_mutex_t log_mutex;
} Logger;

typedef enum {
  LOG_TYPE_INFORMATION,
  LOG_TYPE_WARNING,
  LOG_TYPE_DANGER,
  LOG_TYPE_COUNT
} LogType;

typedef enum { LOG_DATE_SESSION, LOG_DATE_ALL } LogDateType;

// ####################################################################################################################################
/*
  Array Section
*/
// ####################################################################################################################################

typedef struct {
  void *data;
  size_t element_size;
  size_t size;
  size_t capacity;
  DataType type;
} Array;

// ####################################################################################################################################
/*
  Linked List Section
*/
// ####################################################################################################################################

// SINGLE LINKED LIST (CIRCULAR & NORMAL)
typedef struct ListNode {
  void *value;
  struct ListNode *next;
  size_t element_size;
} ListNode;

typedef struct {
  ListNode *head;
  size_t element_size;
  DataType type;
} List;

// DOUBLY LINKED LIST
typedef struct DListNode {
  void *value;
  struct DListNode *next;
  struct DListNode *prev;
} DListNode;

typedef struct {
  DListNode *head;
  size_t element_size;
} DList;

// ####################################################################################################################################
/*
  Tree Section
*/
// ####################################################################################################################################

typedef struct TreeNode {
  void *value;
  struct TreeNode *right;
  struct TreeNode *left;
} TreeNode;

typedef struct {
  TreeNode *root;
  size_t element_size;
  DataType type;
} Tree;

typedef enum {
  TRAVERSE_INORDER,
  TRAVERSE_PREORDER,
  TRAVERSE_POSTORDER,
  TRAVERSE_LEVELORDER,
  TRAVERSE_COUNT
} TraverseMode;

// ####################################################################################################################################
/*
  Stack Section
*/
// ####################################################################################################################################

typedef struct {
  ListNode **items;
  ListNode *head;
  ListNode *tail;
  size_t element_size;
  DataType type;
} Stack;

// ####################################################################################################################################
/*
  Queue Section
*/
// ####################################################################################################################################

typedef struct {
  ListNode *front;
  ListNode *back;
  size_t element_size;
  DataType type;
} Queue;

// ####################################################################################################################################
/*
  Matrix Section
*/
// ####################################################################################################################################

typedef struct {
  void **items;
  size_t rows;
  size_t cols;
  size_t element_size;
  DataType type;
} Matrix;

// ####################################################################################################################################
