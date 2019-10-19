cmake_minimum_required(VERSION 2.6)
project(demo)

aux_source_directory(. SOURCE)
include_directories(../include)

add_executable(demo ${SOURCE})