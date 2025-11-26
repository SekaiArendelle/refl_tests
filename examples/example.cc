#include <cassert> // contract_assert
#include <refl_tests/refl_tests.hh>

namespace unittest {

// unittest 1
[[= ::refl_tests::runtime_test]] void test_example1() noexcept {
    // some test code
    int a = 1;
    int b = 1;
    assert(a == b);
}

void util_function() {
    // some test code
    int a = 1;
    int b = 1;
    assert(a == b);
}

// unittest 2
[[= ::refl_tests::runtime_test]] void test_example2() noexcept {
    // some test code
    int a = 1;
    int b = 1;
    assert(a == b);
}

// The compile_time_test annotation can safely be removed from the code
// because the compiler will execute the code at compile time aggressively.
// Maybe an explicit annotation [[= ::refl_tests::compile_time_test]] here is better?
consteval test_at_compile() noexcept {
    // some test code
    constexpr int a = 1;
    constexpr int b = 1;
    static_assert(a == b);
}

} // namespace unittest

int main() {
    ::refl_tests::launch_all_tests<^^::unittest>();
}
