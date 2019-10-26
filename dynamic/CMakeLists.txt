cmake_minimum_required(VERSION 3.2) 

project(dynamic)				

#set (FLAG -pthread)
set(SOURCE_LIB dynamic.cpp)		

add_library(dynamic SHARED ${SOURCE_LIB})
target_link_libraries(dynamic pthread)