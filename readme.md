# DSA

Library specifically made to provide abstract datastructures and some algorithms.

## Content

-   Graphs
-   Hashsets
-   Dictionaries(HashTables)
-   Dynamic Arrays
-   Linked Lists
-   Stacks
-   Queues
-   Trees
-   Priority Queues and Heaps
-   MISC memory related functionalities

## General Structure

1. create datastructure:
2. use it depending on your needs
3. destroy the datastructure

`
Set set;
set_create(&set, your_match_func, your_destroy_function);

// Do Something

set_destroy(&set);

`
