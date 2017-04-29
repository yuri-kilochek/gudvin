#ifndef GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_layer_properties
#define GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_layer_properties

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <system_error>
#include <vector>
#include <new>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto enumerate_instance_layer_properties(std::error_code& ec) noexcept
-> std::vector<VkLayerProperties>
{
    try {
        uint32_t itemCount;
        ec = vkEnumerateInstanceLayerProperties(&itemCount, nullptr);
        if (ec && ec != VK_INCOMPLETE) { return {}; }
        std::vector<VkLayerProperties> items(itemCount);
        ec = vkEnumerateInstanceLayerProperties(&itemCount, items.data());
        if (ec && ec != VK_INCOMPLETE) { return {}; }
        items.resize(itemCount);
        return items;
    } catch (std::bad_alloc const&) {
        ec = make_error_code(std::errc::not_enough_memory);
        return {};
    }
}

inline auto enumerate_instance_layer_properties()
-> std::vector<VkLayerProperties>
{
    std::error_code ec;
    auto items = enumerate_instance_layer_properties(ec);
    if (ec) { throw std::system_error(ec); };
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
