cmake_minimum_required(VERSION 3.0)

project(TicTacToe)

add_executable(TicTacToe)

target_sources(TicTacToe PRIVATE tic_tac_toe.c board.c board.h)

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT TicTacToe)
