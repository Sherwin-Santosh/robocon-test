/**
 * @file trolly_logger_ros2.h
 * @author Anthony Law (anthlaw@connect.hku.hk)
 * @brief Logger implementation using ros2 logging interface
 * @version 0.1
 * @date 2025-06-26
 *
 * @copyright Copyright (c) 2025 HKU Robocon Team
 *
 */

#ifndef TROLLY_LOGGER_ROS2_H
#define TROLLY_LOGGER_ROS2_H

#include "trolly/log/trolly_logger_base.h"

#include <rclcpp/rclcpp.hpp>

namespace trolly::log {

inline constexpr size_t LOG_ROS2_VSPRINTF_BUFFER_SIZE = 256;

/**
 * @brief Logger implementation using ros1 logging interface
 *
 */
class logger_ros2 : public logger_base {
public:
    explicit logger_ros2(
        const rclcpp::Logger& logger, const rclcpp::Clock::SharedPtr& clock) noexcept;

    ~logger_ros2() noexcept override = default;

    void log(logger_level_t level, const char* format, va_list args) const noexcept override;

    void log_throttle(logger_level_t level, double period, const char* format,
        va_list args) const noexcept override;

private:
    rclcpp::Logger logger_;
    rclcpp::Clock::SharedPtr clock_;

    TROLLY_DISALLOW_COPY_AND_MOVE(logger_ros2);
};

void use_ros2_logger(const rclcpp::Logger& logger, const rclcpp::Clock::SharedPtr& clock) noexcept;

}  // namespace trolly::log

#endif
