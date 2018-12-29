cmake_minimum_required(VERSION 3.12)
project(projectpart1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -std=c++11 -pthread")

add_executable(projectpart1 main.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h Expression.h ExpressionCommand.h SmallLexer.cpp SmallLexer.h DataReaderServer.cpp DataReaderServer.h LineParser.cpp LineParser.h CommandMap.h BigLexer.cpp BigLexer.h Lexer.h SymbolTable.h ConditionParser.h IfCommand.cpp IfCommand.h BlockParser.cpp BlockParser.h ConditionParser.cpp DataSender.cpp DataSender.h ConnectCommand.cpp ConnectCommand.h SleepCommand.h PrintCommand.h WhileCommand.cpp WhileCommand.h Utilities.cpp Utilities.h BinaryExpression.cpp BinaryExpression.h Div.cpp Div.h Minus.cpp Minus.h Mult.cpp Mult.h Number.cpp Number.h Plus.cpp Plus.h FileOperation.cpp FileOperation.h VarCommand.cpp VarCommand.h EqualCommand.cpp EqualCommand.h)