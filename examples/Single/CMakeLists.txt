cmake_minimum_required(VERSION 3.8)

project(example_Single CXX)

# Load common cmake
include(${PROJECT_SOURCE_DIR}/../../cmake/RxCWCommon.cmake)

# Set environment
rxcw_set_env()

set(RXCW_BINARY_DIR ${RXCW_ROOT_DIR}/build/bin)

rxcw_set(INCLUDE_DIR ${PROJECT_SOURCE_DIR})
rxcw_set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
rxcw_set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES RELATIVE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	${INCLUDE_DIR}/**.h
	${INCLUDE_DIR}/**.inl
	${SOURCE_DIR}/**.cpp
)

include_directories(
	${INCLUDE_DIR}
	${RXCW_INCLUDE_DIR}
)

# RxCpp
find_package(rxcpp CONFIG REQUIRED)

add_executable(example_Single ${SOURCES})

target_link_libraries(example_Single PRIVATE
	rxcpp
	RxCW
)
