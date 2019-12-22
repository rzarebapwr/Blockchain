project(src)

set(HEADER_FILES
        Block.h
        Blockchain.h
        cryptography.h
        Transactions.h
        UtxoSet.h
        Wallet.h
        )

set(SOURCE_FILES
        Block.cpp
        Blockchain.cpp
        Transactions.cpp
        UtxoSet.cpp
        Wallet.cpp
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

        ../lib/cryptoLib/CurvePoint.hpp
        ../lib/cryptoLib/CurvePoint.cpp

        ../lib/cryptoLib/Ecdsa.hpp
        ../lib/cryptoLib/Ecdsa.cpp

        ../lib/cryptoLib/FieldInt.hpp
        ../lib/cryptoLib/FieldInt.cpp

        ../lib/cryptoLib/CountOps.hpp

        ../lib/cryptoLib/Base58Check.hpp
        ../lib/cryptoLib/Base58Check.cpp

        ../lib/cryptoLib/Ripemd160.hpp
        ../lib/cryptoLib/Ripemd160.cpp

        ../lib/cryptoLib/ExtendedPrivateKey.hpp
        ../lib/cryptoLib/ExtendedPrivateKey.cpp

        ../lib/cryptoLib/Sha512.hpp
        ../lib/cryptoLib/Sha512.cpp

)

target_link_libraries(src PRIVATE cryptoLib)