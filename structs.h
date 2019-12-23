//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "tableStack.h"

using std::unordered_map;
using std::string;
using std::vector;

enum types {
    INT, BYTE, BOOL, VOID, STRING, ENUM, FUNC, UNDEF
};

enum statType {
    DECL, FLOW, LOOP, SCOPE, ASSIGN
};


struct Program;
struct Enums;
struct Funcs;
struct FuncDecl;
struct EnumDecl;
struct RetType;
struct Formals;
struct FormalsList;
struct FormalDecl;
struct EnumeratorList;
struct Enumerator;
struct Statements;
struct Statement;
struct Call;
struct ExpList;
struct EnumType;
struct Expression;
struct EnumType;

struct BasicDeclInfo {
    int lineNum;
};

struct Funcs {
    vector<FuncDecl> funcDeclarations;
};

struct Flow{
    types retType;
};

struct EnumType {
    string name;
    // the type of enum ID is set to be enumID
    explicit EnumType(const string id) {
        name = "enum" + id;
    }
};

typedef union {
    string str;
    int integer;
    bool boolean;
    EnumType enumType;
    Call funType;
} Value;

struct Enumerator {
    string value;
    string enumName;
};

struct EnumeratorList {
    unordered_map<string, Enumerator> values;

    EnumeratorList(Enumerator e) {
        this->values[e.enumName] = e;
    }

    EnumeratorList(EnumeratorList elist, Enumerator e) : values(elist.values) {
        this->values[e.enumName] = e;
    }
};

struct EnumDecl : BasicDeclInfo {
    EnumType namedType;
    EnumeratorList values;

    EnumDecl(string name, EnumeratorList vals) {
        namedType = EnumType(name);
        values = vals;
    }
};

struct Expression : BasicDeclInfo {

    Value val;
    string id;
    types type;

    bool isBool() { return type == BOOL; }

    bool isInt() { return type == INT; }

    bool isNumber() { return (type == INT || type == BYTE); }

    bool isByte() { return type == BYTE; }

    bool isString() { return type == STRING; }

    bool isEnum() { return type == ENUM; }

};

struct ExpList {
    vector<Expression> args;

    ExpList(ExpList expList, Expression exp) : args(expList.args) {
        this->args.push_back(exp);
    }
    ExpList(Expression exp) {
        this->args.push_back(exp);
    }
};

struct Call : BasicDeclInfo {
    // the returned type ?
    string name;
    ExpList args;
    types returnType;

    Call( string id, ExpList expList) : args(expList), name(id) {}
    Call( string id): name(id){}
};

struct Formals : BasicDeclInfo {
    FormalsList formalList;
};

struct FormalDecl : BasicDeclInfo {
    types type;
    EnumType enumType;
    string id;
};

struct FormalsList {
    vector<FormalDecl> funDeclParams;

    FormalsList( FormalDecl formalDecl, FormalsList list) : funDeclParams(list.funDeclParams ) {
        this->funDeclParams.push_back(formalDecl);
    }
    FormalsList( FormalDecl formalDecl ){
        this->funDeclParams.push_back(formalDecl);
    }

    vector<string> formalsToStr() {
        vector<string> ret;
        for ( auto formalDecl : funDeclParams ) {
            ret.insert( ret.begin(), formalDecl.type );
        }
        return ret;
    }
};

struct Statement {
    statType statType;
    Statements code;
    FormalDecl formalDecl;
    EnumType enumType;
    EnumDecl enumDecl;
    Expression exp;
    Call call;
};

struct Statements {
    vector<Statement> statements;
};

struct RetType {
    types type;
};

struct FuncDecl : BasicDeclInfo {
    types retType;
    string name;
    Formals formals;
    Statements statements;
};

struct Enums {
    unordered_map<EnumType, EnumDecl> declaredEnums;

    Enums() = default;

    void addEnumerator(EnumDecl enumerator) {
        declaredEnums[enumerator.namedType] = enumerator;
    }
};

struct Program {
    Enums enums;
    Funcs funcs;
};

typedef union {
    int integer;
    bool boolean;
    types type;
    EnumeratorList enumeratorList;
    Enumerator enumerator;
    string str;
    Call call;
    Expression exp;
    EnumDecl enumDecl;
    EnumType enumType;
    ExpList expList;
    FuncDecl funcDecl;
    Funcs funcs;
    Enums enums;
    RetType retType;
    Formals formals;
    FormalsList formalsList;
    FormalDecl formalDecl;
    Statements statements;
    Statement statement;
} Types;

extern Enums declared;
extern symbolTable symbolTable;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
