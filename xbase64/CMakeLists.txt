include(CheckIncludeFileCXX)
include(CheckFunctionExists)

check_include_file_cxx(io.h        HAVE_IO_H)
check_include_file_cxx(dos.h       HAVE_DOS_H)
check_include_file_cxx(dlfcn.h     HAVE_DLFCN_H)
check_include_file_cxx(fcntl.h     HAVE_FCNTL_H)
check_include_file_cxx(memory.h    HAVE_MEMORY_H)
check_include_file_cxx(stdint.h    HAVE_STDINT_H)
check_include_file_cxx(stdlib.h    HAVE_STDLIB_H)
check_include_file_cxx(stddef.h    HAVE_STDDEF_H)
check_include_file_cxx(string.h    HAVE_STRING_H)
check_include_file_cxx(unistd.h    HAVE_UNISTD_H)
check_include_file_cxx(strings.h   HAVE_STRINGS_H)
check_include_file_cxx(inttypes.h  HAVE_INTTYPES_H)
check_include_file_cxx(sys/stat.h  HAVE_SYS_STAT_H)
check_include_file_cxx(sys/types.h HAVE_SYS_TYPES_H)

check_function_exists(fseeko     HAVE_FSEEKO)
check_function_exists(ftello     HAVE_FTELLO)
check_function_exists(vsprintf   HAVE_VSPRINTF)
check_function_exists(vsnprintf  HAVE_VSNPRINTF)
check_function_exists(strcasecmp HAVE_STRCASECMP)

option(XBASE_DEBUG "compile in debug logic" ON)
option(XB_FILTERS "compile support for filters" ON)
option(XB_INDEX_NDX "compile support for ndx index logic" ON)
option(XB_INDEX_NTX "compile support for ntx index logic" ON)
option(XB_LARGEFILE_SUPPORT "compile in largefile support" ON)
option(XB_LOCKING_ON "compile support for record locking" ON)
option(XB_MEMO_FIELDS "compile support for memo fields" ON)
option(XB_REAL_DELETE "compile support for real record deletion" ON)
option(
	XB_EXPRESSIONS
	"compile support for expressions; index logic requires this be enabled"
	ON
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/xbconfig.h.in
	${CMAKE_CURRENT_BINARY_DIR}/xbase64/xbconfig.h
)

set(
	SRC_FILES
		xbase64.cpp
		xbcdx.cpp
		xbdate.cpp
		xbdbf.cpp
		xbexp.cpp
		xbexpfnc.cpp
		xbexpprc.cpp
		xbfields.cpp
		xbfile.cpp
		xbfilter.cpp
		xbindex.cpp
		xblock.cpp
		xbmemo.cpp
		xbndx.cpp
		xbnode.cpp
		xbntx.cpp
		xbstring.cpp
)

add_library(xbase64_static STATIC ${SRC_FILES})
set_target_properties(
	xbase64_static PROPERTIES
	OUTPUT_NAME "xbase64"
	VERSION ${XBASE_VERSION}
)
target_include_directories(
	xbase64_static
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
install(
	TARGETS xbase64_static
	ARCHIVE DESTINATION usr/lib
)
add_library(xbase64_shared SHARED ${SRC_FILES})
set_target_properties(
	xbase64_shared PROPERTIES
	OUTPUT_NAME "xbase64"
	VERSION ${XBASE_VERSION}
)
target_include_directories(
	xbase64_shared
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
	PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)
install(
	TARGETS xbase64_shared
	LIBRARY DESTINATION usr/lib
)

install(
	DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	DESTINATION usr/include
	FILES_MATCHING PATTERN "*.h"
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/xbase64/xbconfig.h
	DESTINATION usr/include/xbase64
)
