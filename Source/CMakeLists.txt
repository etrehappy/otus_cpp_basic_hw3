cmake_minimum_required (VERSION 3.8)

project(Guess_number_prj)

add_executable(GuessNumber
	main.cpp
	main.h
)

set_target_properties(GuessNumber PROPERTIES
	CXX_STANDART 20
	CXX_STANDART_REQUIRED ON
)

