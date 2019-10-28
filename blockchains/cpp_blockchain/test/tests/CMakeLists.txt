include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests
        tests.cpp
        blockTest.cpp
        blockchainTest.cpp
        cryptographyTest.cpp)

target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests src)