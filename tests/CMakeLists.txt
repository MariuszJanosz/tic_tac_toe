add_executable(glfw_window_test glfw_window_test.c)

target_link_libraries(glfw_window_test PRIVATE glfw)
if (WIN32)
	target_link_libraries(glfw_window_test PRIVATE opengl32)
elseif (UNIX)
	target_link_libraries(glfw_window_test PRIVATE GL m)
else ()
	message(FATAL_ERROR "Unsupported OS")
endif ()


target_include_directories(glfw_window_test PRIVATE ${CMAKE_BINARY_DIR}/_deps/glfw-src/include)