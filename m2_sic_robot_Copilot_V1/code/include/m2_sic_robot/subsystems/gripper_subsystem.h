#ifndef M2_SIC_ROBOT_SUBSYSTEMS_GRIPPER_SUBSYSTEM_H
#define M2_SIC_ROBOT_SUBSYSTEMS_GRIPPER_SUBSYSTEM_H

#include "m2_fsm_cpp/base/fsm_subsystem.h"
#include "m2_sic_robot/base/sic_robot_define.h"

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

#include <gpiod.hpp>

namespace m2::sic_robot {

class gripper_subsystem : public fsm::subsystem {
public:
    explicit gripper_subsystem(std::shared_ptr<rclcpp::Node> node) noexcept;
    ~gripper_subsystem() noexcept = default;

    void set_elevator_up(bool target);
    void set_front_released(bool target);
    void set_back_released(bool target);

    void tick() noexcept override;

private:
    void example_sub_cb(const std_msgs::msg::Float32& msg) noexcept;

private:
    std::shared_ptr<rclcpp::Node> node_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr example_pub_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr example_sub_;

    gpiod::line front_;
    gpiod::line back_;
    gpiod::line elevator_;



    TROLLY_DISALLOW_COPY_AND_MOVE(gripper_subsystem);
};

}  // namespace m2::sic_robot

#endif  // M2_SIC_ROBOT_SUBSYSTEMS_GRIPPER_SUBSYSTEM_H
