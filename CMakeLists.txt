cmake_minimum_required(VERSION 3.11)

project(GTestAllureUtilities)

option(BUILD_SAMPLE_TEST_PROJECT "Build sample test project" ON)

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

# Configure GTestAllureUtilities static library
set(GTEST_ALLURE_UTILITIES GTestAllureUtilities)
file(GLOB_RECURSE GTEST_ALLURE_UTILITIES_SRC "src/*.cpp")
add_library(${GTEST_ALLURE_UTILITIES} STATIC ${GTEST_ALLURE_UTILITIES_SRC})

target_link_libraries(${GTEST_ALLURE_UTILITIES} PUBLIC GTest::GTest)
target_include_directories(${GTEST_ALLURE_UTILITIES} PUBLIC src)

target_compile_definitions(${GTEST_ALLURE_UTILITIES} PRIVATE RAPIDJSON_HAS_STDSTRING=1)
target_include_directories(${GTEST_ALLURE_UTILITIES} PRIVATE 
	src/GTestAllureUtilities
	deps)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(${GTEST_ALLURE_UTILITIES} PRIVATE -Wno-error=implicit-fallthrough)
endif()

if (BUILD_SAMPLE_TEST_PROJECT)
	add_subdirectory(test/SampleTestProject)
endif()
