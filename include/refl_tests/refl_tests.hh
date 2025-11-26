#pragma once

#include <type_traits>
#include <meta>

namespace refl_tests {

// TODO can I detect whether a test function have been marked with consteval e.t.c.
// This may no need to do anything
inline constexpr struct {
} compile_time_test{};

inline constexpr struct {
} runtime_test{};

template<typename Func>
concept is_valid_runtime_test = ::std::is_function_v<Func> && requires(Func&& func) { func(); };

namespace details {

consteval auto has_runtime_test_annotation(::std::meta::info function_info) noexcept -> bool {
    template for (constexpr auto annotation : ::std::meta::annotations_of(function_info)) {
        if constexpr (::std::meta::type_of(annotation) == ::std::meta::type_of(::refl_tests::runtime_test)) {
            return true;
        }
    }
    return false;
}

} // namespace details

template<::std::meta::info namespace_info>
    requires (::std::meta::is_namespace(namespace_info))
consteval void launch_all_tests() /* noexcept( noexcept([:function_info:]) && ... ) */ {
    template for (constexpr auto function_info :
                  ::std::meta::members_of(namespace_info, ::std::meta::access_context::current())) {
        if constexpr (not ::refl_tests::is_valid_runtime_test<decltype([:function_info:])>) {
            continue;
        }
        if constexpr (not ::refl_tests::details::has_runtime_test_annotation(function_info)) {
            continue;
        }
        [:function_info:]();
    }
}

} // namespace refl_tests
