#ifndef GUDVIN_INCLUDED_VK_HANDLE
#define GUDVIN_INCLUDED_VK_HANDLE

#include <vulkan/vulkan.h>

#include <utility>
#include <exception>
#include <type_traits>

namespace gudvin::vk {
///////////////////////////////////////////////////////////////////////////////

template <typename Value>
struct handle
{
    using value_type = Value;

    explicit
    handle(Value value)
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
    { if (value_) { std::terminate(); } }

    explicit operator bool()
    const noexcept
    { return static_cast<bool>(value_); }

    auto value()
    const noexcept
    { return value_; }

    template <typename... Args, std::enable_if_t<
        std::is_constructible_v<handle, Args...>>*...>
    auto reset(Args&&... args)
    noexcept
    { 
        auto value = std::exchange(value_, Value(VK_NULL_HANDLE));
        *this = handle(std::forward<Args>(args)...);
        return value;
    }

private:
    Value value_;
};

///////////////////////////////////////////////////////////////////////////////
} // gudvin::vk

#endif
