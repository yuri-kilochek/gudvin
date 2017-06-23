#ifndef GUDVIN_INCLUDED_SCOPE_GUARD
#define GUDVIN_INCLUDED_SCOPE_GUARD

#include <utility>
#include <tuple>
#include <exception>

namespace gudvin {
///////////////////////////////////////////////////////////////////////////////

namespace detail::scope_guard {
    template <typename Fn, typename... Args>
    struct base
    {
        base(Fn&& fn, Args&&... args)
        : fn_(std::forward<Fn>(fn)), args_(std::forward<Args>(args)...)
        {}

    protected:
        void invoke()
        { std::apply(std::forward<Fn>(fn_), std::move(args_)); }

    private:
        Fn fn_; std::tuple<Args...> args_;
    };
} // detail::scope_guard

template <typename... Params>
struct scope_guard
: private detail::scope_guard::base<Params...>
{
    using detail::scope_guard::base<Params...>::base;

    ~scope_guard()
    { this->invoke(); }
};

template <typename... Params>
scope_guard(Params&&...)
-> scope_guard<std::tuple_element_t<
      0, decltype(std::make_tuple(std::declval<Params>()))>...>;

template <typename... Params>
struct scope_guard_ok
: private detail::scope_guard::base<Params...>
{
    using detail::scope_guard::base<Params...>::base;

    ~scope_guard_ok()
    {
        int out_count = std::uncaught_exceptions();
        if (out_count == in_count) { this->invoke(); }
    }

private:
    int in_count = std::uncaught_exceptions();
};

template <typename... Params>
scope_guard_ok(Params&&...)
-> scope_guard_ok<std::tuple_element_t<
      0, decltype(std::make_tuple(std::declval<Params>()))>...>;

template <typename... Params>
struct scope_guard_fail
: private detail::scope_guard::base<Params...>
{
    using detail::scope_guard::base<Params...>::base;

    ~scope_guard_fail()
    {
        int out_count = std::uncaught_exceptions();
        if (out_count > in_count) { this->invoke(); }
    }

private:
    int in_count = std::uncaught_exceptions();
};

template <typename... Params>
scope_guard_fail(Params&&...)
-> scope_guard_fail<std::tuple_element_t<
      0, decltype(std::make_tuple(std::declval<Params>()))>...>;

///////////////////////////////////////////////////////////////////////////////
} // gudvin

#endif
