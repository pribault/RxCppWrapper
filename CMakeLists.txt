cmake_minimum_required(VERSION 3.8)

project(RxCppWrapper CXX)

# Options
set(ENABLE_DYNAMIC_LINK True)

# Set variables
set(RXCW_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(RXCW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(RXCW_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})

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

target_link_libraries(RxCW PRIVATE rxcpp)
