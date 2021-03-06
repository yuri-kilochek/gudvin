#ifndef GUDVIN_INCLUDED_VK_HANDLE
#define GUDVIN_INCLUDED_VK_HANDLE

#include <vulkan/vulkan.h>

#include <utility>
#include <exception>
#include <cassert>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

template <typename ValueType>
struct handle
{
    using value_type = ValueType;

    explicit
    handle(value_type value)
    noexcept
    : value_(value)
    {}

    handle()
    noexcept
    : handle(VK_NULL_HANDLE)
    {}

    friend
    void swap(handle& a, handle& b)
    noexcept
    {
        using std::swap;
        swap(a.value_, b.value_);
    }

    handle(handle const&) = delete;

    handle(handle&& other)
    noexcept
    : handle()
    { swap(*this, other); }

    auto& operator=(handle other)
    noexcept
    {
        swap(*this, other);
        return *this;
    }

    ~handle()
    { assert(!value_); }

    explicit operator bool()
    const noexcept
    { return static_cast<bool>(value_); }

    auto value()
    const noexcept
    { return value_; }

    operator value_type()
    const noexcept
    { return value_; }

    template <typename... Args, std::enable_if_t<
        std::is_constructible_v<handle, Args...>>*...>
    auto reset(Args&&... args)
    noexcept
    { 
        auto value = std::exchange(value_, value_type(VK_NULL_HANDLE));
        *this = handle(std::forward<Args>(args)...);
        return value;
    }

private:
    value_type value_;
};

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
