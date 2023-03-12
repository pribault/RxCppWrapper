cmake_minimum_required(VERSION 3.8)

project(example_Observable CXX)

# Load common cmake
include(${PROJECT_SOURCE_DIR}/../../cmake/RxCWCommon.cmake)

set(RXCW_BINARY_DIR ${RXCW_ROOT_DIR}/build/bin)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR})
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

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

add_executable(example_Observable ${SOURCES})

if(UNIX)
	target_link_libraries(example_Observable PRIVATE rxcpp RxCW pthread)
else()
	target_link_libraries(example_Observable PRIVATE rxcpp RxCW)
endif()
