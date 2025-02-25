cmake_minimum_required(VERSION 3.28.3)
project(DSA)
set(CMAKE_C_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

# Gather all .c source files
file(GLOB_RECURSE SRC
  "Array/*.c"
  "Bits/*.c"
  "Hash/*.c"
  "Linked Lists/*.c"
  "Map/*.c"
  "Matrix/*.c"
  "Queue/*.c"
  "Stack/*.c"
  "Tree/*.c"
  "Utils/*.c"
  "main.c"
)

set(INCLUDE_DIRS   
  "${CMAKE_SOURCE_DIR}/Array"
  "${CMAKE_SOURCE_DIR}/Bits"
  "${CMAKE_SOURCE_DIR}/Hash"
  "${CMAKE_SOURCE_DIR}/Linked Lists"
  "${CMAKE_SOURCE_DIR}/Map"
  "${CMAKE_SOURCE_DIR}/Matrix"
  "${CMAKE_SOURCE_DIR}/Queue"
  "${CMAKE_SOURCE_DIR}/Stack"
  "${CMAKE_SOURCE_DIR}/Tree"
  "${CMAKE_SOURCE_DIR}/Utils")

add_executable(DSA ${SRC})

# Tell the compiler where to find .h files (directories, not files!)
target_include_directories(DSA PRIVATE
  ${INCLUDE_DIRS}
)

# Compiler options
target_compile_options(DSA PRIVATE
  -Wall
  -Wextra
  -Wpedantic
  # TODO reenable me
  # -Werror
  -O2
)

# (Optional) custom run target
# add_custom_target(RUN ALL
#   COMMAND "./DSA"
# )
