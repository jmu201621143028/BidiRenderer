#include <gtest/gtest.h>
#include <glog/logging.h>

#include "test_glyph_string.cpp"


int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::GLOG_INFO, "./testing.log");  
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}