#include <gtest/gtest.h>
#include <Logger/Logger.h>

using namespace logger;

TEST(LoggerTest, Formatter) {
    const auto logMsg = "This is a log!";
    const auto timestamp = std::chrono::system_clock::now();
    constexpr auto level = LogLevel::INFO;
    const auto msg = LogMessage{.time_ = timestamp, .level_ = level,.message_ = logMsg };
    const auto expected_message = std::format("timestamp={} level=INFO message=This is a log!", timestamp);
    std::ostringstream oss;
    oss << msg;
    EXPECT_EQ(oss.str(), expected_message);
}

// TEST(LoggerTest, LogFilter) {
//     const LoggerConfig config = {.level = LogLevel::INFO }
//     Logger logger{config};
//     logger::info("here is some information");
//     logger::debug("here is some debugging information");
//     logger::warn("Something bad happened");
//      check that filtering works
//     output should contain: info and warn. where to check?
// OUTPUT:
// new entity LogAggregator holds logs before flushing to destination.
// timestamp=... level=INFO message="here is some information"
// timestamp=... level=WARN message="Something bad happened"
// }


// TEST(LoggerTest, LogToFiler) {
//     const LoggerConfig config = {.level = LogLevel::INFO, log_to_file = "path_to_log.log" }
//     Logger logger{config};
//     logger::info("here is some information");
//     logger::debug("here is some debugging information");
//     logger::warn("Something bad happened");
//      check that filtering works
//     check file exists
// check that file contains
// timestamp=... level=INFO message="here is some information"
// timestamp=... level=WARN message="Something bad happened"
// }