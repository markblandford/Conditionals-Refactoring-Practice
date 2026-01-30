#ifndef REFACTORCONDITIONALS_GUARDCLAUSES_H
#define REFACTORCONDITIONALS_GUARDCLAUSES_H


class GuardClauses {
public:
    int y;
    int z;

    void introduce_guard_clause_simple(int x);
    void remove_guard_clause_simple(int x);
    int introduce_guard_clause_single_return(int x);
    int remove_guard_clause_single_return(int x);
    int introduce_guard_clause_multi_return(int x);
    int remove_guard_clause_multi_return(int x);
};


#endif //REFACTORCONDITIONALS_GUARDCLAUSES_H