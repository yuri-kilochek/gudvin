#ifndef GUDVIN_INCLUDED_VK_ENUMERATE_PHYSICAL_DEVICES
#define GUDVIN_INCLUDED_VK_ENUMERATE_PHYSICAL_DEVICES

#include "error.hxx"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto enumerate_physical_devices(VkInstance instance)
-> std::vector<VkPhysicalDevice>
{
    std::uint32_t item_count;
    check(vkEnumeratePhysicalDevices(instance, &item_count, nullptr));
    std::vector<VkPhysicalDevice> items(item_count);
    check(vkEnumeratePhysicalDevices(instance, &item_count, items.data()));
    items.resize(item_count);
    return items;
}

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
