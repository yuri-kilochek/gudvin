#ifndef GUDVIN_INCLUDED_VK_ERROR
#define GUDVIN_INCLUDED_VK_ERROR

#include <vulkan/vulkan.h>
#include <boost/config.hpp>

#include <system_error>
#include <stdexcept>
#include <string>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto error_category()
noexcept
-> std::error_category const&
{
    static struct final
    : std::error_category
    {
        auto name()
        const noexcept
        -> char const*
        override final
        { return "vulkan"; }

        auto message(int value)
        const
        -> std::string
        override final
        {
            switch (value) {
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                    return "out of host memory";
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    return "out of device memory";
                case VK_ERROR_INITIALIZATION_FAILED:
                    return "initialization failed";
                case VK_ERROR_DEVICE_LOST:
                    return "device lost";
                case VK_ERROR_MEMORY_MAP_FAILED:
                    return "memory map failed";
                case VK_ERROR_LAYER_NOT_PRESENT:
                    return "layer not present";
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                    return "extension not present";
                case VK_ERROR_FEATURE_NOT_PRESENT:
                    return "feature not present";
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                    return "incompatible driver";
                case VK_ERROR_TOO_MANY_OBJECTS:
                    return "too many objects";
                case VK_ERROR_FORMAT_NOT_SUPPORTED:
                    return "format not supported";
                case VK_ERROR_FRAGMENTED_POOL:
                    return "fragmented pool";
                case VK_ERROR_SURFACE_LOST_KHR:
                    return "surface lost";
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                    return "native window in use";
                case VK_ERROR_OUT_OF_DATE_KHR:
                    return "out of date";
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                    return "incompatible display";
                case VK_ERROR_VALIDATION_FAILED_EXT:
                    return "validation failed";
                case VK_ERROR_INVALID_SHADER_NV:
                    return "invalid shader";
                case VK_ERROR_OUT_OF_POOL_MEMORY_KHR:
                    return "out of pool memory";
                case VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX:
                    return "invalid external handle";
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
                case VK_ERROR_OUT_OF_HOST_MEMORY:
                case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                    return std::errc::not_enough_memory;
                case VK_ERROR_LAYER_NOT_PRESENT:
                case VK_ERROR_EXTENSION_NOT_PRESENT:
                case VK_ERROR_FEATURE_NOT_PRESENT:
                case VK_ERROR_INCOMPATIBLE_DRIVER:
                case VK_ERROR_FORMAT_NOT_SUPPORTED:
                    return std::errc::not_supported;
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
                    return std::errc::device_or_resource_busy;
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
                    return std::errc::not_supported;
                case VK_ERROR_OUT_OF_POOL_MEMORY_KHR:
                    return std::errc::not_enough_memory;
                case VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX:
                    return std::errc::invalid_argument;
                default:
                    return error_category::default_error_condition(value);
            }
        }
    } const instance;
    return instance;
}

inline
auto make_error_code(VkResult result)
noexcept
-> std::error_code
{ return {result, error_category()}; }

inline
auto make_error_condition(VkResult result)
noexcept
-> std::error_condition
{ return {result, error_category()}; }

inline
auto check(VkResult result)
-> VkResult
{
    if (BOOST_UNLIKELY(result < 0)) {
        throw std::system_error(result, error_category());
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
