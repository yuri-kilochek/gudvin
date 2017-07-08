#ifndef GUDVIN_INCLUDED_VK_INSTANCE
#define GUDVIN_INCLUDED_VK_INSTANCE

#include "handle.hxx"
#include "error.hxx"

#include <vulkan/vulkan.h>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto create_instance(
    VkInstanceCreateInfo const* info,
    VkAllocationCallbacks const* allocator)
-> handle<VkInstance>
{
    VkInstance handle_value;
    check(vkCreateInstance(info, allocator, &handle_value));
    return handle(handle_value);
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
