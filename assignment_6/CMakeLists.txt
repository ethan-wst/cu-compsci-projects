cmake_minimum_required (VERSION 2.8.11)

# set default build to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Release or Debug" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall" CACHE INTERNAL "")

# get folder name as project name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

# defince cmake variables for file locations
file(GLOB USER_FILES_1
"code/*.h"
"code/*.cpp"
"code/*.hpp"
)

file(GLOB TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
"tests/test*.cpp"
)
<<<<<<<< HEAD:CU_CompSci_Projects/assignment_6/CMakeLists.txt

========
add_library(BookCollectionBase SHARED IMPORTED)
set_property(TARGET BookCollectionBase PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/library/BookCollectionBase.so")
>>>>>>>> af4fe0efdf7b187e04b9b41e4583b06fb860a2f1:Assignment_7/CMakeLists.txt
# Try to Find GTest
find_package(GTest QUIET)

if(GTEST_FOUND)
	message(">> GTest was found among local libraries.")
	include_directories(${GTEST_INCLUDE_DIRS})

	# create an executable for all tests 
	add_executable( run_tests ${TEST_FILES} ${USER_FILES_1} )
<<<<<<<< HEAD:CU_CompSci_Projects/assignment_6/CMakeLists.txt
	target_link_libraries( run_tests gtest_main ${GTEST_LIBRARIES} pthread)
========
    target_link_libraries( run_tests gtest_main ${GTEST_LIBRARIES} pthread BookCollectionBase)
>>>>>>>> af4fe0efdf7b187e04b9b41e4583b06fb860a2f1:Assignment_7/CMakeLists.txt

else()
	message(">> Couldn't find Local GTest library, Downloading one instead ...")

	# Download and unpack googletest at configure time
	configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
		${CMAKE_CURRENT_BINARY_DIR}/googletest-build
	        EXCLUDE_FROM_ALL)

	# create an executable for all tests 
	add_executable( run_tests ${TEST_FILES} ${USER_FILES_1} )

<<<<<<<< HEAD:CU_CompSci_Projects/assignment_6/CMakeLists.txt
	target_link_libraries( run_tests gtest_main)
========
	target_link_libraries( run_tests gtest_main BookCollectionBase)
>>>>>>>> af4fe0efdf7b187e04b9b41e4583b06fb860a2f1:Assignment_7/CMakeLists.txt

endif()

ENABLE_TESTING()

# create an executables in the app folder
<<<<<<<< HEAD:CU_CompSci_Projects/assignment_6/CMakeLists.txt
add_executable( run_app "app/main.cpp" ${USER_FILES_1} )
========
add_executable(run_app "app/main.cpp" ${USER_FILES_1} )
target_link_libraries(run_app BookCollectionBase)
>>>>>>>> af4fe0efdf7b187e04b9b41e4583b06fb860a2f1:Assignment_7/CMakeLists.txt
