//
// Created by guy-pc on 18/12/2019.
//

#include "semantic.h"
using namespace output;

void semantic::binop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.inNumber() && b.Exp.inNumber())  {
        if (sign == "+") {
            target.Exp.val.integer = a.Exp.val.integer + b.Exp.val.integer;
        } else if (sign == "-") {
            target.Exp.val.integer = a.Exp.val.integer - b.Exp.val.integer;
        } else if (sign == "*") {
            target.Exp.val.integer = a.Exp.val.integer * b.Exp.val.integer;
        } else if (sign == "/") {
            target.Exp.val.integer = a.Exp.val.integer / b.Exp.val.integer;
        } else {
            string exceptionMessage("binop undefined");
            throw (semErr(exceptionMessage));
        }
        if (a.Exp.isInt() || b.Exp.isInt()) target.Exp.type = INT;
        else target.Exp.type = BYTE;
    } else {
        errorSyn(lineno);
    }
}

void semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.isInt() && b.Exp.isInt()) {
        if (sign == "<") {
            target.Exp.val.boolean = (a.Exp.val.integer < b.Exp.val.integer);
        } else if (sign == "<=") {
            target.Exp.val.boolean = (a.Exp.val.integer <= b.Exp.val.integer);
        } else if (sign == ">") {
            target.Exp.val.boolean = (a.Exp.val.integer > b.Exp.val.integer);
        } else if (sign == ">=") {
            target.Exp.val.boolean = (a.Exp.val.integer >= b.Exp.val.integer);
        } else {
            string exceptionMessage("relop undefined");
            throw (semErr(exceptionMessage));
        }
    } else {
        errorSyn(lineno);
    }
    target.Exp.type = BOOL;
}

void semantic::logicop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.isBool() && b.Exp.isBool()) {
        if (sign == "and") {
            target.Exp.val.boolean = (a.Exp.val.boolean && b.Exp.val.boolean);
        } else if (sign == "or") {
            target.Exp.val.boolean = (a.Exp.val.boolean || b.Exp.val.boolean);
        } else if (sign == "not") {
            target.Exp.val.boolean = !a.Exp.val.boolean;
        } else {
            string exceptionMessage("logicop undefined");
            throw (semErr(exceptionMessage));
        }
    } else {
        errorSyn(lineno);
    }
    target.Exp.type = BOOL;
}

void semantic::call(Types &target, Types &call, int lineno) {
    if (call.call.name == "print") {
        for (auto &str : call.call.params.Params) {
            
        }
    }
    target.Exp.type = call.call.type;
    target.Exp.lineNum = call.call.lineNum;
}

void semantic::bytecheck(Types &target, Types &byte, int lineno) {

}

void semantic::cast(Types &target, Types &a, Types &b, string sign, int lineno) {

}

void semantic::enumdecl( Types &target, string name, EnumeratorList enumValues, int lineno){
    //target.Exp.type( EnumType( name )),
    //target.Exp.values = enumValues;
}

void semantic::enumeratorlist( Types &target, Enumerator name, int lineno ){

}





