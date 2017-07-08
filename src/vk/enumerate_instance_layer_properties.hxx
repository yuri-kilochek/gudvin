#ifndef GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_LAYER_PROPERTIES
#define GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_LAYER_PROPERTIES

#include "error.hxx"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto enumerate_instance_layer_properties()
-> std::vector<VkLayerProperties>
{
    std::uint32_t item_count;
    check(vkEnumerateInstanceLayerProperties(&item_count, nullptr));
    std::vector<VkLayerProperties> items(item_count);
    check(vkEnumerateInstanceLayerProperties(&item_count, items.data()));
    items.resize(item_count);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
