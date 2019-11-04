project(src)

set(HEADER_FILES
        Block.h
        Blockchain.h
        cryptography.h
        Transactions.cpp
        Transactions.h
        )

set(SOURCE_FILES
        Block.cpp
        Blockchain.cpp
        cryptography.h
        Transactions.cpp
        Transactions.h
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_library(
        sha256
        ../lib/sha256/sha256.h
        ../lib/sha256/sha256.cpp
)

target_link_libraries(src PRIVATE sha256)



add_library(
        cryptoLib

        ../lib/cryptoLib/Utils.hpp
        ../lib/cryptoLib/Utils.cpp

        ../lib/cryptoLib/Uint256.hpp
        ../lib/cryptoLib/Uint256.cpp

        ../lib/cryptoLib/Sha256.hpp
        ../lib/cryptoLib/Sha256.cpp

        ../lib/cryptoLib/Sha256Hash.hpp
        ../lib/cryptoLib/Sha256Hash.cpp

)

target_link_libraries(src PRIVATE cryptoLib)