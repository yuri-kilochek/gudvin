#ifndef GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES
#define GUDVIN_INCLUDED_VK_ENUMERATE_INSTANCE_EXTENSION_PROPERTIES

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>
#include <string>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto enumerate_instance_extension_properties(char const* layer_name = nullptr)
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

inline
auto enumerate_instance_extension_properties(std::string const& layer_name)
{ return enumerate_instance_extension_properties(layer_name.data()); }

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
