//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"
void Table::newLine(string name, types type, int off, Types &value) {

    if (scopeTable.empty()) {
        string exceptionMessage("new line to empty scopeTable");
        throw (TblErr(exceptionMessage));
    }

    // TODO no matching member function for call to push_back
    scopeTable.push_back(*(new TableEntry(name, type, off, value )));

}
Table::~Table() {
    for (auto entry : scopeTable) {
        delete &entry;
    }
}

bool Table::existInTable(string name) {
    for (auto &entry : scopeTable) {
        if (entry->name == name) return true;
    }
    return false;
}



void symbolTable::newVar( string symbol, types type, Types & value ) {
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
    tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value );
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

string symbolTable::getStringVal(string symbol) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if(( entry->name == symbol) && (entry->type == STRING )) {
                return entry->val.str;
            }
            else {
                // TODO throw the right exception
                throw (TblErr("error Undefined"));
            }
        }
    }
}

bool symbolTable::getBoolVal(string symbol) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if(( entry->name == symbol) && (entry->type == BOOL)) {
                return entry->val.boolean;
            }
            else {
                // TODO throw the right exception
                throw (TblErr("error Undefined"));
            }
        }
    }
}

int symbolTable::getIntegerVal(string symbol) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if(( entry->name == symbol) && (entry->type == INT )) {
                return entry->val.integer;
            }
            else {
                // TODO throw the right exception
                throw (TblErr("error Undefined"));
            }
        }
    }
}

FuncDecl symbolTable::getFuncVal(string symbol) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if(( entry->name == symbol) && (entry->type == FUNC )) {
                // TODO: add FuncDecl to union types
                return FuncDecl();
                //return entry->val.func;
            }
            else {
                // TODO throw the right exception
                throw (TblErr("error Undefined"));
            }
        }
    }
}

types getType( string symbol){
    return BOOL;
}

void updateSymbolValue( string symbol, Types value ){

}

bool symbolTable::exist(string symbol) {

    // go lifo in the vector, look for the symbol
    bool exists = false;
    for (auto table : tablesStack) {
        if (table->existInTable(symbol))
            exists = true;
    }
    return exists;

}
//Types & symbolTable::findSymbol(string symbol) {
//
//    return getSymbolEntry(symbol).val;
//}
//
//types symbolTable::getType( string symbol){
//    return getSymbolEntry(symbol).type;
//}
//
//void symbolTable::updateSymbolValue( string symbol, Types value ){
//    getSymbolEntry(symbol).val = value;
//}

