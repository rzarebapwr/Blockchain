project(src)

set(HEADER_FILES
        Block.h
        Blockchain.h
        sha256.cpp sha256.h cryptography.h)

set(SOURCE_FILES
        Block.cpp
        Blockchain.cpp
        sha256.cpp sha256.h cryptography.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})