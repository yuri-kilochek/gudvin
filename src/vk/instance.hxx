#ifndef GUDVIN_INCLUDED_VK_INSTANCE
#define GUDVIN_INCLUDED_VK_INSTANCE

#include "result.hxx"
#include "handle.hxx"

#include <vulkan/vulkan.h>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto create_instance(
    VkInstanceCreateInfo const* info,
    VkAllocationCallbacks const* allocator)
{
    VkInstance instance;
    check(vkCreateInstance(info, allocator, &instance));
    return handle<VkInstance>(instance);
}

inline
void destroy_instance(
    handle<VkInstance>& instance, VkAllocationCallbacks const* allocator)
noexcept
{ vkDestroyInstance(instance.reset(), allocator); }

inline
void destroy_instance(
    handle<VkInstance>&& instance, VkAllocationCallbacks const* allocator)
noexcept
{ destroy_instance(instance, allocator); }

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
