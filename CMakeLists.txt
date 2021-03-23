cmake_minimum_required(VERSION 3.17)
project(EarleyRecognizer)

set(CMAKE_CXX_STANDARD 17)

add_executable(EarleyRecognizer main.cpp Production.cpp Production.h State.cpp State.h Grammar.cpp Grammar.h EarleyRecognizer.cpp EarleyRecognizer.h)