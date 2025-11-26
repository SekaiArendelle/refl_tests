#pragma once

#include <type_traits>
#include <concepts>
#include <meta>

namespace refl_tests {

inline constexpr struct {
} compile_time_test{};

inline constexpr struct {
} runtime_test{};

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
        if constexpr (not ::std::invocable<decltype([:function_info:])>) {
            continue;
        }
        if constexpr (not ::refl_tests::details::has_runtime_test_annotation(function_info)) {
            continue;
        }
        [:function_info:]();
    }
}

} // namespace refl_tests
