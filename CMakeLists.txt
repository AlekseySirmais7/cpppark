cmake_minimum_required(VERSION 3.2) 

project(main)				

set(SOURCE_EXE main.cpp)			

include_directories("./static" )
include_directories("./dynamic")				# Расположение заголовочных файлов

add_executable(main ${SOURCE_EXE})	# Создает исполняемый файл с именем main

add_subdirectory(static)
add_subdirectory(dynamic)				# Добавление подпроекта, указывается имя дирректории

target_link_libraries(main static dynamic)		# Линковка программы с библиотекой

