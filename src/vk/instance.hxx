#ifndef GUDVIN_INCLUDED_VK_INSTANCE
#define GUDVIN_INCLUDED_VK_INSTANCE

#include "handle.hxx"
#include "result.hxx"

#include <vulkan/vulkan.h>

#include <cassert>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

inline
auto create_instance(
    VkInstanceCreateInfo const* info,
    VkAllocationCallbacks const* allocator,
    handle<VkInstance>* instance)
{
    assert(instance);
    VkInstance raw_instance;
    auto result = check(vkCreateInstance(info, allocator, &raw_instance));
    instance->reset(raw_instance);
    return result;
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
