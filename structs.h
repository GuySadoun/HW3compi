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

enum types {INT, BYTE, BOOL, VOID, STRING, ENUM};

class EnumClass {
    string name;
    std::vector<string> enumarators;
public:
    EnumClass(string str) {
        name = "enum" + str;
    }
    string getName() {
        return name;
    }
    void addEnumarator(string enumarator) {
        enumarators.push_back(enumarator);
    }
};

typedef union{
    string str;
    int integer;
    bool boolean;
}Value;

struct Expression {

    Value val;
    types type;
    int lineNum;

    bool isBool() { return type == BOOL; }
    bool isInt() { return type == INT; }
    bool isByte() { return type == BYTE; }
    bool isString() { return type == STRING; }
    bool isEnum() { return type == ENUM; }
};

struct NamedExpression : Expression {
    string ID;
};

struct Named{
    string ID;
};

struct NamedType : Named{
    types type;
};


struct ExpList {
    types type;
    vector<string> names;
};

struct Call {
    string ID;
    types type;
    vector<Expression> params;
};


struct Formals{
    // TODO: what about enums
    vector<NamedType> params;
};

struct Statement{
    // TODO
};

struct Statements{
    vector<Statement> statements;
};

struct FuncDecl {
    types retType;
    string ID;
    Formals formals;
    Statements statements;

};

typedef union {
    int integer;
    bool boolean;
    types type;
    string str;
    EnumClass enumClass;
    Call call;
    Expression Exp;
    NamedExpression NamedExp;

} Types;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
