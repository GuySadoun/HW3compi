//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_OFFSETSTACK_H
#define HW3COMPI_OFFSETSTACK_H

#include <iostream>
#include <string>
#include <stack>

using std::string;
using std::stack;


class OffsetErr : public std::exception {
public:
    OffsetErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "OffsetErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class OffsetStack {
    stack<int> offsetStack;
    int current;
public:
    OffsetStack() = default;
    void incTop();
    int getTop();
    void endScope();
    void newScope();
};

#endif //HW3COMPI_OFFSETSTACK_H
