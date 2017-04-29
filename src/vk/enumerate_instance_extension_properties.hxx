#ifndef GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_extension_properties
#define GUDVIN_DETAIL_INCLUDE_vk_enumerate_instance_extension_properties

#include "result.hxx"

#include <vulkan/vulkan.h>

#include <system_error>
#include <vector>
#include <new>
#include <string>

namespace gudvin {
namespace vk {
///////////////////////////////////////////////////////////////////////////////

inline auto enumerate_instance_extension_properties(
    std::error_code ec,
    char const* layer_name = nullptr)
noexcept
-> std::vector<VkExtensionProperties>
{
    try {
        uint32_t itemCount;
        ec = vkEnumerateInstanceExtensionProperties(
            layer_name, &itemCount, nullptr);
        if (ec && ec != VK_INCOMPLETE) { return {}; }
        std::vector<VkExtensionProperties> items(itemCount);
        ec = vkEnumerateInstanceExtensionProperties(
            layer_name, &itemCount, items.data());
        if (ec && ec != VK_INCOMPLETE) { return {}; }
        items.resize(itemCount);
        return items;
    } catch (std::bad_alloc const&) {
        ec = make_error_code(std::errc::not_enough_memory);
        return {};
    }
}

inline auto enumerate_instance_extension_properties(
    char const* layer_name = nullptr)
-> std::vector<VkExtensionProperties>
{
    std::error_code ec;
    auto items = enumerate_instance_extension_properties(ec, layer_name);
    if (ec) { throw std::system_error(ec); };
    return items;
}

inline auto enumerate_instance_extension_properties(
    std::error_code& ec,
    std::string const& layer_name)
noexcept
-> std::vector<VkExtensionProperties>
{ return enumerate_instance_extension_properties(ec, layer_name.data()); }

inline auto enumerate_instance_extension_properties(
    std::string const& layer_name)
-> std::vector<VkExtensionProperties>
{ return enumerate_instance_extension_properties(layer_name.data()); }

///////////////////////////////////////////////////////////////////////////////
} // namespace vk
} // namespace gudvin

#endif
