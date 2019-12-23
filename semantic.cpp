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
void print(const string& str) {
    cout << str << endl;
}

void printi(int n) {
    cout << n << endl;
}
//-----------------------------------------------------------------------//

void semantic::binop(Types &target, Types &a, Types &b, const string& sign, int lineno) {
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

void semantic::relop(Types &target, Types &a, Types &b, const string& sign, int lineno) {
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
                    //TODO: repair!!!
                    errorPrototypeMismatch(lineno, arg.id, arg.val.funType.);

            }
        }
    }
    target.exp.type = call.call.returnType;
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
    EnumDecl enumDecl(std::move(name), std::move(enumValues));
    target.enumDecl = enumDecl;
    declared.declaredEnums[enumDecl.namedType] = enumDecl;
}

void semantic::enumeratorlist(Types &target, Types& enumerator, int lineno) {
    EnumeratorList enumList(enumerator.enumerator);
    target.enumeratorList = enumList;
}

void semantic::enumeratorlist(Types &target, Types &enumeratorList, Types& enumerator, int lineno) {
    EnumeratorList enumList(enumerator.enumerator);
    target.enumeratorList = enumList;
}

void semantic::enumType(Types &target, string name, int lineno) {
    EnumType eType(std::move(name));
    target.enumType = eType;
}

void semantic::expList(Types &target, Types &expList, Types &exp) {
    ExpList expList1(expList.expList, exp.exp);
    target.expList = expList1;
}

void semantic::expList(Types &target, Types & expList) {
    ExpList expList1(expList.expList);
    target.expList = expList1;
}

void semantic::callCreate(Types &target, const string& id, Types &expList, int lineno) {
    if (!symbolTable.exist(id)) {
        errorUndefFunc(lineno, id);
        exit(1);
    }
    FuncDecl ret = symbolTable.getFuncVal(id, lineno);
    FormalsList formalList = FormalsList(ret.formals);
    vector<string> strParams = formalList.formalsToStr();

    if (expList.expList.args.size() != formalList.funDeclParams.size()){
        errorPrototypeMismatch(lineno, id, strParams);
        exit(1);
    }
    for (int i = 0; i < expList.expList.args.size(); ++i) {
        if(expList.expList.args.at(i).type != formalList.funDeclParams.at(i).type ){
            errorPrototypeMismatch(lineno, id, strParams);
            exit(1);
        }
    }
    Call call = Call( id, expList.expList );
    target.call = call;
}

void semantic::callCreate(Types &target, const string& id, int lineno) {
    if (!symbolTable.exist(id)){
        errorUndefFunc(lineno, id);
        exit(1);
    }

    Call call = Call( id );
    target.call = call;
}

void semantic::block(Types &target, Types &code) {
    target.statement.code.statements = code.statements.statements;
    symbolTable.endScope();
}

void semantic::varDecl(Types &target, types type, string &id, int lineno) {
    symbolTable.newVar(id, type, )
}








