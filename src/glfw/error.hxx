#ifndef GUDVIN_INCLUDED_GLFW_ERROR
#define GUDVIN_INCLUDED_GLFW_ERROR

#include <GLFW/glfw3.h>
#include <boost/config.hpp>

#include <system_error>
#include <stdexcept>
#include <string>
#include <exception>
#include <cassert>
#include <utility>

namespace gudvin::glfw {
///////////////////////////////////////////////////////////////////////////////

inline
auto error_category()
noexcept
-> std::error_category const&
{
    static
    struct final
    : std::error_category
    {
        auto name()
        const noexcept
        -> char const*
        override final
        { return "glfw"; }

        auto message(int value)
        const
        -> std::string
        override final
        {
            switch (value) {
                case GLFW_NOT_INITIALIZED:
                    return "not initialized";
                case GLFW_NO_CURRENT_CONTEXT:
                    return "no current context";
                case GLFW_INVALID_ENUM:
                    return "invalid enum";
                case GLFW_INVALID_VALUE:
                    return "invalid value";
                case GLFW_OUT_OF_MEMORY:
                    return "out of memory";
                case GLFW_API_UNAVAILABLE:
                    return "api unavailable";
                case GLFW_VERSION_UNAVAILABLE:
                    return "version unavailable";
                case GLFW_PLATFORM_ERROR:
                    return "platform error";
                case GLFW_FORMAT_UNAVAILABLE:
                    return "format unavailable";
                case GLFW_NO_WINDOW_CONTEXT:
                    return "no window context";
                default:
                    throw std::domain_error(
                        "unknown error code: " + std::to_string(value)); 
            }
        }

        auto default_error_condition(int value)
        const noexcept
        -> std::error_condition
        override final
        {
            switch (value) {
                case GLFW_INVALID_ENUM:
                case GLFW_INVALID_VALUE:
                    return std::errc::invalid_argument;
                case GLFW_OUT_OF_MEMORY:
                    return std::errc::not_enough_memory;
                case GLFW_API_UNAVAILABLE:
                case GLFW_VERSION_UNAVAILABLE:
                case GLFW_FORMAT_UNAVAILABLE:
                    return std::errc::not_supported;
                default:
                    return error_category::default_error_condition(value);
            }
        }
    } const instance;
    return instance;
}

inline
auto make_error_code(int value)
noexcept
-> std::error_code
{ return {value, error_category()}; }

inline
auto make_error_condition(int value)
noexcept
-> std::error_condition
{ return {value, error_category()}; }

namespace detail::error {
    inline
    auto& latest()
    noexcept
    {
        thread_local
        std::exception_ptr instance = nullptr;
        return instance;
    }
} // detail::error

inline
void ensure_error_callback_is_set()
noexcept
{
    static
    char const dummy = (glfwSetErrorCallback(
        +[](int value, char const* description) noexcept {
            assert(value);
            assert(description);
            try {
                throw std::system_error(value, error_category(), description);
            } catch (...) {
                auto& latest = detail::error::latest();
                assert(!latest && "previous error not handled");
                latest = std::current_exception();
            }
        }), 0);
    (void)dummy;
}

namespace detail::error {
    inline char const dummy = (ensure_error_callback_is_set(), 0);
} // detail::error

inline
void check_error()
{
    auto& latest = detail::error::latest();
    if (BOOST_LIKELY(!latest)) { return; }
    std::rethrow_exception(std::exchange(latest, nullptr));
}

inline
void suppress_error()
noexcept
{ detail::error::latest() = nullptr; }

///////////////////////////////////////////////////////////////////////////////
} // gudvin::glfw

#endif
