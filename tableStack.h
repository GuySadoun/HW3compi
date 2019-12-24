//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_TABLESTACK_H
#define HW3COMPI_TABLESTACK_H

#include "hw3_output.hpp"
#include "offsetStack.h"
#include "structs.h"
#include <utility>
#include <vector>

using std::vector;

class TblErr : public std::exception {
public:
    TblErr(const string msg) : m_msg(msg) {}

    const char *what() const throw() override {
        cout << "TblErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }

    const string m_msg;
};

struct Table {
    struct TableEntry {
        string name;
        string typeStr;
        types type;
        int offset;
        shared_ptr<Types> val;

        TableEntry(string name, types type, string typeStr, int offset, shared_ptr<Types> val) :
                name(std::move(name)), type(type), typeStr(std::move(typeStr)), offset(offset), val(std::move(val)) {}

        TableEntry(string name, types type, string typeStr, int offset, const FuncDecl& val) :
                name(std::move(name)), type(type), typeStr(std::move(typeStr)), offset(offset) {
            this->val->funcDecl = val;
        }
    };

    vector<TableEntry *> scopeTable;

    Table() = default;

    void newLine(const string &name, types type, int off, Types &value);

    void newLineForEnum(const string &name, int off, Types &value);

    void newLineForFunc(const string &name, int off, FuncDecl& value);

    bool existInTable(const string &name);

    ~Table();
};

class symbolTable {
    vector<Table *> tablesStack;
    OffsetStack offsetStack;

    void checkTableEmpty(const string &expMessage);

public:

    symbolTable() = default;

    void newScope();

    void endScope();

    void newVar(const string &name, types type, Types &value, int lineNum);

    void newDecl(const string &name, types type, int lineNum);

    void newFuncDecl(const string &name, FuncDecl& funcDecl, int lineNum);

    void updateSymbolValue(const string &name, const Types &value, int lineNum);

    string getStringVal(const string &symbol, int lineNum);

    int getEnumIntegerVal(const string &symbol, int lineNum);

    bool getBoolVal(const string &symbol, int lineNum);

    FuncDecl getFuncVal(const string &symbol, int lineNum);

    bool exist(const string &symbol);
};

extern Enums declared;
extern symbolTable symbolTable;
extern bool insideWhile;

#endif //HW3COMPI_TABLESTACK_H
