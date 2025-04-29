cmake_minimum_required(VERSION 3.5.0)
project(graph VERSION 0.1.0 LANGUAGES C)

add_executable(graph.exe evaluator.c graph.c parser.c ps_creator.c stack.c validator.c convertor.c)
target_link_libraries(graph.exe m)

include(CTest)
enable_testing()

