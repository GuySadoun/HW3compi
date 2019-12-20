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
    INT, BYTE, BOOL, VOID, STRING, ENUM
};
enum unionHelper {
    Int_type,
    Bool_type,
    Types_type;
    EnumeratorList_type,
    Enumerator_type,
    String_type,
    Call_type,
    Expression_type
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
} Value;

struct Enumerator {
    string value;
    string enumName;
};

struct EnumeratorList {
    unordered_map<string, Enumerator> values;
    EnumeratorList(EnumeratorList elist, Enumerator e) : values(std::move(elist.values)) {
        values[e.enumName] = e;
    }
    EnumeratorList(Enumerator e) {
        values[e.enumName] = e;
    }
};

struct EnumDecl : BasicDeclInfo {
    EnumType namedType;
    EnumeratorList values;
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
};

struct FormalDecl : BasicDeclInfo {
    types type;
};

struct FormalsList {
    vector<FormalDecl> FunDeclParams;
};

struct Statement {
    statType statType;
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

union Types {
    struct {
        unionHelper h;
        int i;
    } integer;
    struct {
        unionHelper h;
        bool b;
    } boolean;
    struct {
        unionHelper h;
        types t;
    } type;
    struct {
        unionHelper h;
        EnumeratorList el;
    } enumeratorList;
    struct {
        unionHelper h;
        Enumerator e;
    } numerator;
    struct {
        unionHelper h;
        string s;
    } str;
    struct {
        unionHelper h;
        Call c;
    } call;
    struct {
        unionHelper h;
        Expression exp;
    } Exp;
    types (types const& other) {
        // This is safe.
        switch (other.integer.h) {
            case Int_type:   ::new(&i) auto(other.i); break;
            case Bool_type:  ::new(&f) auto(other.f); break;
            case EnumeratorList_type: ::new(&s) auto(other.el); break;
            case Enumerator_type: ::new(&s) auto(other.e); break;
            case String_type: ::new(&s) auto(other.s); break;
            case Call_type: ::new(&s) auto(other.c); break;
            case Expression_type: ::new(&s) auto(other.exp); break;
        }
    }
};

Int_type,
Bool_type,
Types_type;
EnumeratorList_type,
Enumerator_type,
String_type,
Call_type,
Expression_type
extern Enums declared;
extern symbolTable symbolTable;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
