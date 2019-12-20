//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <utility>

using std::string;
using std::vector;
using std::unordered_map;

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

    string enumName;

    // the type of enum ID is set to be enumID
    explicit EnumType(const string id) {
        enumName = "enum" + id;
    }
};
struct Enumerator {
    int index;
    string value;
    string enumName;

    void setType( string type ){
        enumName = type;
    }
};

struct EnumeratorList {
    int index = 0;
    vector<Enumerator> values;
};

struct EnumDecl : BasicDeclInfo {
    EnumType namedType;
    EnumeratorList values;
};

struct Enums {
    unordered_map<string, EnumDecl> enumerators;

    void addEnumarator(EnumDecl enumerator) {
        enumerators[enumerator.namedType.enumName] = enumerator;
    }
};

typedef union {
    string str;
    int integer;
    bool boolean;
    Enumerator enumerator;
} Value;

class Expression : public BasicDeclInfo {

    Value val;
    types type;

public:
    bool isBool() { return type == BOOL; }

    bool isInt() { return type == INT; }

    bool inNumber() { return (type == INT || type == BYTE); }

    bool isByte() { return type == BYTE; }

    bool isString() { return type == STRING; }

    bool isEnum() { return type == ENUM; }

    Value getVal( ){

        if( isEnum() ){

            // the value
            val.enumerator;

            // the type
            Enums.
        }
    }
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
    Call call;
    Expression Exp;
} Types;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
