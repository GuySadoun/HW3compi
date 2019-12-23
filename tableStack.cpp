//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"
#include <utility>

using namespace output;
void Table::newLine(string name, types type, int off, const Types& value) {
    scopeTable.insert( scopeTable.begin(),
            new TableEntry(std::move(name), type, typeToStr(type, value), off, value));
}

Table::~Table() {
    for (auto entry : scopeTable) {
        delete &entry;
    }
}

bool Table::existInTable(const string& name) {
    for (auto &entry : scopeTable) {
        if (entry->name == name) return true;
    }
    return false;
}

string Table::typeToStr(types type, const Types& value) {

    string typeStr;
    switch (type) {
        case INT:
            typeStr = "int";
            break;
        case BYTE:
            typeStr = "int";
            break;
        case BOOL:
            typeStr = "bool";
            break;
        case STRING:
            typeStr = "string";
            break;
        case ENUM:
            typeStr = value.enumDecl.namedType;
            break;
        case FUNC:
            string retVal = typeToStr( value.funcDecl.retType, value.funcDecl.statements );
            typeStr = output::makeFunctionType( retVal, value.funcDecl.formals.formalList.formalsToStr());
            break;
        case VOID:
            typeStr = "void";
            break;

    }
    return typeStr;
}


void symbolTable::newScope() {
    auto it = tablesStack.begin();
    offsetStack.newScope();
    tablesStack.insert(it, new Table);
}

void symbolTable::endScope() {

    if (tablesStack.empty()) {
        //TODO is it possible to end scope which was not open?
    }

    delete *(tablesStack.begin());
    tablesStack.erase(tablesStack.begin());
    offsetStack.endScope();
}

void symbolTable::newVar(const string& symbol, types type, Types &value, int lineNum) {
    if (exist(symbol)) {
        errorDef(lineNum, symbol);
        exit(1);
    }
    tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value);
    offsetStack.incTop();
}

void symbolTable::updateSymbolValue(const string& symbol, const Types& value, int lineNum) {
    int found = 0;
    for (auto table : tablesStack) {
        if (table->existInTable(symbol)) {
            found = 1;
            for (auto entry : table->scopeTable) {
                if (entry->name == symbol) {
                    switch (entry->type) {
                        case INT:
                            entry->val.integer = value.integer;
                            break;
                        case BYTE:
                            entry->val.integer = value.integer;
                            break;
                        case BOOL:
                            entry->val.boolean = value.boolean;
                            break;
                        case STRING:
                            entry->val.str = value.str;
                            break;
                        case ENUM:
                            entry->val.enumDecl = value.enumDecl;
                            break;
                        case FUNC:
                            errorSyn(lineNum);
                            break;
                        case VOID:
                            break;
                    }
                }
            }
        }
    }
    if (!found) {
        errorUndef(lineNum, symbol);
        exit(1);
    }
}

string symbolTable::getStringVal(const string& symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol) && (entry->type == STRING)) {
                return entry->val.str;
            }
        }
    }
    output::errorUndef( lineNum, symbol );
    exit(1);
}

bool symbolTable::getBoolVal(const string& symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol) && (entry->type == BOOL)) {
                return entry->val.boolean;
            }
        }
    }
    output::errorUndef( lineNum, symbol );
    exit(1);
}

int symbolTable::getIntegerVal(const string& symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol) && (entry->type == INT)) {
                return entry->val.integer;
            }
        }
    }
    output::errorUndef( lineNum, symbol );
    exit(1);
}

FuncDecl symbolTable::getFuncVal(const string& symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if (entry->name == symbol) {
                return entry->val.funcDecl;
            }
        }
    }
    output::errorUndefFunc( lineNum, symbol );
    exit(1);
}

bool symbolTable::exist(const string& symbol) {

    // go lifo in the vector, look for the symbol
    bool exists = false;
    for (auto table : tablesStack) {
        if (table->existInTable(symbol))
            exists = true;
    }
    return exists;

}

void symbolTable::newDecl(const string &symbol, types type, int lineNum) {
    if (exist(symbol)){
        errorDef(lineNum, symbol);
        exit(1);
    }
    Types t;
    tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), t);
    offsetStack.incTop();
}

