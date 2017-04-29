#ifndef GUDVIN_DETAIL_INCLUDE_vk_instance
#define GUDVIN_DETAIL_INCLUDE_vk_instance

#include "result.hxx"
#include "allocation_callbacks.hxx"

#include <vulkan/vulkan.h>
#include <boost/optional.hpp>

#include <string>
#include <unordered_set>
#include <vector>
#include <system_error>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

struct application_info
: VkApplicationInfo
{
    boost::optional<std::string> application_name;
    boost::optional<std::string> engine_name;

    application_info()
    : VkApplicationInfo()
    { sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; }

    auto& prepare()
    {
        if (application_name) {
            pApplicationName = application_name->data();
        } else {
            pApplicationName = nullptr;
        }

        if (engine_name) {
            pEngineName = engine_name->data();
        } else {
            pEngineName = nullptr;
        }

        return *this;
    }
};

struct instance_create_info
: VkInstanceCreateInfo
{
    std::unordered_set<std::string> enabled_layer_names;
    std::unordered_set<std::string> enabled_extension_names;

    instance_create_info()
    : VkInstanceCreateInfo()
    { sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO; }

    auto& prepare()
    {
        raw_enabled_layer_names_.clear();
        raw_enabled_layer_names_.reserve(enabled_layer_names.size());
        for (auto const& name : enabled_layer_names) {
            raw_enabled_layer_names_.emplace_back(name.data());
        }
        enabledLayerCount = raw_enabled_layer_names_.size();
        ppEnabledLayerNames = raw_enabled_layer_names_.data();

        raw_enabled_extension_names_.clear();
        raw_enabled_extension_names_.reserve(enabled_extension_names.size());
        for (auto const& name : enabled_extension_names) {
            raw_enabled_extension_names_.emplace_back(name.data());
        }
        enabledExtensionCount = raw_enabled_extension_names_.size();
        ppEnabledExtensionNames = raw_enabled_extension_names_.data();

        return *this;
    }

private:
    std::vector<char const*> raw_enabled_layer_names_;
    std::vector<char const*> raw_enabled_extension_names_;
};

inline auto create_instance(
    std::error_code& ec,
    VkInstanceCreateInfo const& info,
    VkAllocationCallbacks const* allocation_callbacks = nullptr)
noexcept
-> VkInstance
{
    VkInstance instance;
    ec = vkCreateInstance(&info, allocation_callbacks, &instance);
    if (ec) { instance = VK_NULL_HANDLE; }
    return instance;
}

inline auto create_instance(
    VkInstanceCreateInfo const& info,
    VkAllocationCallbacks const* allocation_callbacks = nullptr)
-> VkInstance
{
    std::error_code ec;
    auto instance = create_instance(ec, info, allocation_callbacks);
    if (ec) { throw std::system_error(ec); }
    return instance;
}

inline void destroy_instance(
    VkInstance instance,
    VkAllocationCallbacks const* allocation_callbacks = nullptr)
noexcept
{ vkDestroyInstance(instance, allocation_callbacks); }

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
