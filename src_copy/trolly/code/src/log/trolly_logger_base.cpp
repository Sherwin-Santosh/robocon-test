#include "trolly/log/trolly_logger_base.h"

namespace trolly::log {

void set_logger(std::unique_ptr<logger_base>&& ptr) { global_logger_ = std::move(ptr); };

void log(logger_level_t level, const char* format, va_list args)
{
    global_logger_->log(level, format, args);
}

void log(logger_level_t level, const char* format, ...)
{
    va_list args;  // NOLINT(cppcoreguidelines-init-variables)
    va_start(args, format);
    global_logger_->log(level, format, args);
    va_end(args);
}

void log_throttle(logger_level_t level, double period, const char* format, va_list args)
{
    global_logger_->log_throttle(level, period, format, args);
}

void log_throttle(logger_level_t level, double period, const char* format, ...)
{
    va_list args;  // NOLINT(cppcoreguidelines-init-variables)
    va_start(args, format);
    global_logger_->log_throttle(level, period, format, args);
    va_end(args);
}

}  // namespace trolly::log
