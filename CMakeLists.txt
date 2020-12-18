cmake_minimum_required (VERSION 3.10)
project (NanoPascal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Run FA2LEXER to generate the lexer
add_custom_command (
  OUTPUT lexer.cpp
  COMMAND fa2lexer --hdr tokens.h --src lexer.cpp --tpl ${PROJECT_SOURCE_DIR}/fa/project.fa2l
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/fa/project.fa2l
  DEPENDS ${PROJECT_SOURCE_DIR}/fa/Start.jff
          ${PROJECT_SOURCE_DIR}/fa/Comment.jff
          ${PROJECT_SOURCE_DIR}/fa/MultComment.jff
          ${PROJECT_SOURCE_DIR}/fa/Number.jff
          ${PROJECT_SOURCE_DIR}/fa/Identifier.jff
          ${PROJECT_SOURCE_DIR}/fa/Symbols.jff
          ${PROJECT_SOURCE_DIR}/fa/CompileDirectives.jff
          ${PROJECT_SOURCE_DIR}/fa/CharString.jff
)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp lexer.cpp) 