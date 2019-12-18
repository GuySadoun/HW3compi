//
// Created by guy-pc on 18/12/2019.
//

#include "semantic.h"
using namespace output;

ErrorType semantic::binop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if(a.Exp.isBool() && b.Exp.isBool()) {
        target.Exp.val.boolean = a.Exp.val.boolean && b.Exp.val.boolean;
        target.Exp.type = BOOL;
    } else
        errorSyn(lineno);
}

ErrorType semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if ((a.Exp.type == INT && b.Exp.type == INT) || (a.Exp.type == BYTE && b.Exp.type == BYTE) {
        target.type = BOOL;
        target.val = (a.Exp.val == b.Exp.val);
    } else
        errorSyn(yylineno);
}
