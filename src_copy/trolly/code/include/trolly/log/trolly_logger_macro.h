/**
 * @file trolly_logger_macro.h
 * @author Fernando (ferrrnnnandochen@gmail.com)
 * @brief Logger interface macros
 * @version 0.1
 * @date 2023-11-05
 *
 * @copyright Copyright (c) 2023 HKU Robocon Team
 *
 */

#ifndef TROLLY_LOGGER_MACRO_H
#define TROLLY_LOGGER_MACRO_H

#include "trolly/log/trolly_logger_base.h"

/**
 * @brief Log as trace
 *
 */
#define TROLLY_TRACE(...) trolly::log::log(trolly::log::LOGGER_LEVEL_TRACE, __VA_ARGS__)

/**
 * @brief Log as debug
 *
 */
#define TROLLY_DEBUG(...) trolly::log::log(trolly::log::LOGGER_LEVEL_DEBUG, __VA_ARGS__)

/**
 * @brief Log as info
 *
 */
#define TROLLY_INFO(...) trolly::log::log(trolly::log::LOGGER_LEVEL_INFO, __VA_ARGS__)

/**
 * @brief Log as warn
 *
 */
#define TROLLY_WARN(...) trolly::log::log(trolly::log::LOGGER_LEVEL_WARN, __VA_ARGS__)

/**
 * @brief Log as error
 *
 */
#define TROLLY_ERROR(...) trolly::log::log(trolly::log::LOGGER_LEVEL_ERROR, __VA_ARGS__)

/**
 * @brief Log as fatal
 *
 */
#define TROLLY_FATAL(...) trolly::log::log(trolly::log::LOGGER_LEVEL_FATAL, __VA_ARGS__)

/**
 * @brief Log as trace at a throttled rate
 *
 */
#define TROLLY_TRACE_THROTTLE(...) \
    trolly::log::log_throttle(trolly::log::LOGGER_LEVEL_TRACE, __VA_ARGS__)

/**
 * @brief Log as debug at a throttled rate
 *
 */
#define TROLLY_DEBUG_THROTTLE(...) \
    trolly::log::log_throttle(trolly::log::LOGGER_LEVEL_DEBUG, __VA_ARGS__)

/**
 * @brief Log as info at a throttled rate
 *
 */
#define TROLLY_INFO_THROTTLE(...) \
    trolly::log::log_throttle(trolly::log::LOGGER_LEVEL_INFO, __VA_ARGS__)

/**
 * @brief Log as warn at a throttled rate
 *
 */
#define TROLLY_WARN_THROTTLE(...) \
    trolly::log::log_throttle(trolly::log::LOGGER_LEVEL_WARN, __VA_ARGS__)

/**
 * @brief Log as error at a throttled rate
 *
 */
#define TROLLY_ERROR_THROTTLE(...) \
    trolly::log::log_throttle(trolly::log::LOGGER_LEVEL_ERROR, __VA_ARGS__)

#endif
