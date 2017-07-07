#ifndef GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES
#define GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto enumerate_instance_extension_properties(char const* layer_name)
-> std::vector<VkExtensionProperties>
{
    std::uint32_t item_count;
    check(vkEnumerateInstanceExtensionProperties(
        layer_name, &item_count, nullptr));
    std::vector<VkExtensionProperties> items(item_count);
    check(vkEnumerateInstanceExtensionProperties(
        layer_name, &item_count, items.data()));
    items.resize(item_count);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
