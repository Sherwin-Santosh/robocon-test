#include "m2_sic_robot/subsystems/gripper_subsystem.h"
#include "m2_sic_robot/base/sic_robot_define.h"

#include "trolly/log/trolly_logger_macro.h"
#include "trolly/math/trolly_math_util.h"

#include "std_msgs/msg/float32.hpp"

namespace m2::sic_robot {

gripper_subsystem::gripper_subsystem(std::shared_ptr<rclcpp::Node> node) noexcept
    : subsystem("gripper_subsystem")
    , node_(node)
{

    auto chip = gpiod::chip("gpiochip4"); //CHECK FOR PIN
    front_ = chip.get_line(18);
    front_.request({"front_", gpiod::line_request::DIRECTION_OUTPUT, 0}, false);
    back_ = chip.get_line(23);
    back_.request({"back_", gpiod::line_request::DIRECTION_OUTPUT, 0}, false);
    elevator_ = chip.get_line(24);
    elevator_.request({"elevator_", gpiod::line_request::DIRECTION_OUTPUT, 0}, false);
    
    // node_->declare_parameter("example_set_topic", "example/setpoint");
    // node_->declare_parameter("example_fb_topic", "example/feedback");

    // auto example_set_topic = node_->get_parameter("example_set_topic").as_string();
    // auto example_fb_topic = node_->get_parameter("example_fb_topic").as_string();

    // // publishers here...
    // example_pub_ = node_->create_publisher<std_msgs::msg::Float32>(example_set_topic, 1);

    // // subscribers here...
    // example_sub_ = node->create_subscription<std_msgs::msg::Float32>(example_fb_topic, 1,
    //     [this](const std_msgs::msg::Float32& msg) { this->example_sub_cb(msg); });
}

// void 
void gripper_subsystem::set_elevator_up(bool target) 
{
    elevator_.set_value(target);  // process msg here
}

void gripper_subsystem::set_front_released(bool target) 
{
    front_.set_value(target);  // process msg here
}

void gripper_subsystem::set_back_released(bool target) 
{
    back_.set_value(target);  // process msg here
}

// void gripper_subsystem::example_sub_cb(const std_msgs::msg::Float32& msg) noexcept
// {
//     (void)msg;  // process msg here
// }

void gripper_subsystem::tick() noexcept {}

}  // namespace m2::sic_robot
