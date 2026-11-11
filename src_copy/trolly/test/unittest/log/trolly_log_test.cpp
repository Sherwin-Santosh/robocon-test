#include "trolly/log/trolly_logger_macro.h"
#include "trolly/test/trolly_unittest.h"

namespace {

inline constexpr float TEST_PERIOD = 2.0F;

class logger_test : public trolly::log::logger_base {
public:
    explicit logger_test() noexcept = default;

    ~logger_test() noexcept override = default;

    void log(const trolly::log::logger_level_t level, const char* format,
        va_list args) const noexcept override
    {
        TROLLY_EXPECT_EQ(level, trolly::log::logger_level_t::LOGGER_LEVEL_INFO);
        TROLLY_EXPECT_EQ(format, "log: %d %f %s");
        TROLLY_EXPECT_EQ(va_arg(args, int), 1);
        TROLLY_EXPECT_EQ(va_arg(args, double), 2.0);
        TROLLY_EXPECT_EQ(va_arg(args, const char*), "string");
    }

    void log_throttle(const trolly::log::logger_level_t level, const double period,
        const char* format, va_list args) const noexcept override
    {
        TROLLY_EXPECT_EQ(level, trolly::log::logger_level_t::LOGGER_LEVEL_INFO);
        TROLLY_EXPECT_EQ(period, 1.0);
        TROLLY_EXPECT_EQ(format, "log_throttle: %c %u");
        TROLLY_EXPECT_EQ(va_arg(args, int), 'a');
        TROLLY_EXPECT_EQ(va_arg(args, unsigned int), 1);
    }

private:
    TROLLY_DISALLOW_COPY_AND_MOVE(logger_test);
};

}  // namespace

TROLLY_TEST(log_test, polymorphic_logger)
{
    trolly::log::set_logger(std::make_unique<logger_test>());

    TROLLY_INFO("log: %d %f %s", 1, TEST_PERIOD, "string");
    TROLLY_INFO_THROTTLE(1.0, "log_throttle: %c %u", 'a', 1);
}
