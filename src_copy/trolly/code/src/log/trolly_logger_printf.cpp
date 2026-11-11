#include "trolly/log/trolly_logger_printf.h"

#include <cstdio>

namespace trolly::log {

void logger_printf::log(logger_level_t level, const char* format, va_list args) const noexcept
{
    char buffer[LOG_PRINTF_VSPRINTF_BUFFER_SIZE];

    if (vsnprintf(buffer, LOG_PRINTF_VSPRINTF_BUFFER_SIZE, format, args) < 0) {
        printf("Error using vsnprintf to write logs");
        return;
    }

    // TODO(Anthony Law): don't have handlers for TRACE and DEBUG
    if (level == LOGGER_LEVEL_INFO) {
        printf("[INFO] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_WARN) {
        printf("[WARN] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_ERROR) {
        printf("[ERROR] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_FATAL) {
        printf("[FATAL] %s\r\n", buffer);
    }
    va_end(args);
}

void logger_printf::log_throttle(
    logger_level_t level, double period, const char* format, va_list args) const noexcept
{
    TROLLY_UNUSED(period);

    char buffer[LOG_PRINTF_VSPRINTF_BUFFER_SIZE];

    if (vsnprintf(buffer, LOG_PRINTF_VSPRINTF_BUFFER_SIZE, format, args) < 0) {
        printf("Error using vsnprintf to write logs");
        return;
    }

    // TODO(Anthony Law): don't have handlers for TRACE and DEBUG
    if (level == LOGGER_LEVEL_INFO) {
        printf("[INFO] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_WARN) {
        printf("[WARN] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_ERROR) {
        printf("[ERROR] %s\r\n", buffer);
    } else if (level == LOGGER_LEVEL_FATAL) {
        printf("[FATAL] %s\r\n", buffer);
    }
    va_end(args);
}

void use_printf_logger() noexcept { set_logger(std::make_unique<logger_printf>()); }

}  // namespace trolly::log
