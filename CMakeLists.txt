cmake_minimum_required(VERSION 3.14)

project(TicTacToe)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_LINK_WARNING_AS_ERROR ON)

include(FetchContent)
FetchContent_Declare(GLFW
					GIT_REPOSITORY git@github.com:glfw/glfw.git
					GIT_TAG 3.4)
FetchContent_MakeAvailable(GLFW)

find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(VENV_DIR ${CMAKE_BINARY_DIR}/.venv)

if(NOT EXISTS ${VENV_DIR})
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -m venv --upgrade-deps --system-site-packages ${VENV_DIR}
        RESULT_VARIABLE VENV_CREATED
    )

    if(VENV_CREATED)
        message(FATAL_ERROR "Failed to create python venv")
    endif()
endif()

if (WIN32)
	set(VENV_PYTHON ${VENV_DIR}/Scripts/python.exe)
elseif (UNIX)
	set(VENV_PYTHON ${VENV_DIR}/bin/python)
else ()
	message(FATAL_ERROR "Unsupported OS")
endif ()

execute_process(COMMAND ${VENV_PYTHON} -m pip install --upgrade pip
				RESULT_VARIABLE PIP_AVAILABLE)

if (PIP_AVAILABLE)
	message(FATAL_ERROR "Pip missing")
endif ()

execute_process(COMMAND ${VENV_PYTHON} -c "import imageio.v3"
				RESULT_VARIABLE IMAGEIO_AVAILABLE)

if (IMAGEIO_AVAILABLE)
	message(STATUS "ImageIO not found. Installing...")

    execute_process(COMMAND ${VENV_PYTHON} -m pip install ImageIO
					RESULT_VARIABLE INSTALL_STATUS)

    if(INSTALL_STATUS)
        message(FATAL_ERROR "Failed to install ImageIO")
    endif()
endif ()

if (WIN32)
	if (MSVC)
		add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	endif()
elseif (UNIX)
else ()
	message(FATAL_ERROR "Unsupported OS")
endif ()

add_executable(TicTacToe)

target_sources(TicTacToe PRIVATE	tic_tac_toe.c
									board.c board.h
									players.c players.h
									human_player.c human_player.h
									ai_player.c ai_player.h
									menu.c menu.h
									input.c input.h
									terminal_draw.c terminal_draw.h
									gui_draw.c gui_draw.h
									terminal_tictactoe.c terminal_tictactoe.h
									gui_tictactoe.c gui_tictactoe.h
									button.c button.h
									phases.c phases.h
									update.c update.h
									render.c render.h
									${CMAKE_BINARY_DIR}/font_atlas.c ${CMAKE_BINARY_DIR}/font_atlas.h)

target_link_libraries(TicTacToe PRIVATE glfw)
if (WIN32)
	target_link_libraries(TicTacToe PRIVATE opengl32)
elseif (UNIX)
	target_link_libraries(TicTacToe PRIVATE GL m)
else ()
	message(FATAL_ERROR "Unsupported OS")
endif ()
target_include_directories(TicTacToe PRIVATE	${CMAKE_BINARY_DIR}/_deps/glfw-src/include
												${CMAKE_SOURCE_DIR}
												${CMAKE_BINARY_DIR})

set_directory_properties(PROPERTIES VS_STARTUP_PROJECT TicTacToe)

add_custom_target(	Generate_Font_Atlas 
					${VENV_PYTHON} ${CMAKE_SOURCE_DIR}/generate_font_atlas.py ${CMAKE_BINARY_DIR}/font_atlas.c ${CMAKE_SOURCE_DIR}/font_atlas.c.in
					BYPRODUCTS ${CMAKE_BINARY_DIR}/font_atlas.c ${CMAKE_BINARY_DIR}/font_atlas.h
					SOURCES generate_font_atlas.py font_atlas.c.in)

add_dependencies(TicTacToe Generate_Font_Atlas)

add_subdirectory(tests)
