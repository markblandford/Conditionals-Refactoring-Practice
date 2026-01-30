#include "LiftUpConditional.h"
#include "GuardClauses.h"
#include "ApprovalTests.hpp"
#include "doctest/doctest.h"

#include "ExampleConditionals.h"

#include <vector>
#include <tuple>

TEST_CASE("invert_negative") {
    auto data = {
        std::make_tuple(4, 3),
        std::make_tuple(3, 5),
        std::make_tuple(3, 1),
        std::make_tuple(3, 4)
    };
    for (auto [expected, actual] : data) {
        CHECK(ExampleConditionals::invert_negative(actual) == expected);
    }
}

TEST_CASE("invert_positive") {
    auto data = {
        std::make_tuple(4, 3),
        std::make_tuple(3, 5),
        std::make_tuple(3, 1),
        std::make_tuple(3, 4)
    };
    for (auto [expected, actual] : data) {
        CHECK(ExampleConditionals::invert_positive(actual) == expected);
    }
}

TEST_CASE("redundant_else") {
    auto data = {
        std::make_tuple(2, 1),
        std::make_tuple(7, 10),
        std::make_tuple(29, 30),
        std::make_tuple(30, 0)
    };
    for (auto [x, expected] : data) {
        CHECK(ExampleConditionals::redundant_else(x) == expected);
    }
}

TEST_CASE("missing_else") {
    auto data = {
        std::make_tuple(2, 1),
        std::make_tuple(7, 10),
        std::make_tuple(29, 30),
        std::make_tuple(30, 0)
    };
    for (auto [x, expected] : data) {
        CHECK(ExampleConditionals::missing_else(x) == expected);
    }
}

TEST_CASE("deMorganAnd") {
    SUBCASE("true") {
        for (int valid : {5, 7}) {
            CHECK(ExampleConditionals::deMorganAnd(valid) == true);
        }
    }
    SUBCASE("false") {
        for (int invalid : {4, 8}) {
            CHECK(ExampleConditionals::deMorganAnd(invalid) == false);
        }
    }
}

TEST_CASE("deMorganOr") {
    SUBCASE("true") {
        for (int valid : {5, 7}) {
            CHECK(ExampleConditionals::deMorganOr(valid) == true);
        }
    }
    SUBCASE("false") {
        for (int invalid : {4, 8}) {
            CHECK(ExampleConditionals::deMorganOr(invalid) == false);
        }
    }
}

TEST_CASE("join_AND") {
    auto data = {
        std::make_tuple(4, 3, 0),
        std::make_tuple(7, 3, 0),
        std::make_tuple(1, 3, 0),
        std::make_tuple(3, 4, 7),
        std::make_tuple(3, 11, 0)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::join_AND(x, y) == expected);
    }
}

TEST_CASE("split_AND") {
    auto data = {
        std::make_tuple(4, 3, 0),
        std::make_tuple(7, 3, 0),
        std::make_tuple(1, 3, 0),
        std::make_tuple(3, 4, 7),
        std::make_tuple(3, 11, 0)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::split_AND(x, y) == expected);
    }
}

TEST_CASE("join_OR") {
    auto data = {
        std::make_tuple(0, 3, true),
        std::make_tuple(3, 6, true),
        std::make_tuple(-1, 3, true),
        std::make_tuple(-1, 5, false),
        std::make_tuple(-1, 10, true)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::join_OR(x, y) == expected);
    }
}

TEST_CASE("split_OR") {
    auto data = {
        std::make_tuple(0, 3, true),
        std::make_tuple(3, 6, true),
        std::make_tuple(-1, 3, true),
        std::make_tuple(-1, 5, false),
        std::make_tuple(-1, 10, true)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::split_OR(x, y) == expected);
    }
}

TEST_CASE("split_statements") {
    auto data = {
        std::make_tuple(4, 3, 36),
        std::make_tuple(7, 3, 63),
        std::make_tuple(1, 3, 0),
        std::make_tuple(3, 4, 0)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::split_statements(x, y) == expected);
    }
}

TEST_CASE("join_statements") {
    auto data = {
        std::make_tuple(4, 3, 36),
        std::make_tuple(7, 3, 63),
        std::make_tuple(1, 3, 0),
        std::make_tuple(3, 4, 0)
    };
    for (auto [x, y, expected] : data) {
        CHECK(ExampleConditionals::join_statements(x, y) == expected);
    }
}

TEST_CASE("introduce_guard_clause_simple") {
    auto data = {
        std::make_tuple(4, 3, 3),
        std::make_tuple(0, 0, 9)
    };
    for (auto [expectedY, expectedZ, input] : data) {
        GuardClauses guard;
        guard.y = 0;
        guard.z = 0;
        guard.introduce_guard_clause_simple(input);
        CHECK(guard.y == expectedY);
        CHECK(guard.z == expectedZ);
    }
}

TEST_CASE("remove_guard_clause_simple") {
    auto data = {
        std::make_tuple(4, 3, 3),
        std::make_tuple(0, 0, 9)
    };
    for (auto [expectedY, expectedZ, input] : data) {
        GuardClauses guard;
        guard.y = 0;
        guard.z = 0;
        guard.remove_guard_clause_simple(input);
        CHECK(guard.y == expectedY);
        CHECK(guard.z == expectedZ);
    }
}

TEST_CASE("remove_guard_clause_multi_return") {
    auto data = {
        std::make_tuple(0, 3),
        std::make_tuple(40, 9)
    };
    for (auto [expected, input] : data) {
        GuardClauses guard;
        guard.y = 0;
        int result = guard.remove_guard_clause_multi_return(input);
        CHECK(result == expected);
    }
}

TEST_CASE("introduce_guard_clause_multi_return") {
    auto data = {
        std::make_tuple(0, 3),
        std::make_tuple(40, 9)
    };
    for (auto [expected, input] : data) {
        GuardClauses guard;
        guard.y = 0;
        int result = guard.introduce_guard_clause_multi_return(input);
        CHECK(result == expected);
    }
}

TEST_CASE("LiftUpConditionals liftUpA and liftUpB") {
    SUBCASE("A_True_B_True") {
        CHECK(LiftUpConditional::liftUpB(true, true) == "ATrueBTrue");
        CHECK(LiftUpConditional::liftUpA(true, true) == "ATrueBTrue");
    }
    SUBCASE("A_True_B_False") {
        CHECK(LiftUpConditional::liftUpB(true, false) == "ATrueBFalse");
        CHECK(LiftUpConditional::liftUpA(true, false) == "ATrueBFalse");
    }
    SUBCASE("A_False_B_True") {
        CHECK(LiftUpConditional::liftUpB(false, true) == "AFalseBTrue");
        CHECK(LiftUpConditional::liftUpA(false, true) == "AFalseBTrue");
    }
    SUBCASE("A_False_B_False") {
        CHECK(LiftUpConditional::liftUpB(false, false) == "AFalseBFalse");
        CHECK(LiftUpConditional::liftUpA(false, false) == "AFalseBFalse");
    }
}

TEST_CASE("LiftUpConditionals liftUpWorld and liftUpHello") {
    auto data = {
        std::make_tuple("foo",   "world", 0),
        std::make_tuple("foo",   "bar",   1),
        std::make_tuple("bar",   "world", 2),
        std::make_tuple("hello", "bar",   3),
        std::make_tuple("hello", "foo",   4),
        std::make_tuple("hello", "world", 5),
        std::make_tuple("bar",   "foo",   6)
    };
    for (auto [s1, s2, expected] : data) {
        CHECK(LiftUpConditional::liftUpWorld(s1, s2) == expected);
        CHECK(LiftUpConditional::liftUpHello(s1, s2) == expected);
    }
}


