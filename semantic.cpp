//
// Created by guy-pc on 18/12/2019.
//
#include <iostream>
#include <string>
#include <utility>
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
    if (a.exp.isNumber() && b.exp.isNumber())  {
        if (sign == "+") {
            target.exp.val.integer = a.exp.val.integer + b.exp.val.integer;
        } else if (sign == "-") {
            target.exp.val.integer = a.exp.val.integer - b.exp.val.integer;
        } else if (sign == "*") {
            target.exp.val.integer = a.exp.val.integer * b.exp.val.integer;
        } else if (sign == "/") {
            target.exp.val.integer = a.exp.val.integer / b.exp.val.integer;
        } else {
            string exceptionMessage("binop undefined");
            throw (semErr(exceptionMessage));
        }
        if (a.exp.isInt() || b.exp.isInt()) target.exp.type = INT;
        else target.exp.type = BYTE;
    } else {
        errorSyn(lineno);
    }
}

void semantic::relop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.exp.isNumber() && b.exp.isNumber()) {
        if (sign == "<") {
            target.exp.val.boolean = (a.exp.val.integer < b.exp.val.integer);
        } else if (sign == "<=") {
            target.exp.val.boolean = (a.exp.val.integer <= b.exp.val.integer);
        } else if (sign == ">") {
            target.exp.val.boolean = (a.exp.val.integer > b.exp.val.integer);
        } else if (sign == ">=") {
            target.exp.val.boolean = (a.exp.val.integer >= b.exp.val.integer);
        } else {
            string exceptionMessage("relop undefined");
            throw (semErr(exceptionMessage));
        }
        target.exp.type = BOOL;
    } else {
        errorSyn(lineno);
    }
}

void semantic::logicop(Types &target, Types &a, Types &b, string sign, int lineno) {
    if (a.exp.isBool() && b.exp.isBool()) {
        if (sign == "and") {
            target.exp.val.boolean = (a.exp.val.boolean && b.exp.val.boolean);
        } else if (sign == "or") {
            target.exp.val.boolean = (a.exp.val.boolean || b.exp.val.boolean);
        } else if (sign == "not") {
            target.exp.val.boolean = !a.exp.val.boolean;
        } else {
            string exceptionMessage("logicop undefined");
            throw (semErr(exceptionMessage));
        }
    } else {
        errorSyn(lineno);
    }
    target.exp.type = BOOL;
}

void semantic::call(Types &target, Types &call, int lineno) {
    if (call.call.name == "print") {
        for (auto &arg : call.call.args.args) {
            switch (arg.type) {
                case INT:
                    cout << arg.val.integer;
                    break;
                case BYTE:
                    cout << arg.val.integer;
                    break;
                case BOOL:
                    cout << arg.val.boolean;
                    break;
                case VOID:
                    break;
                case STRING:
                    cout << arg.val.str;
                    break;
                case ENUM:
                    cout << arg.val.enumType.name;
                    break;
                case FUNC:
                    errorPrototypeMismatch(lineno, arg.id, arg.val.funType.);

            }
        }
    }
    target.exp.type = call.call.type;
    target.exp.lineNum = call.call.lineNum;
}

void semantic::bytecheck(Types &target, Types &byte, int lineno) {
    if (byte.integer > 255) errorByteTooLarge(lineno, std::to_string(byte.integer));
    target.exp.val.integer = byte.integer;
    target.exp.type = BYTE;
}

void semantic::cast(Types &target, Types &to, Types &exp, int lineno) {
    if (exp.exp.type != ENUM || to.type != INT) {
        errorMismatch(lineno);
        exit(1);
    }
    if (!symbolTable.exist(exp.exp.id)) {
        errorDef(lineno, exp.exp.id);
        exit(1);
    }
    target.exp.type = INT;
    target.exp.val.integer = symbolTable.getIntegerVal(exp.exp.id);
}

void semantic::enumdecl( Types &target, string name, EnumeratorList enumValues, int lineno){
    EnumDecl enumDecl(std::move(name), enumValues);
    target.enumDecl = enumDecl;
    declared.declaredEnums[enumDecl.namedType] = enumDecl;
}

void semantic::enumeratorlist1(Types &target, Types& enumerator, int lineno) {
    EnumeratorList enumList(enumerator.enumerator);
    target.enumeratorList = enumList;
}

void semantic::enumeratorlist2(Types &target, Types &enumeratorList, Types& enumerator, int lineno) {
    EnumeratorList enumList(enumerator.enumerator);
    target.enumeratorList = enumList;
}

void semantic::enumType(Types &target, string name, int lineno) {
    EnumType eType(std::move(name));
    target.enumType = eType;
}







