//
// Created by guy-pc on 18/12/2019.
//
#include <iostream>
#include <string>
#include "semantic.h"
#include "structs.h"

using namespace output;
using std::cout;
using std::endl;

//----------------------------builtInFunc--------------------------------//
void print(string str) {
    cout << str << endl;
}

void printi(int n) {
    cout << n << endl;
}
//-----------------------------------------------------------------------//

void semantic::binop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.exp.isNumber() && b.Exp.exp.isNumber())  {
        if (sign == "+") {
            target.Exp.exp.val.integer = a.Exp.exp.val.integer + b.Exp.exp.val.integer;
        } else if (sign == "-") {
            target.Exp.exp.val.integer = a.Exp.exp.val.integer - b.Exp.exp.val.integer;
        } else if (sign == "*") {
            target.Exp.exp.val.integer = a.Exp.exp.val.integer * b.Exp.exp.val.integer;
        } else if (sign == "/") {
            target.Exp.exp.val.integer = a.Exp.exp.val.integer / b.Exp.exp.val.integer;
        } else {
            string exceptionMessage("binop undefined");
            throw (semErr(exceptionMessage));
        }
        if (a.Exp.exp.isInt() || b.Exp.exp.isInt()) target.Exp.exp.type = INT;
        else target.Exp.exp.type = BYTE;
    } else {
        errorSyn(lineno);
    }
}

void semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.exp.isNumber() && b.Exp.exp.isNumber()) {
        if (sign == "<") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.integer < b.Exp.exp.val.integer);
        } else if (sign == "<=") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.integer <= b.Exp.exp.val.integer);
        } else if (sign == ">") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.integer > b.Exp.exp.val.integer);
        } else if (sign == ">=") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.integer >= b.Exp.exp.val.integer);
        } else {
            string exceptionMessage("relop undefined");
            throw (semErr(exceptionMessage));
        }
        target.Exp.exp.type = BOOL;
    } else {
        errorSyn(lineno);
    }
}

void semantic::logicop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.Exp.exp.isBool() && b.Exp.exp.isBool()) {
        if (sign == "and") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.boolean && b.Exp.exp.val.boolean);
        } else if (sign == "or") {
            target.Exp.exp.val.boolean = (a.Exp.exp.val.boolean || b.Exp.exp.val.boolean);
        } else if (sign == "not") {
            target.Exp.exp.val.boolean = !a.Exp.exp.val.boolean;
        } else {
            string exceptionMessage("logicop undefined");
            throw (semErr(exceptionMessage));
        }
    } else {
        errorSyn(lineno);
    }
    target.Exp.exp.type = BOOL;
}

void semantic::call(Types &target, Types &call, int lineno) {
    if (call.call.c.name == "print") {
        for (auto &str : call.call.c.params.Params) {
            
        }
    }
    target.Exp.exp.type = call.call.c.type;
    target.Exp.exp.lineNum = call.call.c.lineNum;
}

void semantic::bytecheck(Types &target, Types &byte, int lineno) {
    if (byte.integer.i > 255) errorByteTooLarge(lineno, std::to_string(byte.integer.i));
    target.Exp.exp.val.integer = byte.integer.i;
    target.Exp.exp.type = BYTE;
}

void semantic::cast(Types &target, Types &to, Types &exp, int lineno) {
    if (exp.Exp.exp.type != ENUM || to.type.t != INT) {
        errorMismatch(lineno);
        exit(1);
    }
    if (!symbolTable.exist(exp.Exp.exp.id)) {
        errorDef(lineno, exp.Exp.exp.id);
        exit(1);
    }
    target.Exp.exp.type = INT;
    target.Exp.exp.val.integer = symbolTable.findSymbol(exp.Exp.exp.id).integer;

}

void semantic::enumdecl( Types &target, string name, EnumeratorList enumValues, int lineno){
    //target.Exp.type( EnumType( name )),
    //target.Exp.values = enumValues;
}

void semantic::enumeratorlist1(Types &target, Types& enumerator, int lineno) {
    target.enumeratorList(enumerator);
}

void semantic::enumeratorlist2(Types &target, Types &enumeratorList, Types& enumerator, int lineno) {
    target.enumeratorList(enumeratorList, enumerator);
}





