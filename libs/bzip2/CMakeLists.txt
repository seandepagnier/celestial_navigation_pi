cmake_minimum_required(VERSION 3.1.0)

if (TARGET ocpn::bzip2)
    return ()
endif ()

set(SAVE_CMLOC_BZIP2 ${CMLOC})
set(CMLOC "CMakeLists_BZIP2: ")

message(STATUS "${CMLOC}Building BZIP2")
SET(SRC
    src/bzlib.c
    src/blocksort.c
    src/compress.c
    src/crctable.c
    src/decompress.c
    src/huffman.c
    src/randtable.c
  )

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(BZIP2 STATIC ${SRC})
target_include_directories(BZIP2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(ocpn::bzip2 ALIAS BZIP2)

set(CMLOC ${SAVE_CMLOC_BZIP2})
