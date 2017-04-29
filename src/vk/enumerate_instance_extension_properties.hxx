#ifndef GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_extension_properties
#define GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_extension_properties

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <vector>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto enumerate_instance_extension_properties(
    char const* layer_name = nullptr)
-> std::vector<VkExtensionProperties>
{
    uint32_t itemCount;
    check(vkEnumerateInstanceExtensionProperties(
        layer_name, &itemCount, nullptr));
    std::vector<VkExtensionProperties> items(itemCount);
    check(vkEnumerateInstanceExtensionProperties(
        layer_name, &itemCount, items.data()));
    items.resize(itemCount);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
