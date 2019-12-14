//
// Created by guy-pc on 14/12/2019.
//
#include "offsetStack.h"

void OffsetStack::incTop() {

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }

    this->current++;
    this->offsetStack.pop();
    this->offsetStack.push(this->current);
}

int OffsetStack::getTop(){

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }
    return this->offsetStack.top();
}

void OffsetStack::endScope(){

    if (offsetStack.empty()) {
        string exceptionMessage("Table is empty");
        throw (OffsetErr(exceptionMessage));
    }
    offsetStack.pop();
}

void OffsetStack::newScope() {
    this->offsetStack.push( this->current );
}

