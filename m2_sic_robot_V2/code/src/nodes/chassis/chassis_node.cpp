#include "m2_sic_robot/nodes/chassis/chassis_node.h"
#include "m2_interfaces/msg/joy_data.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

#include "trolly/log/trolly_logger_macro.h"
#include "trolly/ros2/log/trolly_logger_ros2.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>

using namespace std::chrono_literals;

namespace m2::sic_robot {

chassis_node::chassis_node()
    : rclcpp::Node("chassis_node")
{
    declare_parameter<double>("max_vel", max_vel_);
    declare_parameter<double>("max_steer_differential", max_steer_differential_);
    declare_parameter<std::string>("input_topic", "/input/joy_data");
    timer_ = create_wall_timer(10ms, [this]() { tick(); });
}

bool chassis_node::init()
{
    TROLLY_INFO("[chassis_node] Node init begin.");

    max_vel_ = get_parameter("max_vel").as_double();
    max_steer_differential_ = get_parameter("max_steer_differential").as_double();
    const auto input_topic = get_parameter("input_topic").as_string();

    if (!std::isfinite(max_vel_) || max_vel_ <= 0.0 ||
        !std::isfinite(max_steer_differential_) || max_steer_differential_ < 0.0 ||
        max_vel_ > std::numeric_limits<float>::max() ||
        max_steer_differential_ > std::numeric_limits<float>::max() ||
        input_topic.empty()) {
        TROLLY_ERROR("[chassis_node] Invalid speed limit, steering limit, or input topic.");
        return false;
    }

    left_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("left_wheel/v_setpoint", 1);
    right_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("right_wheel/v_setpoint", 1);
    controller_sub_ = create_subscription<m2_interfaces::msg::JoyData>(
        input_topic, 1,
        [this](const m2_interfaces::msg::JoyData& data) { on_controller_data_cb(data); });

    TROLLY_INFO("[chassis_node] Node init end.");
    return true;
}

void chassis_node::tick()
{
    if (!left_wheel_pub_ || !right_wheel_pub_) {
        return;
    }

    const double forward = hat_ly_ * std::pow(max_vel_, 3);
    const double turn = hat_lx_ * std::pow(max_steer_differential_, 3);
    double left_rpm = forward - turn;
    double right_rpm = forward + turn;

    const double peak_command = std::max(std::abs(left_rpm), std::abs(right_rpm));
    if (peak_command > max_vel_) {
        const double scale = max_vel_ / peak_command;
        left_rpm = left_rpm * scale;
        right_rpm = right_rpm * scale;
    }

    std_msgs::msg::Float32 left_command{};
    left_command.data = static_cast<float>(left_rpm);
    left_wheel_pub_->publish(left_command);

    std_msgs::msg::Float32 right_command{};
    right_command.data = static_cast<float>(right_rpm);
    right_wheel_pub_->publish(right_command);
}

void chassis_node::on_controller_data_cb(const m2_interfaces::msg::JoyData& data)
{
    hat_ly_ = std::isfinite(data.hat_ly)
        ? std::clamp(static_cast<double>(data.hat_ly), -1.0, 1.0)
        : 0.0;
    hat_lx_ = std::isfinite(data.hat_lx)
        ? std::clamp(static_cast<double>(data.hat_lx), -1.0, 1.0)
        : 0.0;
}

}  // namespace m2::sic_robot

void shutdown(int)
{
    rclcpp::shutdown();
    exit(0);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    signal(SIGINT, shutdown);

    auto node = std::make_shared<m2::sic_robot::chassis_node>();
    trolly::log::use_ros2_logger(node->get_logger(), node->get_clock());

    if (node->init()) {
        rclcpp::spin(node);
    } else {
        TROLLY_ERROR("[chassis_node] Node init fail! Exiting...");
    }

    rclcpp::shutdown();
    return 0;
}











// #include "m2_sic_robot/nodes/chassis/chassis_node.h"
// #include "m2_interfaces/msg/joy_data.hpp"
// #include "rclcpp/rclcpp.hpp"
// #include "std_msgs/msg/float32.hpp"

// #include "trolly/log/trolly_logger_macro.h"
// #include "trolly/ros2/log/trolly_logger_ros2.h"

// #include <algorithm>
// #include <chrono>
// #include <cmath>

// using namespace std::chrono_literals;

// namespace m2::sic_robot {
// namespace {

// double controller_hat_ly_ = 0.0;
// double controller_hat_lx_ = 0.0;

// }  // namespace

// chassis_node::chassis_node()
//     : rclcpp::Node("chassis_node")
// {
//     declare_parameter<double>("max_vel", max_vel_);
//     declare_parameter<double>("max_steer_differential", max_steer_differential_);
//     declare_parameter<std::string>("input_topic", "/input/joy_data");
//     create_wall_timer(10ms, [this]() { tick(); });
// }

// bool chassis_node::init()
// {
//     TROLLY_INFO("[chassis_node] Node init begin.");

//     max_vel_ = get_parameter("max_vel").as_double();
//     max_steer_differential_ = get_parameter("max_steer_differential").as_double();
//     const auto input_topic = get_parameter("input_topic").as_string();

//     if (!std::isfinite(max_vel_) || max_vel_ <= 0.0 ||
//         !std::isfinite(max_steer_differential_) || max_steer_differential_ < 0.0 ||
//         input_topic.empty()) {
//         TROLLY_ERROR("[chassis_node] Invalid speed limit, steering limit, or input topic.");
//         return false;
//     }

//     left_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("left_wheel/v_setpoint", 1);
//     right_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("right_wheel/v_setpoint", 1);
//     controller_sub_ = create_subscription<m2_interfaces::msg::JoyData>(
//         input_topic, 1,
//         [this](const m2_interfaces::msg::JoyData& data) { on_controller_data_cb(data); });

//     TROLLY_INFO("[chassis_node] Node init end.");
//     return true;
// }

// void chassis_node::tick()
// {
//     const double forward = hat_ly_ * stmax_vel_;
//     const double steering = hat_lx_ * max_steer_differential_;

//     double left_rpm = forward - steering;
//     double right_rpm = forward + steering;

//     const double largest_wheel_rpm = std::max(std::abs(left_rpm), std::abs(right_rpm));
//     if (largest_wheel_rpm > max_vel_) {
//         const double scale = max_vel_ / largest_wheel_rpm;
//         left_rpm *= scale;
//         right_rpm *= scale;
//     }

//     std_msgs::msg::Float32 left_command{};
//     left_command.data = static_cast<float>(left_rpm);
//     left_wheel_pub_->publish(left_command);

//     std_msgs::msg::Float32 right_command{};
//     right_command.data = static_cast<float>(right_rpm);
//     right_wheel_pub_->publish(right_command);
// }

// void chassis_node::on_controller_data_cb(const m2_interfaces::msg::JoyData& data)
// {
//     hat_ly_ = std::isfinite(data.hat_ly)
//         ? std::clamp(static_cast<double>(data.hat_ly), -1.0, 1.0)
//         : 0.0;
//     hat_lx_ = std::isfinite(data.hat_lx)
//         ? std::clamp(static_cast<double>(data.hat_lx), -1.0, 1.0)
//         : 0.0;
// }

// }  // namespace m2::sic_robot

// void shutdown(int)
// {
//     rclcpp::shutdown();
//     exit(0);
// }

// int main(int argc, char** argv)
// {
//     rclcpp::init(argc, argv);
//     signal(SIGINT, shutdown);

//     auto node = std::make_shared<m2::sic_robot::chassis_node>();
//     trolly::log::use_ros2_logger(node->get_logger(), node->get_clock());

//     if (node->init()) {
//         rclcpp::spin(node);
//     } else {
//         TROLLY_ERROR("[chassis_node] Node init fail! Exiting...");
//     }

//     rclcpp::shutdown();
//     return 0;
// }










// // #include "m2_sic_robot/nodes/chassis/chassis_node.h"
// // #include "m2_interfaces/msg/joy_data.hpp"
// // #include "rclcpp/rclcpp.hpp"
// // #include "std_msgs/msg/float32.hpp"

// // #include "trolly/log/trolly_logger_macro.h"
// // #include "trolly/ros2/log/trolly_logger_ros2.h"

// // #include <algorithm>
// // #include <cmath>

// // namespace m2::sic_robot {

// // chassis_node::chassis_node()
// //     : rclcpp::Node("chassis_node")
// // {
// // }

// // bool chassis_node::init()
// // {
// //     TROLLY_INFO("[chassis_node] Node init begin.");

// //     max_vel_ = declare_parameter("max_vel", max_vel_);
// //     max_steer_differential_ =
// //         declare_parameter("max_steer_differential", max_steer_differential_);
// //     if (!std::isfinite(max_vel_) || max_vel_ <= 0.0 ||
// //         !std::isfinite(max_steer_differential_) || max_steer_differential_ < 0.0) {
// //         TROLLY_ERROR("[chassis_node] Velocity limits must be finite; max_vel must be positive "
// //                      "and max_steer_differential must not be negative.");
// //         return false;
// //     }

// //     left_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("/left_wheel/v_setpoint", 10);
// //     right_wheel_pub_ = create_publisher<std_msgs::msg::Float32>("/right_wheel/v_setpoint", 10);
// //     controller_sub_ = create_subscription<m2_interfaces::msg::JoyData>(
// //         "/input/joy_data", 10,
// //         [this](const m2_interfaces::msg::JoyData& data) { on_controller_data_cb(data); });

// //     TROLLY_INFO("[chassis_node] Node init end.");
// //     return true;
// // }

// // void chassis_node::tick()
// // {
// // }

// // void chassis_node::on_controller_data_cb(const m2_interfaces::msg::JoyData& data)
// // {
// //     if (!std::isfinite(data.hat_ly) || !std::isfinite(data.hat_lx)) {
// //         TROLLY_WARN("[chassis_node] Non-finite controller axes; stopping both wheels.");
// //         const std_msgs::msg::Float32 stop_command{};
// //         left_wheel_pub_->publish(stop_command);
// //         right_wheel_pub_->publish(stop_command);
// //         return;
// //     }

// //     const auto forward = std::clamp(static_cast<double>(data.hat_ly), -1.0, 1.0);
// //     const auto turn = std::clamp(static_cast<double>(data.hat_lx), -1.0, 1.0);
// //     const auto left_velocity = std::clamp(
// //         max_vel_ * forward - max_steer_differential_ * turn, -max_vel_, max_vel_);
// //     const auto right_velocity = std::clamp(
// //         max_vel_ * forward + max_steer_differential_ * turn, -max_vel_, max_vel_);

// //     std_msgs::msg::Float32 left_command{};
// //     left_command.data = static_cast<float>(left_velocity);
// //     left_wheel_pub_->publish(left_command);

// //     std_msgs::msg::Float32 right_command{};
// //     right_command.data = static_cast<float>(-right_velocity);
// //     right_wheel_pub_->publish(right_command);
// // }

// // }  // namespace m2::sic_robot

// // void shutdown(int)
// // {
// //     rclcpp::shutdown();
// //     exit(0);
// // }

// // int main(int argc, char** argv)
// // {
// //     rclcpp::init(argc, argv);
// //     signal(SIGINT, shutdown);

// //     auto node = std::make_shared<m2::sic_robot::chassis_node>();
// //     trolly::log::use_ros2_logger(node->get_logger(), node->get_clock());

// //     if (node->init()) {
// //         rclcpp::spin(node);
// //     } else {
// //         TROLLY_ERROR("[chassis_node] Node init fail! Exiting...");
// //     }

// //     rclcpp::shutdown();
// //     return 0;
// // }
