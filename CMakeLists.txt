cmake_minimum_required(VERSION 3.5)
project(ClipboardLogger)

option(DEBUG_CONSOLE ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")
message(STATUS "Output directory set to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if (MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:DEBUG>:Debug>")
	add_compile_options(/Zi /W3 /WX)
elseif(MINGW)
	add_compile_options(-g -Wall -Wextra -Wpedantic)
endif()

# find packages
find_package(SDL3 CONFIG REQUIRED)
# find sorce *.c abd *.cpp files
file(GLOB_RECURSE SRC_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# starting to setup the project


add_executable(ClipboardLogger ${SRC_FILES})

target_include_directories(ClipboardLogger PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(ClipboardLogger PRIVATE SDL3::SDL3-static)