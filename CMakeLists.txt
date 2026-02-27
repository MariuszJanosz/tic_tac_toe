cmake_minimum_required(VERSION 3.0)

project(TicTacToe)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_LINK_WARNING_AS_ERROR ON)

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(TicTacToe)

target_sources(TicTacToe PRIVATE	tic_tac_toe.c
									board.c board.h
									players.c players.h
									human_player.c human_player.h
									ai_player.c ai_player.h
									menu.c menu.h
									input.c input.h)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT TicTacToe)
