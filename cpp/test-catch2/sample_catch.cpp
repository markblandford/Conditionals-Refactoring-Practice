#include "LiftUpConditional.h"
#include "GuardClauses.h"

#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"


#include "ExampleConditionals.h"
#include "LiftUpConditional.h"


TEST_CASE("invert_negative") {
    auto [expected, actual] = GENERATE(table<int, int>({
        {4, 3},
        {3, 5},
        {3, 1},
        {3, 4}
    }));
    REQUIRE(ExampleConditionals::invert_negative(actual) == expected);
}

TEST_CASE("invert_positive") {
    auto [expected, actual] = GENERATE(table<int, int>({
        {4, 3},
        {3, 5},
        {3, 1},
        {3, 4}
    }));
    REQUIRE(ExampleConditionals::invert_positive(actual) == expected);
}

TEST_CASE("redundant_else") {
    auto [x, expected] = GENERATE(table<int, int>({
        {2, 1},
        {7, 10},
        {29, 30},
        {30, 0}
    }));
    REQUIRE(ExampleConditionals::redundant_else(x) == expected);
}

TEST_CASE("missing_else") {
    auto [x, expected] = GENERATE(table<int, int>({
        {2, 1},
        {7, 10},
        {29, 30},
        {30, 0}
    }));
    REQUIRE(ExampleConditionals::missing_else(x) == expected);
}

TEST_CASE("deMorganAnd") {
    SECTION("true") {
        int valid = GENERATE(5, 7);
        REQUIRE(ExampleConditionals::deMorganAnd(valid) == true);
    }
    SECTION("false") {
        int invalid = GENERATE(4, 8);
        REQUIRE(ExampleConditionals::deMorganAnd(invalid) == false);
    }
}

TEST_CASE("deMorganOr") {
    SECTION("true") {
        int valid = GENERATE(5, 7);
        REQUIRE(ExampleConditionals::deMorganOr(valid) == true);
    }
    SECTION("false") {
        int invalid = GENERATE(4, 8);
        REQUIRE(ExampleConditionals::deMorganOr(invalid) == false);
    }
}

TEST_CASE("join_AND") {
    auto [x, y, expected] = GENERATE(table<int, int, int>({
        {4, 3, 0},
        {7, 3, 0},
        {1, 3, 0},
        {3, 4, 7},
        {3, 11, 0}
    }));
    REQUIRE(ExampleConditionals::join_AND(x, y) == expected);
}

TEST_CASE("split_AND") {
    auto [x, y, expected] = GENERATE(table<int, int, int>({
        {4, 3, 0},
        {7, 3, 0},
        {1, 3, 0},
        {3, 4, 7},
        {3, 11, 0}
    }));
    REQUIRE(ExampleConditionals::split_AND(x, y) == expected);
}

TEST_CASE("join_OR") {
    auto [x, y, expected] = GENERATE(table<int, int, bool>({
        {0, 3, true},
        {3, 6, true},
        {-1, 3, true},
        {-1, 5, false},
        {-1, 10, true}
    }));
    REQUIRE(ExampleConditionals::join_OR(x, y) == expected);
}

TEST_CASE("split_OR") {
    auto [x, y, expected] = GENERATE(table<int, int, bool>({
        {0, 3, true},
        {3, 6, true},
        {-1, 3, true},
        {-1, 5, false},
        {-1, 10, true}
    }));
    REQUIRE(ExampleConditionals::split_OR(x, y) == expected);
}

TEST_CASE("split_statements") {
    auto [x, y, expected] = GENERATE(table<int, int, int>({
        {4, 3, 36},
        {7, 3, 63},
        {1, 3, 0},
        {3, 4, 0}
    }));
    REQUIRE(ExampleConditionals::split_statements(x, y) == expected);
}

TEST_CASE("join_statements") {
    auto [x, y, expected] = GENERATE(table<int, int, int>({
        {4, 3, 36},
        {7, 3, 63},
        {1, 3, 0},
        {3, 4, 0}
    }));
    REQUIRE(ExampleConditionals::join_statements(x, y) == expected);
}

TEST_CASE("introduce_guard_clause_simple") {
    auto [expectedY, expectedZ, input] = GENERATE(table<int, int, int>({
        {4, 3, 3},
        {0, 0, 9}
    }));
    GuardClauses guard;
    guard.y = 0;
    guard.z = 0;
    guard.introduce_guard_clause_simple(input);
    REQUIRE(guard.y == expectedY);
    REQUIRE(guard.z == expectedZ);
}

TEST_CASE("remove_guard_clause_simple") {
    auto [expectedY, expectedZ, input] = GENERATE(table<int, int, int>({
        {4, 3, 3},
        {0, 0, 9}
    }));
    GuardClauses guard;
    guard.y = 0;
    guard.z = 0;
    guard.remove_guard_clause_simple(input);
    REQUIRE(guard.y == expectedY);
    REQUIRE(guard.z == expectedZ);
}

TEST_CASE("remove_guard_clause_multi_return") {
    auto [expected, input] = GENERATE(table<int, int>({
        {0, 3},
        {40, 9}
    }));
    GuardClauses guard;
    guard.y = 0;
    int result = guard.remove_guard_clause_multi_return(input);
    REQUIRE(result == expected);
}

TEST_CASE("introduce_guard_clause_multi_return") {
    auto [expected, input] = GENERATE(table<int, int>({
        {0, 3},
        {40, 9}
    }));
    GuardClauses guard;
    guard.y = 0;
    int result = guard.introduce_guard_clause_multi_return(input);
    REQUIRE(result == expected);
}

TEST_CASE("LiftUpConditionals liftUpA and liftUpB") {
    SECTION("A_True_B_True") {
        REQUIRE(LiftUpConditional::liftUpB(true, true) == "ATrueBTrue");
        REQUIRE(LiftUpConditional::liftUpA(true, true) == "ATrueBTrue");
    }
    SECTION("A_True_B_False") {
        REQUIRE(LiftUpConditional::liftUpB(true, false) == "ATrueBFalse");
        REQUIRE(LiftUpConditional::liftUpA(true, false) == "ATrueBFalse");
    }
    SECTION("A_False_B_True") {
        REQUIRE(LiftUpConditional::liftUpB(false, true) == "AFalseBTrue");
        REQUIRE(LiftUpConditional::liftUpA(false, true) == "AFalseBTrue");
    }
    SECTION("A_False_B_False") {
        REQUIRE(LiftUpConditional::liftUpB(false, false) == "AFalseBFalse");
        REQUIRE(LiftUpConditional::liftUpA(false, false) == "AFalseBFalse");
    }
}

TEST_CASE("LiftUpConditionals liftUpWorld and liftUpHello") {
    auto [s1, s2, expected] = GENERATE(table<std::string, std::string, int>({
        {"foo",   "world", 0},
        {"foo",   "bar",   1},
        {"bar",   "world", 2},
        {"hello", "bar",   3},
        {"hello", "foo",   4},
        {"hello", "world", 5},
        {"bar",   "foo",   6},
    }));
    REQUIRE(LiftUpConditional::liftUpWorld(s1, s2) == expected);
    REQUIRE(LiftUpConditional::liftUpHello(s1, s2) == expected);
}
