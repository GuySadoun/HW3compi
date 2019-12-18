//
// Created by guy-pc on 18/12/2019.
//

#include "semantic.h"
using namespace output;

void semantic::binop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if ((a.Exp.isInt() && b.Exp.isInt()) || (a.Exp.isByte() && b.Exp.isByte()))  {
        if (sign == "+") {
            target.Exp.val.integer = a.Exp.val.integer + b.Exp.val.integer;
            target.Exp.type = INT;
        } else if (sign == "-") {
            target.Exp.val.integer = a.Exp.val.integer - b.Exp.val.integer;
            target.Exp.type = INT;
        } else if (sign == "*") {
            target.Exp.val.integer = a.Exp.val.integer * b.Exp.val.integer;
            target.Exp.type = INT;
        } else if (sign == "/") {
            target.Exp.val.integer = a.Exp.val.integer / b.Exp.val.integer;
            target.Exp.type = INT;
        } else {
            string exceptionMessage("binop undefined");
            throw (semErr(exceptionMessage));
        }
    } else
        errorSyn(lineno);
}

void semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.isInt() && b.Exp.isInt()) {
        if (sign == "<") {
            target.Exp.val.boolean = (a.Exp.val.integer < b.Exp.val.integer);
            target.Exp.type = BOOL;
        } else if (sign == "<=") {
            target.Exp.val.boolean = (a.Exp.val.integer <= b.Exp.val.integer);
            target.Exp.type = BOOL;
        } else if (sign == ">") {
            target.Exp.val.boolean = (a.Exp.val.integer > b.Exp.val.integer);
            target.Exp.type = BOOL;
        } else if (sign == ">=") {
            target.Exp.val.boolean = (a.Exp.val.integer >= b.Exp.val.integer);
            target.Exp.type = BOOL;
        } else {
            string exceptionMessage("relop undefined");
            throw (semErr(exceptionMessage));
        }
    } else
        errorSyn(lineno);
}

void semantic::logicop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.isBool() && b.Exp.isBool()) {
        if (sign == "and") {
            target.Exp.val.boolean = (a.Exp.val.boolean && b.Exp.val.boolean);
            target.Exp.type = BOOL;
        } else if (sign == "or") {
            target.Exp.val.boolean = (a.Exp.val.boolean || b.Exp.val.boolean);
            target.Exp.type = BOOL;
        } else if (sign == "not") {
            target.Exp.val.boolean = !a.Exp.val.boolean;
            target.Exp.type = BOOL;
        } else {
            string exceptionMessage("logicop undefined");
            throw (semErr(exceptionMessage));
        }
    } else
        errorSyn(lineno);
}

void semantic::call(Types &target, Types &call, int lineno) {
    target.Exp.type = call.
}

void semantic::bytecheck(Types &target, Types &byte, int lineno) {

}

void semantic::enumdecl(Types &target, string name, string enumValues, int lineno){
    target.Exp.val.boolean = a.Exp.val.boolean && b.Exp.val.boolean;
    target.Exp.type = BOOL;

}

