//
// Created by guy-pc on 18/12/2019.
//
#include <iostream>
#include <string>
#include <utility>
#include "semantic.h"

using namespace output;
using std::cout;
using std::endl;

//----------------------------builtInFunc--------------------------------//
void print(const string &str) {
    cout << str << endl;
}

void printi(int n) {
    cout << n << endl;
}
//-----------------------------------------------------------------------//

void semantic::binop(Types &target, Types &a, Types &b, const string &sign, int lineno) {
    if (a.exp.isNumber() && b.exp.isNumber()) {
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

void semantic::relop(Types &target, Types &a, Types &b, const string &sign, int lineno) {
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

void semantic::logicop(Types &target, Types &a, Types &b, const string &sign, int lineno) {
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
        for (auto &arg : call.call.args->args) {
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
                    //TODO: repair!!
                    break;
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
    target.exp.val.integer = symbolTable.getEnumIntegerVal(exp.exp.id, lineno);
}

void semantic::enumdecl(Types &target, string name, EnumeratorList enumValues, int lineno) {
    EnumDecl enumDecl(std::move(name), std::move(enumValues));
    target.enumDecl = enumDecl;
    declared.declaredEnums[enumDecl.namedType.name] = enumDecl;
}

void semantic::enumeratorlist(Types &target, Types &enumerator, int lineno) {
    EnumeratorList enumList(enumerator.enumerator);
    target.enumeratorList = enumList;
}

void semantic::enumeratorlist(Types &target, Types &enumeratorList, Types &enumerator, int lineno) {
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

void semantic::expList(Types &target, Types &expList) {
    ExpList expList1(expList.expList);
    target.expList = expList1;
}

void semantic::callCreate(Types &target, const string &id, Types &expList, int lineno) {
    if (!symbolTable.exist(id)) {
        errorUndefFunc(lineno, id);
        exit(1);
    }
    FuncDecl ret = symbolTable.getFuncVal(id, lineno);
    FormalsList formalList = FormalsList(ret.formals.formalList);
    vector<string> strParams = formalList.formalsToStr();

    if (expList.expList.args.size() != formalList.funDeclParams.size()) {
        errorPrototypeMismatch(lineno, id, strParams);
        exit(1);
    }
    for (int i = 0; i < expList.expList.args.size(); ++i) {
        if (expList.expList.args.at(i).type != formalList.funDeclParams.at(i).type) {
            errorPrototypeMismatch(lineno, id, strParams);
            exit(1);
        }
    }
    std::shared_ptr<ExpList> listPtr = make_shared<ExpList>(expList.expList);
    Call call = Call(id, listPtr);
    target.call = call;
}

void semantic::callCreate(Types &target, const string &id, int lineno) {
    if (!symbolTable.exist(id)) {
        errorUndefFunc(lineno, id);
        exit(1);
    }

    Call call = Call(id);
    target.call = call;
}

void semantic::block(Types &target, Types &code) {
    target.statement.code.statements = code.statements.statements;
    symbolTable.endScope();
}

void semantic::varDecl(Types &target, types type, const string &id, int lineno) {
    symbolTable.newDecl(id, type, lineno);
}

void semantic::enumStatement(Types &target, Types &senum) {
    target.enumType = senum.enumType;
}

void semantic::declAndAssign(Types &target, types type, const string& id, Types &exp, int lineno) {
    symbolTable.newVar(id, type, exp, lineno);
    target.exp.id = id;
    switch (type) {
        case INT:
            target.exp.val.integer = exp.exp.val.integer;
            break;
        case BYTE:
            target.exp.val.integer = exp.exp.val.integer;
            break;
        case BOOL:
            target.exp.val.boolean = exp.exp.val.boolean;
            break;
        case STRING:
            target.exp.val.str = exp.exp.val.str;
            break;
        case ENUM:
            target.exp.val.enumType = exp.exp.val.enumType;
            break;
        case FUNC:
            target.exp.val.funType = exp.exp.val.funType;
            break;
    }
    target.exp.type = exp.exp.type;
}

void semantic::enumTypeAssign(Types &target, Types &enumType, const string& id, Types &exp, int lineno) {
    if (declared.declaredEnums.find(enumType.enumDecl.namedType.name) == declared.declaredEnums.end()) {
        errorUndefEnum(lineno, id);
        exit(1);
    } else {
        bool found = false;
        for (auto &it : declared.declaredEnums.find(enumType.enumDecl.namedType.name)->second.values.values) {
            if (it.enumName == id) {
                found = true;
                break;
            }
        }
        if (!found) {
            errorUndefEnumValue(lineno, enumType.enumType.name);
            exit(1);
        }
    }
    symbolTable.newVar(id, enumType.type, exp, lineno);
    target.exp.id = id;
    target.exp.val.enumType = exp.exp.val.enumType;
    target.exp.type = exp.exp.type;
}

void semantic::assign(Types &target, string &id, Types &exp, int lineno) {
    symbolTable.updateSymbolValue(id, exp, lineno);
}

void semantic::ifStatement(Types &target, Types &exp, Types &statement, int lineno) {
    if (!exp.exp.isBool()) {
        errorMismatch(lineno);
        exit(1);
    }
    target.statement.ifStat.cond.val.boolean = exp.exp.val.boolean;
    target.statement.ifStat.cond.type = exp.exp.type;
    target.statement.ifStat.cond.id = exp.exp.id;
    target.statement.ifStat.stat = std::make_shared<Statement>(statement.statement);
}

void semantic::ifElseStatement(Types &target, Types &exp, Types &statement1, Types &statement2, int lineno) {
    if (!exp.exp.isBool()) {
        errorMismatch(lineno);
        exit(1);
    }
    target.statement.ifElseStat.cond.val.boolean = exp.exp.val.boolean;
    target.statement.ifElseStat.cond.type = exp.exp.type;
    target.statement.ifElseStat.cond.id = exp.exp.id;
    target.statement.ifElseStat.statIf = std::make_shared<Statement>(statement1.statement);
    target.statement.ifElseStat.statElse = std::make_shared<Statement>(statement2.statement);
}

void semantic::whileStatement(Types &target, Types &exp, Types &statement, int lineno) {

    if (!exp.exp.isBool()) {
        errorMismatch(lineno);
        exit(1);
    }
    target.statement.whileStat.cond.val.boolean = exp.exp.val.boolean;
    target.statement.whileStat.cond.id = exp.exp.id;
    target.statement.whileStat.cond.type = exp.exp.type;
    target.statement.whileStat.whileScope = std::make_shared<Statement>(statement.statement);
    insideWhile = true;
}

void semantic::breakContinue(Types &target, bool isContinue, int lineno) {
    if (!insideWhile && !isContinue) errorUnexpectedBreak(lineno);
    else if (!insideWhile && isContinue) errorUnexpectedContinue(lineno);
    target.statement.breakStatement = {.line = lineno, .isContinue = isContinue};
}

void semantic::enumVarDeck(Types &target, Types &enumType, const string &str, int lineno) {
    if (declared.declaredEnums.find(enumType.enumType.name) == declared.declaredEnums.end()) {
        errorUndefEnum(lineno, str);
    }
    EnumType enumType1(str);
    target.formalDecl.enumType = enumType1;
    symbolTable.newDecl(str, ENUM, lineno);
}

void semantic::typeVarDec(Types &target, Types &type, const string &str, int lineno) {
    if (symbolTable.exist(str)) {
        errorDef(lineno, str);
    }
    symbolTable.newDecl(str, type.type, lineno);
}

void semantic::formalList(Types &target, Types &decl) {
    FormalsList fl = FormalsList(decl.formalDecl);
    target.formalsList = fl;
}

void semantic::formalList(Types &target, Types &decl, Types &list) {
    FormalsList fl = FormalsList(decl.formalDecl, list.formalsList);
    target.formalsList = fl;
}

void semantic::formals( Types &target, Types &formalsList) {
    Formals formals = Formals( formalsList.formalsList );
    target.formals = formals;
}

void semantic::funcDecl( Types &target, string &name, Types &retType, Types &formals, Types &statements, int lineno) {
    FuncDecl funcDecl = FuncDecl(retType.retType, name, formals.formals, statements.statements);
    symbolTable.newFuncDecl(name, funcDecl, lineno);
    target.funcDecl = funcDecl;
}

void semantic::enumDeclToEnums(Types &target, Types &enums, Types &enumDecl) {
    target.enums.declaredEnums = enums.enums.declaredEnums;
    target.enums.addEnumerator(enumDecl.enumDecl);
}

void semantic::checkMain() {
    if (!symbolTable.exist("main")) {
        errorMainMissing();
    }
}

void semantic::program(Types &target, Types &enums, Types &funcs) {
    target.program.enums = enums.enums;
    target.program.funcs = funcs.funcs;
}
