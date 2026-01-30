
#ifndef EXAMPLECONDITIONALS_H
#define EXAMPLECONDITIONALS_H


class ExampleConditionals {
public:
    static int invert_negative(int x);
    static int invert_positive(int x);
    static int redundant_else(int x);
    static int missing_else(int x);
    static bool deMorganAnd(int x);
    static bool deMorganOr(int x);
    static int join_AND(int x, int y);
    static int split_AND(int x, int y);
    static bool join_OR(int x, int y);
    static bool split_OR(int x, int y);
    static int join_statements(int x, int y);
    static int split_statements(int x, int y);
};



#endif //EXAMPLECONDITIONALS_H
