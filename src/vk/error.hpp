#ifndef GUDVIN_DETAIL_INCLUDE_vk_error
#define GUDVIN_DETAIL_INCLUDE_vk_error

#include <system_error>
#include <type_traits>

#include <vulkan/vulkan.h>

namespace gudvin { namespace vk {
///////////////////////////////////////////////////////////////////////////////

static_assert(VK_SUCCESS == 0);

enum class error
{
    out_of_host_memory    = VK_ERROR_OUT_OF_HOST_MEMORY,
    out_of_device_memory  = VK_ERROR_OUT_OF_DEVICE_MEMORY,
    initialization_failed = VK_ERROR_INITIALIZATION_FAILED,
    device_lost           = VK_ERROR_DEVICE_LOST,
    memory_map_failed     = VK_ERROR_MEMORY_MAP_FAILED,
    layer_not_present     = VK_ERROR_LAYER_NOT_PRESENT,
    extension_not_present = VK_ERROR_EXTENSION_NOT_PRESENT,
    feature_not_present   = VK_ERROR_FEATURE_NOT_PRESENT,
    incompatible_driver   = VK_ERROR_INCOMPATIBLE_DRIVER,
    too_many_objects      = VK_ERROR_TOO_MANY_OBJECTS,
    format_not_supported  = VK_ERROR_FORMAT_NOT_SUPPORTED,
    fragmented_pool       = VK_ERROR_FRAGMENTED_POOL,
};

///////////////////////////////////////////////////////////////////////////////
} /* namespace vk */ } /* namespace gudvin */

namespace std {
///////////////////////////////////////////////////////////////////////////////

template <>
struct is_error_code_enum<gudvin::vk::error>
    : true_type
{};

///////////////////////////////////////////////////////////////////////////////
} // namespace std

namespace gudvin { namespace vk {
///////////////////////////////////////////////////////////////////////////////

auto error_category() noexcept
    -> std::error_category const&;

inline auto make_error_code(error e) noexcept
    -> std::error_code
{
    return {static_cast<int>(e), error_category()};
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace vk */ } /* namespace gudvin */

#endif
