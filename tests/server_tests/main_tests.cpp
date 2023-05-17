#include <gtest/gtest.h>
// go to build/test and run ./server_tests to run tests

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
