#include "trolly/ros2/log/trolly_logger_ros2.h"

namespace trolly::log {

logger_ros2::logger_ros2(
    const rclcpp::Logger& logger, const rclcpp::Clock::SharedPtr& clock) noexcept
    : logger_(logger)
    , clock_(clock)
{}

void logger_ros2::log(logger_level_t level, const char* format, va_list args) const noexcept
{
    char buffer[LOG_ROS2_VSPRINTF_BUFFER_SIZE];

    if (vsnprintf(buffer, LOG_ROS2_VSPRINTF_BUFFER_SIZE, format, args) < 0) {
        printf("Error using vsnprintf to write logs");
        return;
    }

    va_end(args);
    // TODO(Anthony Law): handlers for TRACE
    if (level == LOGGER_LEVEL_INFO) {
        RCLCPP_INFO(logger_, "%s", buffer);
    } else if (level == LOGGER_LEVEL_WARN) {
        RCLCPP_WARN(logger_, "%s", buffer);
    } else if (level == LOGGER_LEVEL_ERROR) {
        RCLCPP_ERROR(logger_, "%s", buffer);
    } else if (level == LOGGER_LEVEL_DEBUG) {
        RCLCPP_DEBUG(logger_, "%s", buffer);
    } else if (level == LOGGER_LEVEL_FATAL) {
        RCLCPP_FATAL(logger_, "%s", buffer);
    }
}

void logger_ros2::log_throttle(
    logger_level_t level, double period, const char* format, va_list args) const noexcept
{
    char buffer[LOG_ROS2_VSPRINTF_BUFFER_SIZE];

    if (vsnprintf(buffer, LOG_ROS2_VSPRINTF_BUFFER_SIZE, format, args) < 0) {
        printf("Error using vsnprintf to write logs");
        return;
    }

    va_end(args);
    // TODO(Anthony Law): handlers for TRACE and DEBUG
    auto period_in_ms = static_cast<int64_t>(period * 1000.0);
    if (level == LOGGER_LEVEL_INFO) {
        RCLCPP_INFO_THROTTLE(logger_, *clock_, period_in_ms, "%s", buffer);
    } else if (level == LOGGER_LEVEL_WARN) {
        RCLCPP_WARN_THROTTLE(logger_, *clock_, period_in_ms, "%s", buffer);
    } else if (level == LOGGER_LEVEL_ERROR) {
        RCLCPP_ERROR_THROTTLE(logger_, *clock_, period_in_ms, "%s", buffer);
    } else if (level == LOGGER_LEVEL_FATAL) {
        RCLCPP_FATAL_THROTTLE(logger_, *clock_, period_in_ms, "%s", buffer);
    }
}

void use_ros2_logger(const rclcpp::Logger& logger, const rclcpp::Clock::SharedPtr& clock) noexcept
{
    set_logger(std::make_unique<logger_ros2>(logger, clock));
}

}  // namespace trolly::log
