cmake_minimum_required(VERSION 3.12)
project(projectpart1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11 -pthread")

add_executable(projectpart1 main.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h Expression.h ExpressionCommand.h Lexer.cpp Lexer.h DataReaderServer.cpp DataReaderServer.h)