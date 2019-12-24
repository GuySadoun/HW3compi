//
// Created by guy-pc on 18/12/2019.
//

#ifndef HW3COMPI_SEMANTIC_H
#define HW3COMPI_SEMANTIC_H

#include <string>
#include "hw3_output.hpp"
#include "tableStack.h"
#include "structs.h"


enum ErrorType {
    SUCCESS,
    SYNERR,
    LEXERR,
};

class semErr : public std::exception {
public:
    semErr(const string msg) : m_msg(msg) {}

    const char *what() const noexcept override {
        cout << "semErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }

    const string m_msg;
};

using std::string;
namespace semantic {
    void binop(Types &target, Types &a, Types &b, const string &sign, int lineno);

    void logicop(Types &target, Types &a, Types &b, const string &sign, int lineno);

    void relop(Types &target, Types &a, Types &b, const string &sign, int lineno);

    void cast(Types &target, Types &a, Types &b, int lineno);

    void call(Types &target, Types &call, int lineno);

    void bytecheck(Types &target, Types &byte, int lineno);

    void enumeratorlist(Types &target, Types &enumerator, int lineno);

    void enumeratorlist(Types &target, Types &enumeratorList, Types &enumerator, int lineno);

    void enumdecl(Types &target, string name, EnumeratorList enumValues, int lineno);

    void enumType(Types &target, string name, int lineno);

    void expList(Types &target, Types &exp);

    void expList(Types &target, Types &expList, Types &exp);

    void callCreate(Types &target, const string &id, Types &expList, int lineno);

    void callCreate(Types &target, const string &id, int lineno);

    void block(Types &target, Types &statements);

    void varDecl(Types &target, types type, const string &id, int lineno);

    void enumStatement(Types &target, Types &senum);

    void declAndAssign(Types &target, types type, const string& id, Types &exp, int lineno);

    void enumTypeAssign(Types &target, Types &enumType, const string& id, Types &exp, int lineno);

    void assign(Types &target, string &id, Types &exp, int lineno);

    void ifStatement(Types &target, Types &exp, Types &statement, int lineno);

    void ifElseStatement(Types &target, Types &exp, Types &statement1, Types &statement2, int lineno);

    void whileStatement(Types &target, Types &exp, Types &statement, int lineno);

    void enumVarDeck(Types &target, Types &enumType, const string &str, int lineno);

    void typeVarDec(Types &target, Types &type, const string &str, int lineno);

    void breakContinue(Types &target, bool isContinue, int lineno);

    void formalList(Types &target, Types &decl);

    void formalList(Types &target, Types &decl, Types &list);

    void formals(Types &target, Types &formalsList);

    void funcDecl(Types &target, string &name, Types &retType, Types &formals, Types &statements, int lineno);

    void enumDeclToEnums(Types &target, Types &enums, Types &enumDecl);

    void checkMain();

    void program(Types &target, Types &enums, Types &funcs);
}
#endif //HW3COMPI_SEMANTIC_H
