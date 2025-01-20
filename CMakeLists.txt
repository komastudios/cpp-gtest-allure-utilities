cmake_minimum_required(VERSION 3.11)

project(GTestAllureUtilities)

set(GTEST_ALLURE_GTEST_TARGET "GTest::GTest" CACHE STRING "Google Test target name")

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  option(GTEST_ALLURE_USE_EXTERNAL_GOOGLETEST "Use external GoogleTest" OFF)
  option(GTEST_ALLURE_FIND_GOOGLETEST "Use external GoogleTest" ON)

  option(BUILD_SAMPLE_TEST_PROJECT "Build sample test project" ON)
else()
  option(GTEST_ALLURE_USE_EXTERNAL_GOOGLETEST "Use external GoogleTest" ON)
  option(GTEST_ALLURE_FIND_GOOGLETEST "Use external GoogleTest" OFF)

  option(BUILD_SAMPLE_TEST_PROJECT "Build sample test project" OFF)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GTEST_TARGET ${GTEST_ALLURE_GTEST_TARGET})

if(GTEST_ALLURE_FIND_GOOGLETEST)
  find_package(GTest CONFIG QUIET)
  if (GTest_FOUND)
    message(STATUS "Found Google Test ${GTest_VERSION}")
  endif()
endif()

if(NOT TARGET ${GTEST_TARGET} AND NOT GTEST_ALLURE_USE_EXTERNAL_GOOGLETEST)
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        b514bdc898e2951020cbdca1304b75f5950d1f59 # release-1.15.2
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)

  set(GTEST_TARGET "gtest")
endif()

if(NOT TARGET ${GTEST_TARGET})
  message(FATAL_ERROR "Google Test target not found: ${GTEST_TARGET}")
endif()

# Configure GTestAllureUtilities static library
set(GTEST_ALLURE_UTILITIES GTestAllureUtilities)
file(GLOB_RECURSE GTEST_ALLURE_UTILITIES_SRC "src/*.cpp")
add_library(${GTEST_ALLURE_UTILITIES} STATIC ${GTEST_ALLURE_UTILITIES_SRC})

target_link_libraries(${GTEST_ALLURE_UTILITIES} PUBLIC ${GTEST_TARGET})
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
