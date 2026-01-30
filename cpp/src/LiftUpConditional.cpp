#include "LiftUpConditional.h"

std::string LiftUpConditional::liftUpB(bool a, bool b) {
    if (a) {
        if (b) {
            return aTrueBTrue();
        } else {
            return aTrueBFalse();
        }
    } else {
        if (b) {
            return aFalseBTrue();
        } else {
            return aFalseBFalse();
        }
    }
}

std::string LiftUpConditional::liftUpA(bool a, bool b) {
    if (b) {
        if (a) {
            return aTrueBTrue();
        } else {
            return aFalseBTrue();
        }
    } else {
        if (a) {
            return aTrueBFalse();
        } else {
            return aFalseBFalse();
        }
    }
}

int LiftUpConditional::liftUpWorld(std::string s1, std::string s2) {
    if (s1 != "hello") {
        if (s2 != "world") {
            if (s1 != "foo") {
                return 6;
            }
            return 1;
        } else if (s1 != "foo") {
            return 2;
        }
    } else {
        if (s2 == "bar") {
            return 3;
        } else if (s2 != "world") {
            return 4;
        }
        return 5;
    }
    return 0;
}

int LiftUpConditional::liftUpHello(std::string s1, std::string s2) {
    if (s2 == "world") {
        if (s1 != "hello") {
            if (s1 != "foo") {
                return 2;
            }
        } else {
            return 5;
        }
        return 0;
    } else {
        if (s1 != "hello") {
            if (s1 != "foo") {
                return 6;
            }
            return 1;
        } else {
            if (s2 == "bar") {
                return 3;
            } else {
                return 4;
            }
        }
    }
}

std::string LiftUpConditional::aFalseBFalse() {
    return "AFalseBFalse";
}

std::string LiftUpConditional::aFalseBTrue() {
    return "AFalseBTrue";
}

std::string LiftUpConditional::aTrueBFalse() {
    return "ATrueBFalse";
}

std::string LiftUpConditional::aTrueBTrue() {
    return "ATrueBTrue";
}