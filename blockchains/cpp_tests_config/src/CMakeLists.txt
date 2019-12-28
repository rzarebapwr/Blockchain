project(src)

set(HEADER_FILES
        Checkout.h
        )

set(SOURCE_FILES
        Checkout.cpp
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})