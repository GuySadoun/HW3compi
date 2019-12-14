//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"

void TableStack::Table::newLine(string name, string type, int off) {

}

void TableStack::Table::removeTopTable() {

}

void TableStack::newVar(string name, string type, int off) {
    if (tablesStuck.empty()) {
        string exceptionMessage("new var with empty string");
        throw (TblErr(exceptionMessage));
    }
    tablesStuck.top.newLine(name, type, off);
}

void TableStack::newScope() {

}

void TableStack::endScope() {

}
