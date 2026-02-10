add_library(Logger
        src/Logger/LogMessage.h
        src/Logger/RingBuffer.cpp)

target_sources(Logger
    PRIVATE
        src/Logger/Logger.cpp
        src/Logger/RingBuffer.cpp
    PUBLIC
        src/Logger/Logger.h
        src/Logger/ILogSink.h
        src/Logger/LogLevel.h
        src/Logger/LogMessage.h
        src/Logger/RingBuffer.h
)
target_include_directories(Logger
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

add_executable(RingBuffer src/Logger/RingBuffer.cpp)

set_target_properties(RingBuffer
        PROPERTIES
        OSX_DEPLOYMENT_TARGET 13.0
)


find_package(GTest REQUIRED)

enable_testing()

add_executable(
        logger_test
        tests/logger_test.cpp
)
target_link_libraries(
        logger_test
        Logger
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(logger_test)
