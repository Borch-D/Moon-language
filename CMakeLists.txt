cmake_minimum_required(VERSION 3.4)

project(Moon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lexer_lib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/text_split_by_words.cpp
        )

add_library(parser_lib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/expression_parse.cpp)

add_library(executor_lib STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/executor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/operators.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/main/main.cpp)

target_link_libraries(main lexer_lib parser_lib executor_lib)
