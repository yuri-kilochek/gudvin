#ifndef GUDVIN_DETAIL_INCLUDE_DEFER
#define GUDVIN_DETAIL_INCLUDE_DEFER

#include <boost/scope_exit.hpp>

#define GUDVIN_DEFER(...) \
    BOOST_SCOPE_EXIT_ALL(&) { __VA_ARGS__; }

#endif
