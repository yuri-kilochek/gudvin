#ifndef GUDVIN_DETAIL_INCLUDE_vk_allocation_callbacks
#define GUDVIN_DETAIL_INCLUDE_vk_allocation_callbacks

#include <vulkan/vulkan.h>

#include <functional>
#include <cstddef>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

struct allocation_callbacks
: VkAllocationCallbacks
{
    std::function<void*(
        std::size_t size, std::size_t alignment,
        VkSystemAllocationScope scope)> allocation;

    std::function<void*(
        void* original, std::size_t size, std::size_t alignment,
        VkSystemAllocationScope scope)> reallocation;

    std::function<void(void* memory)> free;

    std::function<void(
        std::size_t size,
        VkInternalAllocationType type,
        VkSystemAllocationScope scope)> internal_allocation;

    std::function<void(
        std::size_t size,
        VkInternalAllocationType type,
        VkSystemAllocationScope scope)> internal_free;

    allocation_callbacks()
    : VkAllocationCallbacks()
    { pUserData = this; }

    auto& prepare()
    {
        if (allocation) {
            pfnAllocation = +[](
                void* user_data,
                std::size_t size, std::size_t alignment,
                VkSystemAllocationScope scope)
            noexcept
            -> void*
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                return self.allocation(size, alignment, scope);
            };
        } else if (reallocation) {
            pfnAllocation = +[](
                void* user_data,
                std::size_t size, std::size_t alignment,
                VkSystemAllocationScope scope)
            noexcept
            -> void*
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                return self.reallocation(nullptr, size, alignment, scope);
            };
        } else {
            pfnAllocation = nullptr;
        }

        if (reallocation) {
            pfnReallocation = +[](
                void* user_data,
                void* original, std::size_t size, std::size_t alignment,
                VkSystemAllocationScope scope)
            noexcept
            -> void*
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                return self.reallocation(original, size, alignment, scope);
            };
        } else {
            pfnReallocation = nullptr;
        }

        if (free) {
            pfnFree = +[](void* user_data, void* memory) noexcept
            -> void
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                self.free(memory);
            };
        } else if (reallocation) {
            pfnFree = +[](void* user_data, void* memory) noexcept
            -> void
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                self.reallocation(
                    memory, 0, 1, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE);
            };
        } else {
            pfnFree = nullptr;
        }

        if (internal_allocation) {
            pfnInternalAllocation = +[](
                void* user_data,
                std::size_t size,
                VkInternalAllocationType type,
                VkSystemAllocationScope scope)
            noexcept
            -> void
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                self.internal_allocation(size, type, scope);
            };
        } else {
            pfnInternalAllocation = nullptr;
        }

        if (internal_free) {
            pfnInternalFree = +[](
                void* user_data,
                std::size_t size,
                VkInternalAllocationType type,
                VkSystemAllocationScope scope)
            noexcept
            -> void
            {
                auto& self = *static_cast<allocation_callbacks*>(user_data);
                self.internal_free(size, type, scope);
            };
        } else {
            pfnInternalFree = nullptr;
        }

        return *this;
    }
};

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
