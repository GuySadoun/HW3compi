//
// Created by guy-pc on 14/12/2019.
//

#include "offsetStack.h"

OffsetStack(){
    this.current = -1;
    default;
}
void OffsetStack::incTop() {
    this->current++;
    this->offsetStack.pop(this->current);
    this->offsetStack.push(this->current);
}

int OffsetStack::getTop(){
    this->offsetStack.top();
}

int OffsetStack::endScope(){
    this->offsetStack.pop();
}

void OffsetStack::dupAndAddTop() {
    this->offsetStack.

}

