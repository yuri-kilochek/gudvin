#include "error.hpp"

namespace gudvin { namespace vk {
///////////////////////////////////////////////////////////////////////////////

namespace error_detail {
    struct category final
        : std::error_category
    {
        auto name() const noexcept
            -> char const*
            override final
        {
            return "vulkan";
        }

        auto message(int e) const
            -> std::string
            override final
        {
            switch (e) {
                case static_cast<int>(error::out_of_host_memory):
                    return "out of host memory";
                case static_cast<int>(error::out_of_device_memory):
                    return "out of device memory";
                case static_cast<int>(error::initialization_failed):
                    return "initialization failed";
                case static_cast<int>(error::device_lost):
                    return "device lost";
                case static_cast<int>(error::memory_map_failed):
                    return "memory map failed";
                case static_cast<int>(error::layer_not_present):
                    return "layer not present";
                case static_cast<int>(error::extension_not_present):
                    return "extension not present";
                case static_cast<int>(error::feature_not_present):
                    return "feature not present";
                case static_cast<int>(error::incompatible_driver):
                    return "incompatible driver";
                case static_cast<int>(error::too_many_objects):
                    return "too many objects";
                case static_cast<int>(error::format_not_supported):
                    return "format not supported";
                case static_cast<int>(error::fragmented_pool):
                    return "fragmented pool";
                default:
                    throw std::invalid_argument("unknown error");
            }
        }

        auto default_error_condition(int e) const noexcept
            -> std::error_condition
            override final
        {
            switch (e) {
                //case static_cast<int>(error::out_of_host_memory):
                //    return "out of host memory";
                //case static_cast<int>(error::out_of_device_memory):
                //    return "out of device memory";
                //case static_cast<int>(error::initialization_failed):
                //    return "initialization failed";
                //case static_cast<int>(error::device_lost):
                //    return "device lost";
                //case static_cast<int>(error::memory_map_failed):
                //    return "memory map failed";
                //case static_cast<int>(error::layer_not_present):
                //    return "layer not present";
                case static_cast<int>(error::extension_not_present):
                    return std::errc::function_not_supported;
                case static_cast<int>(error::feature_not_present):
                    return std::errc::function_not_supported;
                //case static_cast<int>(error::incompatible_driver):
                //    return "incompatible driver";
                //case static_cast<int>(error::too_many_objects):
                //    return "too many objects";
                //case static_cast<int>(error::format_not_supported):
                //    return "format not supported";
                //case static_cast<int>(error::fragmented_pool):
                //    return "fragmented pool";
                default:
                    return std::error_category::default_error_condition(e);
            }
        }
    };
} // namespace error_detail

auto error_category() noexcept
    -> std::error_category const&
{
    static error_detail::category const category;
    return category;
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace vk */ } /* namespace gudvin */
