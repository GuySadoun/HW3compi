//
// Created by guy-pc on 14/12/2019.
//

#include "tableStack.h"
Enums declared;
class symbolTable symbolTable;
bool insideWhile;

using namespace output;

void Table::newLine(const string &name, types type, int off, int value) {
    scopeTable.insert(scopeTable.begin(),
                      new TableEntry(name, type, symbolTable::typeToStr(type), off, value));
}

void Table::newLine(const string &name, types type, int off, bool value) {
    scopeTable.insert(scopeTable.begin(),
                      new TableEntry(name, type, symbolTable::typeToStr(type), off, value));
}

void Table::newLine(const string &name, types type, int off, const EnumType& value) {
    scopeTable.insert(scopeTable.begin(),
                      new TableEntry(value.name, type, symbolTable::typeToStr(ENUM), off, value));
}

void Table::newLine(const string &name, types type, int off) {
    scopeTable.insert(scopeTable.begin(),
                      new TableEntry(name, type, symbolTable::typeToStr(ENUM), off));
}

void Table::newLineForFunc(const string &name,  int off, FuncDecl& value) {
    string typeName = value.toStr();
    scopeTable.insert(scopeTable.begin(),
                      new TableEntry(name, FUNC, typeName, off, value));
}

Table::~Table() {
    for (auto entry : scopeTable) {
        delete &entry;
    }
}

bool Table::existInTable(const string &name) {
    for (auto &entry : scopeTable) {
        if (entry->name == name) return true;
    }
    return false;
}

void symbolTable::checkTableEmpty(const string &expMessage) {
    if (tablesStack.empty()) {
        //TODO
    }
}

void symbolTable::newScope() {
    auto it = tablesStack.begin();
    offsetStack.newScope();
    tablesStack.insert(it, new Table);
}

void symbolTable::endScope() {

    checkTableEmpty("end scope with empty stack exception");

    delete *(tablesStack.begin());
    tablesStack.erase(tablesStack.begin());
    offsetStack.endScope();
}

void symbolTable::newVar(const string &symbol, types type, Types &value, int lineNum) {
    if (exist(symbol)) {
        errorDef(lineNum, symbol);
        exit(1);
    }
    switch (type) {
        case INT:
            tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value.integer);
            break;
        case BYTE:
            tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value.integer);
            break;
        case BOOL:
            tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value.boolean);
            break;
        case ENUM:
            tablesStack.front()->newLine(symbol, type, offsetStack.getTop(), value.enumType);
            break;
        default:
            break;
    }
    offsetStack.incTop();
}

void symbolTable::updateSymbolValue(const string &symbol, const Types &value, int lineNum) {
    int found = 0;
    for (auto table : tablesStack) {
        if (table->existInTable(symbol)) {
            found = 1;
            for (auto entry : table->scopeTable) {
                if (entry->name == symbol) {
                    switch (entry->type) {
                        case INT:
                            entry->val->integer = value.integer;
                            break;
                        case BYTE:
                            entry->val->integer = value.integer;
                            break;
                        case BOOL:
                            entry->val->boolean = value.boolean;
                            break;
                        case STRING:
                            entry->val->str = value.str;
                            break;
                        case ENUM:
                            entry->val->enumDecl = value.enumDecl;
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

string symbolTable::getStringVal(const string &symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol) && (entry->type == STRING)) {
                return entry->val->str;
            }
        }
    }
    output::errorUndef(lineNum, symbol);
    exit(1);
}

bool symbolTable::getBoolVal(const string &symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol) && (entry->type == BOOL)) {
                return entry->val->boolean;
            }
        }
    }
    output::errorUndef(lineNum, symbol);
    exit(1);
}

int symbolTable::getEnumIntegerVal(const string &symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol)) {
                for (int i = 0; i < entry->val->enumDecl.values.values.size(); ++i) {
                    if (entry->val->enumDecl.values.values.at(i).enumName == symbol) {
                        return i;
                    }
                }
            }
        }
    }
    output::errorUndef(lineNum, symbol);
    exit(1);
}

FuncDecl symbolTable::getFuncVal(const string &symbol, int lineNum) {
    for (auto table : tablesStack) {
        for (auto entry : table->scopeTable) {
            if ((entry->name == symbol)) {
                return entry->val->funcDecl;
            }
        }
    }
    output::errorUndefFunc(lineNum, symbol);
    exit(1);
}

bool symbolTable::exist(const string &symbol) {

    // go lifo in the vector, look for the symbol
    bool exists = false;
    for (auto table : tablesStack) {
        if (table->existInTable(symbol))
            exists = true;
    }
    return exists;
}

void symbolTable::newDecl(const string &symbol, types type, int lineNum) {
    if (exist(symbol)) {
        errorDef(lineNum, symbol);
        exit(1);
    }
    tablesStack.front()->newLine(symbol, type, offsetStack.getTop());
    offsetStack.incTop();
}

void symbolTable::newFuncDecl(const string &name, FuncDecl& funcDecl, int lineNum) {
    if (exist(name)) {
        errorDef(lineNum, name);
        exit(1);
    }
    tablesStack.front()->newLineForFunc(name, offsetStack.getTop(), funcDecl);
    output::endScope();
}

string symbolTable::typeToStr(types type) {
    string typeStr;
    switch (type) {
        case INT:
            typeStr = "int";
            break;
        case BYTE:
            typeStr = "byte";
            break;
        case BOOL:
            typeStr = "bool";
            break;
        case STRING:
            typeStr = "string";
            break;
        case ENUM:
            //TODO how to save enum custom type
            typeStr = "enum";
            break;
        case FUNC:
            //TODO where to get the params for makeFunctionType
            //output::makeFunctionType( );
            break;
        case VOID:
            break;
    }
    return typeStr;
}

void symbolTable::printScope() {
    Table table = *tablesStack.front();
    for (auto var : table.scopeTable) {
        if (var->type == ENUM) {
            //TODO:: printEnumType(const string& name, vector<string>& values); should be called
            // small structural changes needed.
        }
        printID(var->name, var->offset, var->typeStr);
    }
}
