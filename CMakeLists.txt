cmake_minimum_required(VERSION 3.11)

project(GTestAllureUtilities)

# Configure environment
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(rapidjson CONFIG)
if (rapidjson_FOUND)
  message(STATUS "Found rapidjson ${rapidjson_VERSION}")
else()
  add_library(RapidJSON INTERFACE)
  target_include_directories(RapidJSON INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/deps)

  add_library(rapidjson::rapidjson ALIAS RapidJSON)
endif()

find_package(GTest CONFIG)
if (GTest_FOUND)
  message(STATUS "Found Google Test ${GTest_VERSION}")
else()
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)

	add_library(GTest::GTest ALIAS gmock)
endif()

add_subdirectory(deps/cpp-test-utilities)
add_subdirectory(deps/cpp-json-adapter)
add_subdirectory(deps/cpp-rapidjson-json-adapter)

# Adjust compilation flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=implicit-fallthrough")
endif()

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/GTestAllureUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/TestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/UnitTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/IntegrationTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/SampleTestProject)
