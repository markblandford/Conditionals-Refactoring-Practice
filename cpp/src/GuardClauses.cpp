#include "GuardClauses.h"


void GuardClauses::introduce_guard_clause_simple(int x) {
    if (x == 3) {
        y = 4;
        // imagine lots more lines of code here including if statements
        z = x;
    }
}

void GuardClauses::remove_guard_clause_simple(int x) {
    if (x != 3) {
        return;
    }
    y = 4;
    // imagine lots more lines of code here including if statements
    z = x;
}

int GuardClauses::introduce_guard_clause_single_return(int x) {
    int result = 0;
    if (x != 3) {
        y = 4;
        // imagine lots more lines of code here including if statements
        z = x;
        result = 4 * x + y;
    }
    return result;
}

int GuardClauses::remove_guard_clause_single_return(int x) {
    if (x == 3) {
        return 0;
    }

    y = 4;
    // imagine lots more lines of code here including if statements
    z = x;
    return 4 * x + y;
}

int GuardClauses::introduce_guard_clause_multi_return(int x) {
    if (x != 3) {
        y = 4;
        // imagine lots more lines of code here including if statements
        z = x;
        return 4 * x + y;
    } else {
        return 0;
    }
}

int GuardClauses::remove_guard_clause_multi_return(int x) {
    if (x == 3) {
        return 0;
    }
    y = 4;
    // imagine lots more lines of code here including if statements
    z = x;

    return 4 * x + y;
}

