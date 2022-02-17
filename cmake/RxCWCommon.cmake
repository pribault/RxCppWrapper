
macro(rxcw_set)
	set(${ARGV0} ${ARGV1} PARENT_SCOPE)
	set(${ARGV0} ${ARGV1})
endmacro()

# setup cmake env
function(rxcw_set_env)
	# RXCW_CMAKE_DIR is the directory of RxCWCommon.cmake
	rxcw_set(RXCW_CMAKE_DIR ${CMAKE_CURRENT_FUNCTION_LIST_DIR})

	rxcw_set(RXCW_ROOT_DIR ${RXCW_CMAKE_DIR}/..)
	rxcw_set(RXCW_INCLUDE_DIR ${RXCW_ROOT_DIR}/include)
	rxcw_set(RXCW_SOURCE_DIR ${RXCW_ROOT_DIR}/src)
	rxcw_set(RXCW_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

	rxcw_set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})
	rxcw_set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})
	rxcw_set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RXCW_OUTPUT_DIR})
endfunction()
