//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using std::unordered_map;
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
    explicit BasicDeclInfo(int lineNum) : lineNum(lineNum) {}
};

typedef union {
    string str;
    int integer;
    bool boolean;
} Value;

struct Funcs {
    vector<FuncDecl> funcDeclarations;
};

struct EnumType {
    string enumName;

    // the type of enum ID is set to be enumID
    explicit EnumType(const string id) {
        enumName = "enum" + id;
    }

    EnumType() {}
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
    vector<Enumerator> values;
};

struct EnumDecl : BasicDeclInfo {
    EnumType namedType;
    EnumeratorList values;
    EnumDecl(string enumName, EnumeratorList el, int lineNum) : BasicDeclInfo(lineNum) {

    }
};

class Expression : public BasicDeclInfo {

    Value val;
    types type;

public:
    bool isBool() { return type == BOOL; }

    bool isInt() { return type == INT; }

    bool isNumber() { return (type == INT || type == BYTE); }

    bool isByte() { return type == BYTE; }

    bool isString() { return type == STRING; }

    bool isEnum() { return type == ENUM; }

    Value getVal(){

        if( isEnum() ){

        }
        return val;
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
    unordered_map<string, EnumDecl> enumerators;
    Enums() = default;
    void addEnumarator(EnumDecl enumerator) {
        enumerators[enumerator.namedType.enumName] = enumerator;
    }
};

struct Program {
    Enums enumns;
    Funcs funcs;
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
