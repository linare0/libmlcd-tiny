cmake_minimum_required(VERSION 3.3)
project(libmlcd-tiny C)
include_directories(./include/)
aux_source_directory(src/ libSource)
add_library(mlcd-tiny STATIC ${libSource})
