//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_OFFSETSTACK_H
#define HW3COMPI_OFFSETSTACK_H

#include <string>
#include <stack>

using std::string;
using std::stack;

class OffsetStack {
    stack<int> offsetStack;
public:
    void incFirst();
    void dupAndAddTop();
};

#endif //HW3COMPI_OFFSETSTACK_H
