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
    if (a.Exp.isNumber() && b.Exp.isNumber())  {
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
    if (a.Exp.isNumber() && b.Exp.isNumber()) {
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
        target.Exp.type = BOOL;
    } else {
        errorSyn(lineno);
    }
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
    if (byte.integer > 255) errorByteTooLarge(lineno, std::to_string(byte.integer));
    target.Exp.val.integer = byte.integer;
    target.Exp.type = BYTE;
}

void semantic::cast(Types &target, Types &to, Types &exp, int lineno) {
    if (exp.Exp.type != ENUM || to.type != INT) {
        errorMismatch(lineno);
        exit(1);
    }
    if (!symbolTable.exist(exp.Exp.id)) {
        errorDef(lineno, exp.Exp.id);
        exit(1);
    }
    if (symbolTable.getType(exp.Exp.id) != )
    target.Exp.type = INT;
    target.Exp.val.integer = symbolTable.findSymbol(exp.Exp.id).integer;

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





