#ifndef REFACTORCONDITIONALS_LIFTUPCONDITIONAL_H
#define REFACTORCONDITIONALS_LIFTUPCONDITIONAL_H


#include <string>

class LiftUpConditional {
public:
    static std::string liftUpB(bool a, bool b);
    static std::string liftUpA(bool a, bool b);
    static int liftUpWorld(std::string s1, std::string s2);
    static int liftUpHello(std::string s1, std::string s2);

private:
    static std::string aFalseBFalse();
    static std::string aFalseBTrue();
    static std::string aTrueBFalse();
    static std::string aTrueBTrue();
};


#endif //REFACTORCONDITIONALS_LIFTUPCONDITIONAL_H