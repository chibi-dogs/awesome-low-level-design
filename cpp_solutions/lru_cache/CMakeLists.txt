add_library(LRUCache INTERFACE
)

target_sources(LRUCache
        PUBLIC
        src/Cache/LRUCache.h
)
target_include_directories(LRUCache
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

find_package(GTest REQUIRED)

enable_testing()

add_executable(
        lru_cache_test
        tests/lrucache_tests.cpp
)
target_link_libraries(
        lru_cache_test
        LRUCache
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lru_cache_test)