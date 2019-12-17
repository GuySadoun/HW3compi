//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <vector>
#include <iostream>

using std::string;

enum type {INT, BYTE, BOOL, VOID};

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

struct exp {
    int val;
    string name;
};

class TypeClass {
    type t;
public:
    TypeClass(type type) {
        t = type;
    }
};

typedef union {
    int integer;
    char singlechar;
    string str;
    EnumClass enumClass;
    TypeClass typeClass;
    exp EXP;
} Types;

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
