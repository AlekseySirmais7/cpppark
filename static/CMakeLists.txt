cmake_minimum_required(VERSION 3.2) 

project(static)				

set(SOURCE_LIB static.cpp)		

add_library(static STATIC ${SOURCE_LIB})