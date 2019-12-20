//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"

void symbolTable::Table::newLine(string name, string type, int off) {
    if (scopeTable.empty()) {
        string exceptionMessage("new line to empty scopeTable");
        throw (TblErr(exceptionMessage));
    }
    scopeTable.push_back(*(new TableEntry(name, type, off)));
}

symbolTable::Table::~Table() {
    for (auto entry : scopeTable) {
        delete &entry;
    }
}

bool symbolTable::Table::existInTable(string name) {
    for (auto &entry : scopeTable) {
        if (entry.name == name) return true;
    }
    return false;
}

Table::TableEntry Table::getEntryfromScope(string name) {

    for (auto &entry : scopeTable) {
        if (entry.name == name) return entry;
    }
   // TODO if entry not found
}


Table::TableEntry symbolTable::getSymbolEntry (string symbol){


    for (auto table : tablesStack) {
        if (table->existInTable(symbol)) {
            return table->getEntryfromScope(symbol);
        }
    }
}

void symbolTable::newVar( string symbol, string type, Types value ) {
    if (tablesStack.empty()) {
        string exceptionMessage("new var with empty");
        throw (TblErr(exceptionMessage));
    }
    for (auto table : tablesStack) {
        if (table->existInTable(symbol)) {
            string exceptionMessage("already exist in scopeTable");
            throw (TblErr(exceptionMessage));
        }
    }
    tablesStack.front()->newLine(symbol, type, offsetStack.getTop());
    offsetStack.incTop();
}

void symbolTable::newScope() {
    auto it = tablesStack.begin();
    offsetStack.newScope();
    tablesStack.insert(it, new Table);
}

void symbolTable::endScope() {
    if (tablesStack.empty()) {
        string exceptionMessage("end scope with empty stack");
        throw (TblErr(exceptionMessage));
    }
    delete *(tablesStack.begin());
    tablesStack.erase(tablesStack.begin());
    offsetStack.endScope();
}

bool symbolTable::exist(string str) {
    // go lifo in the vector, look for the symbol

    return false;
}

string symbolTable::findStringSymbol(string symbol) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {

        }
    }
}

Table::TableEntry *symbolTable::getEntry(string symbol) {
    return nullptr;
}

Types symbolTable::findSymbol(string symbol) {

    //getSymbolEntry
    Types result;
    return result;
}

types getType( string symbol){
    return BOOL;
}

void updateSymbolValue( string symbol, Types value ){

}

bool exist(string symbol){

}

TableEntry getSymbolEntry( string name ){
    for (auto table : tablesStack) {
    }
}

