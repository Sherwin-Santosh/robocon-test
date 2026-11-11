/**
 * @file trolly_logger_base.h
 * @author Fernando (ferrrnnnandochen@gmail.com)
 * @brief Logger interface and wrapper
 * @version 0.1
 * @date 2023-11-05
 *
 * @copyright Copyright (c) 2023 HKU Robocon Team
 *
 */

#ifndef TROLLY_LOGGER_BASE_H
#define TROLLY_LOGGER_BASE_H

#include "trolly/trolly_macro.h"

#include <cstdarg>
#include <memory>

namespace trolly::log {

/**
 * @brief Log levels
 *
 */
enum logger_level_t : uint8_t {
    LOGGER_LEVEL_TRACE = 0,
    LOGGER_LEVEL_DEBUG = 1,
    LOGGER_LEVEL_INFO = 2,
    LOGGER_LEVEL_WARN = 3,
    LOGGER_LEVEL_ERROR = 4,
    LOGGER_LEVEL_FATAL = 5
};

/**
 * @brief Abstract interface for logger
 *
 */
class logger_base {
public:
    logger_base() noexcept = default;

    virtual ~logger_base() noexcept = default;

    /**
     * @brief Log into the global logger with the provided log level, format and arguments
     *
     * @param level Log level
     * @param format Log format
     * @param args Log format arguments
     */
    virtual void log(logger_level_t level, const char* format, va_list args) const noexcept = 0;

    /**
     * @brief Log into the global logger at a throttled rate with the provided log level, format and arguments
     *
     * @param level Log level
     * @param period Time in seconds before the next message should show up
     * @param format Log format
     * @param args Log format arguments
     */
    virtual void log_throttle(
        logger_level_t level, double period, const char* format, va_list args) const noexcept = 0;

    TROLLY_DISALLOW_COPY_AND_MOVE(logger_base);
};

#ifdef __GNUC__
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
__attribute__((unused)) static std::unique_ptr<logger_base> global_logger_;
#else
static std::unique_ptr<logger_base> global_logger_;
#endif

/**
 * @brief Sets the global logger object
 *
 * @param ptr The logger pointer to set
 */
void set_logger(std::unique_ptr<logger_base>&& ptr);

/**
 * @brief Log into the global logger with the provided log level, format and arguments
 * 
 * @param level Log level
 * @param format Log format
 * @param args Log format arguments
 */
void log(logger_level_t level, const char* format, va_list args);

/**
 * @brief Log into the global logger with the provided log level, format and arguments
 *
 * @param level Log level
 * @param format Log format
 * @param ... Log format arguments
 */
void log(logger_level_t level, const char* format, ...);

/**
 * @brief Log into the global logger at a throttled rate with the provided log level, format and arguments
 * 
 * @param level Log level
 * @param period Time in seconds before the next message should show up
 * @param format Log format
 * @param args Log format arguments
 */
void log_throttle(logger_level_t level, double period, const char* format, va_list args);

/**
 * @brief Log into the global logger at a throttled rate with the provided log level, format and arguments
 *
 * @param level Log level
 * @param period Time in seconds before the next message should show up
 * @param format Log format
 * @param ... Log format arguments
 */
void log_throttle(logger_level_t level, double period, const char* format, ...);

}  // namespace trolly::log

#endif
