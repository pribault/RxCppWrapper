cmake_minimum_required(VERSION 3.8)

project(RxCppWrapper CXX)

# Options
if(NOT DEFINED ENABLE_DYNAMIC_LINK)
	set(ENABLE_DYNAMIC_LINK False)
endif()

# Load common cmake
include(${PROJECT_SOURCE_DIR}/cmake/RxCWCommon.cmake)

# Set environment
rxcw_set_env()

add_subdirectory(examples)

# Find required packages
find_package(rxcpp CONFIG REQUIRED)

# Retrieve sources
file(GLOB_RECURSE SOURCES RELATIVE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	${RXCW_INCLUDE_DIR}/**.h
	${RXCW_INCLUDE_DIR}/**.inl
	${RXCW_SOURCE_DIR}/**.cpp
)

include_directories(
	${RXCW_INCLUDE_DIR}
)

# Create library
if(ENABLE_DYNAMIC_LINK)
	add_library(RxCW SHARED ${SOURCES})
else()
	add_library(RxCW STATIC ${SOURCES})
endif()

set_target_properties(RxCW
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR}
)

target_link_libraries(RxCW PRIVATE rxcpp)

target_compile_features(RxCW PRIVATE cxx_std_17)
