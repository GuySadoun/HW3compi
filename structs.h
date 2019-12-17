//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <vector>
#include <iostream>

using std::string;

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

class Expression {
public:
    Value val;
    string name;
    types type;

    bool isBool() return type == BOOL;
    bool isInt() return type == INT;
    bool isByte() return type == BYTE;
    bool isString() return type == STRING;
    bool isEnum() return type == ENUM;
};

struct Call {
    string ID;
    types type;
    vector<Expression> params;
};


typedef union {
    int integer;
    bool boolean;
    string str;
    EnumClass enumClass;
    Expression Exp;

} Types;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
