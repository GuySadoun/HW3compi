//
// Created by guy-pc on 14/12/2019.
//
#include "offsetStack.h"

void OffsetStack::incTop() {

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }

    current++;
    offsetStack.pop();
    offsetStack.push(current);
}

int OffsetStack::getTop(){

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }
    return offsetStack.top();
}

void OffsetStack::endScope(){

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }
    offsetStack.pop();
}

void OffsetStack::newScope() {
    offsetStack.push( current );
}

