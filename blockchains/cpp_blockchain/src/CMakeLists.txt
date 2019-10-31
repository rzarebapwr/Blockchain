project(src)

set(HEADER_FILES
        Block.h
        Blockchain.h
        cryptography.h
        Transaction.cpp
        Transaction.h
        )

set(SOURCE_FILES
        Block.cpp
        Blockchain.cpp
        cryptography.h
        Transaction.cpp
        Transaction.h
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_library(
        sha256
        ../lib/sha256/sha256.h
        ../lib/sha256/sha256.cpp
)

target_link_libraries(src PRIVATE sha256)