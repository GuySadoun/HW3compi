//
// Created by guy-pc on 18/12/2019.
//

#ifndef HW3COMPI_SEMANTIC_H
#define HW3COMPI_SEMANTIC_H

#include <string>
#include "structs.h"
#include "hw3_output.hpp"
enum ErrorType {
    SUCCESS,
    SYNERR,
    LEXERR,
};

class semErr : public std::exception {
public:
    semErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "semErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

using std::string;
namespace semantic {
    void binop(Types& target, Types &a, Types &b, string sign, int lineno);
    void logicop(Types& target, Types &a, Types &b, string sign, int lineno);
    void relop(Types& target, Types &a, Types &b, string sign, int lineno);
    void cast(Types& target, Types &a, Types &b, string sign, int lineno);
    void call(Types& target, Types &call, int lineno);
    void bytecheck(Types& target, Types &byte, int lineno);
}
#endif //HW3COMPI_SEMANTIC_H
