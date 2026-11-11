#include "m2_sic_robot/modes/manual_mode.h"
#include "m2_sic_robot/base/sic_robot_define.h"
#include "m2_sic_robot/commands/gripper/set_gripper_back_released_command.h"
#include "m2_sic_robot/commands/gripper/set_gripper_elevator_up_command.h"
#include "m2_sic_robot/commands/gripper/set_gripper_front_released_command.h"

#include "m2_fsm_cpp/base/fsm_command_scheduler.h"
#include "trolly/log/trolly_logger_macro.h"

namespace m2::sic_robot {

manual_mode::manual_mode() noexcept
    : ps_mode("Manual Mode")
{}

void manual_mode::tick() noexcept {}

void manual_mode::on_enter() noexcept { TROLLY_INFO("[Mode] Entering Manual Mode"); }

void manual_mode::on_exit() noexcept { TROLLY_INFO("[Mode] Exiting Manual Mode"); }

void manual_mode::on_input(const ps_input_data_type& /* data */) noexcept
{
    using namespace fsm::input;
    auto& cs = fsm::command_scheduler::instance();

    // schedule a single command
    //Changes made here to schedule gripper commands based on button presses
    if (is_dpad_pressed<ps_dpad_direction_t::UP>()) {
        cs.schedule_command<set_gripper_elevator_up_command>(true);
    } else if (is_dpad_pressed<ps_dpad_direction_t::DOWN>()) {
        cs.schedule_command<set_gripper_elevator_up_command>(false);
    }

    if (is_button_pressed<ps_button_t::CROSS>()) {
        cs.schedule_command<set_gripper_front_released_command>(true);
    } else if (is_button_pressed<ps_button_t::CIRCLE>()) {
        cs.schedule_command<set_gripper_front_released_command>(false);
    }

    if (is_button_pressed<ps_button_t::SQUARE>()) {
        cs.schedule_command<set_gripper_back_released_command>(true);
    } else if (is_button_pressed<ps_button_t::CIRCLE>()) {
        cs.schedule_command<set_gripper_back_released_command>(false);
    }
    // cancel all existing scheduled commands
    if (is_button_pressed<ps_button_t::OPTIONS>()) {
        cs.cancel_all_commands();
    }
}

}  // namespace m2::sic_robot
