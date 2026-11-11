/**
 * @file trolly_logger_printf.h
 * @author Fernando (ferrrnnnandochen@gmail.com)
 * @brief Logger implementation using printf
 * @version 0.1
 * @date 2023-11-05
 *
 * @copyright Copyright (c) 2023 HKU Robocon Team
 *
 */

#ifndef TROLLY_LOGGER_PRINTF_H
#define TROLLY_LOGGER_PRINTF_H

#include "trolly/log/trolly_logger_base.h"

namespace trolly::log {

inline constexpr size_t LOG_PRINTF_VSPRINTF_BUFFER_SIZE = 256;

/**
 * @brief Logger implementation using printf
 *
 */
class logger_printf : public logger_base {
public:
    explicit logger_printf() noexcept = default;

    ~logger_printf() noexcept override = default;

    void log(logger_level_t level, const char* format, va_list args) const noexcept override;

    void log_throttle(logger_level_t level, double period, const char* format,
        va_list args) const noexcept override;

private:
    TROLLY_DISALLOW_COPY_AND_MOVE(logger_printf);
};

void use_printf_logger() noexcept;

}  // namespace trolly::log

#endif
