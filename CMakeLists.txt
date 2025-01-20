cmake_minimum_required(VERSION 3.11)

project(GTestAllureUtilities)

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  option(BUILD_SAMPLE_TEST_PROJECT "Build sample test project" ON)
else()
  option(BUILD_SAMPLE_TEST_PROJECT "Build sample test project" OFF)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

	add_library(GTest::GTest ALIAS gtest)
endif()

# Configure GTestAllureUtilities static library
set(GTEST_ALLURE_UTILITIES GTestAllureUtilities)
file(GLOB_RECURSE GTEST_ALLURE_UTILITIES_SRC "src/*.cpp")
add_library(${GTEST_ALLURE_UTILITIES} STATIC ${GTEST_ALLURE_UTILITIES_SRC})

target_link_libraries(${GTEST_ALLURE_UTILITIES} PUBLIC GTest::GTest)
target_include_directories(${GTEST_ALLURE_UTILITIES} PUBLIC src)

target_compile_definitions(${GTEST_ALLURE_UTILITIES} PRIVATE 
	RAPIDJSON_HAS_STDSTRING=1
	RAPIDJSON_NAMESPACE=rapidjson_gtest_allure
	)
target_include_directories(${GTEST_ALLURE_UTILITIES} PRIVATE 
	src/GTestAllureUtilities
	deps)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_compile_options(${GTEST_ALLURE_UTILITIES} PRIVATE -Wno-error=implicit-fallthrough)
endif()

if (BUILD_SAMPLE_TEST_PROJECT)
	add_subdirectory(test/SampleTestProject)
endif()
