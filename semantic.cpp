//
// Created by guy-pc on 18/12/2019.
//

#include "semantic.h"
using namespace output;

void semantic::binop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if(a.Exp.isBool() && b.Exp.isBool()) {
        target.Exp.val.boolean = a.Exp.val.boolean && b.Exp.val.boolean;
        target.Exp.type = BOOL;
    } else
        errorSyn(lineno);
}

void semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if ((a.Exp.isInt() && b.Exp.isInt()) || (a.Exp.isByte() && b.Exp.isByte())) {
        target.Exp.type = BOOL;
        target.Exp.val.boolean = (a.Exp.val.boolean == b.Exp.val.boolean);
    } else
        errorSyn(lineno);
}

void semantic::logicop(Types &target, Types &a, Types &b, string sign, int lineno) {

}

void semantic::call(Types &target, Types &call, int lineno) {

}

