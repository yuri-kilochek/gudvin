#ifndef GUDVIN_DETAIL_INCLUDE_vk_result
#define GUDVIN_DETAIL_INCLUDE_vk_result

#include <system_error>
#include <type_traits>
#include <string>

#include <vulkan/vulkan.h>

namespace std {
///////////////////////////////////////////////////////////////////////////////

template <>
struct is_error_code_enum<::VkResult>
: true_type
{};

///////////////////////////////////////////////////////////////////////////////
} // namespace std


namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto result_category() noexcept
-> std::error_category const&
{
    static struct final
    : std::error_category
    {
        auto name() const noexcept
        -> char const*
        override final
        { return "vulkan"; }

        auto message(int result) const
        -> std::string
        override final
        {
            switch (result) {
            case VK_ERROR_OUT_OF_HOST_MEMORY:
                return "Out of host memory";
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return "Out of device memory";
            case VK_ERROR_INITIALIZATION_FAILED:
                return "Initialization failed";
            case VK_ERROR_DEVICE_LOST:
                return "Device lost";
            case VK_ERROR_MEMORY_MAP_FAILED:
                return "Memory map failed";
            case VK_ERROR_LAYER_NOT_PRESENT:
                return "Layer not present";
            case VK_ERROR_EXTENSION_NOT_PRESENT:
                return "Extension not present";
            case VK_ERROR_FEATURE_NOT_PRESENT:
                return "Feature not present";
            case VK_ERROR_INCOMPATIBLE_DRIVER:
                return "Incompatible driver";
            case VK_ERROR_TOO_MANY_OBJECTS:
                return "Too many objects";
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                return "Format not supported";
            case VK_ERROR_FRAGMENTED_POOL:
                return "Fragmented pool";
            default:
                return "Unknown error " + std::to_string(result); 
            }
        }

        auto default_error_condition(int result) const noexcept
        -> std::error_condition
        override final
        {
            switch (result) {
            case VK_ERROR_OUT_OF_HOST_MEMORY:
            case VK_ERROR_OUT_OF_DEVICE_MEMORY:
                return std::errc::not_enough_memory;
            case VK_ERROR_LAYER_NOT_PRESENT:
            case VK_ERROR_EXTENSION_NOT_PRESENT:
            case VK_ERROR_FEATURE_NOT_PRESENT:
            case VK_ERROR_INCOMPATIBLE_DRIVER:
            case VK_ERROR_FORMAT_NOT_SUPPORTED:
                return std::errc::not_supported;
            default:
                return error_category::default_error_condition(result);
            }
        }
    } const instance;
    return instance;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin


inline auto make_error_code(VkResult result) noexcept
-> std::error_code
{ return {result, gudvin::vk::result_category()}; }

inline auto make_error_condition(VkResult result) noexcept
-> std::error_condition
{ return {result, gudvin::vk::result_category()}; }

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto check(VkResult result)
-> VkResult
{
    if (result < 0) { throw std::system_error(result); }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
