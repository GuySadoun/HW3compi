//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

enum types {
    INT, BYTE, BOOL, VOID, STRING, ENUM
};

struct Program;
class Enums;
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

typedef union {
    string str;
    int integer;
    bool boolean;
} Value;


class Enums {
    string name;
    std::vector<string> enumarators;
public:
    explicit Enums(string str) {
        name = "enum" + str;
    }

    string getName() {
        return name;
    }

    void addEnumarator(string enumarator) {
        enumarators.push_back(enumarator);
    }
};

struct Expression : BasicDeclInfo {

    Value val;
    types type;

    bool isBool() { return type == BOOL; }

    bool isInt() { return type == INT; }

    bool inNumber() { return (type == INT || type == BYTE); }

    bool isByte() { return type == BYTE; }

    bool isString() { return type == STRING; }

    bool isEnum() { return type == ENUM; }

    // casting?
};

struct RetType {
    types type;
};

struct Funcs {
    vector<FuncDecl> funcDeclarations;
};

struct Program {
    Enums enumns;
    Funcs funcs;
};

struct EnumType {
    string enumType;

    // the type of enum ID is set to be enumID
    explicit EnumType(const string id) {
        enumType = "enum" + id;
    }
};

struct EnumDecl : BasicDeclInfo {
    EnumType namedType;
    vector<Enumerator> values;
};

struct Enumerator {
    int num;
    string value;
};

struct EnumeratorList {
    vector<Enumerator> values;
};


struct NamedType {
    types type;
    string id;
};

struct ExpList {
    types type;
    vector<Expression> Params;
};

struct Call : BasicDeclInfo {
    // the returned type ?
    string name;
    types type;
    ExpList params;
};


struct Formals : BasicDeclInfo {
    // TODO: what about enums
    vector<NamedType> params;
};

struct FormalDecl : BasicDeclInfo {
    types type;
};

struct FormalsList {
    vector<FormalDecl> FunDeclParams;
};

struct Statement {
    // TODO
};

struct Statements {
    vector<Statement> statements;
};

struct FuncDecl : BasicDeclInfo {
    types retType;
    string name;
    Formals formals;
    Statements statements;
};

typedef union {
    int integer;
    bool boolean;
    types type;
    string str;
    Enums enums;
    Call call;
    Expression Exp;
} Types;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
