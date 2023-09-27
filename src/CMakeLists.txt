#cmake_minimum_required(VERSION 3.24.3)
project("Terminal Timetable")

add_executable(timetable main.cpp utils.cpp)
configure_file(timetable.csv timetable.csv COPYONLY)
