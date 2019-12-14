//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"

void TableStack::Table::newLine(string name, string type, int off) {
    if (scopeTable.empty()) {
        string exceptionMessage("new line to empty scopeTable");
        throw (TblErr(exceptionMessage));
    }
    scopeTable.push_back(*(new TableEntry(name, type, off)));
}

TableStack::Table::~Table() {
    for (auto entry : scopeTable) {
        delete &entry;
    }
}

bool TableStack::Table::existInTable(string name) {
    for (auto &entry : scopeTable) {
        if (entry.name == name) return true;
    }
    return false;
}

void TableStack::newVar(string name, string type) {
    if (tablesStack.empty()) {
        string exceptionMessage("new var with empty");
        throw (TblErr(exceptionMessage));
    }
    for (auto table : tablesStack) {
        if (table->existInTable(name)) {
            string exceptionMessage("already exist in scopeTable");
            throw (TblErr(exceptionMessage));
        }
    }
    tablesStack.front()->newLine(name, type, offsetStack.getTop());
    offsetStack.incTop();
}

void TableStack::newScope() {
    auto it = tablesStack.begin();
    offsetStack.newScope();
    tablesStack.insert(it, new Table);
}

void TableStack::endScope() {
    if (tablesStack.empty()) {
        string exceptionMessage("end scope with empty stack");
        throw (TblErr(exceptionMessage));
    }
    delete *(tablesStack.begin());
    tablesStack.erase(tablesStack.begin());
    offsetStack.endScope();
}
