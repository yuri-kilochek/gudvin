#ifndef GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES
#define GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <optional>
#include <string>
#include <vector>
#include <cstdint>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto enumerate_instance_extension_properties(
    std::optional<std::string> layer_name = std::nullopt)
-> std::vector<VkExtensionProperties>
{
    auto raw_layer_name = layer_name ? layer_name->data() : nullptr;
    std::uint32_t item_count;
    check(vkEnumerateInstanceExtensionProperties(
        raw_layer_name, &item_count, nullptr));
    std::vector<VkExtensionProperties> items(item_count);
    check(vkEnumerateInstanceExtensionProperties(
        raw_layer_name, &item_count, items.data()));
    items.resize(item_count);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
