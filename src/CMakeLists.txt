include_directories(${ROOT_DIR}/src)

#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRCS)

set(SRCS 
    "encryption_tool.h"
    "handler.h"
    "simple_xor.h"
    "simple_xor.cc"
)
add_library(${LIB_NAME} ${SRCS})
add_executable(${PACKAGE_NAME} main.cc ${SRCS})
target_link_libraries(${PACKAGE_NAME} PUBLIC gflags::gflags stdc++)
