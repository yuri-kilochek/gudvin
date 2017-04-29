#ifndef GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_layer_properties
#define GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_layer_properties

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <vector>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto enumerate_instance_layer_properties()
-> std::vector<VkLayerProperties>
{
    uint32_t itemCount;
    check(vkEnumerateInstanceLayerProperties(&itemCount, nullptr));
    std::vector<VkLayerProperties> items(itemCount);
    check(vkEnumerateInstanceLayerProperties(&itemCount, items.data()));
    items.resize(itemCount);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
