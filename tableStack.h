//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_TABLESTACK_H
#define HW3COMPI_TABLESTACK_H

#include "hw3_output.hpp"
#include "offsetStack.h"
#include "structs.h"
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
        Types &val;

        TableEntry(string name, string type, int offset, Types &val) :
                name(name), type(type), typeStr(typeStr), offset(offset), val(val) {}
    };

    vector<TableEntry *> scopeTable;

    Table() = default;

    void newLine(string name, types type, int off, Types value);

    bool existInTable(const string &name);

    string typeToStr(types t);

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

    void newVar(const string &name, string type, Types &value, int lineNum);

    void newDecl(const string &name, string type, int lineNum);

    void updateSymbolValue(const string &name, const Types &value, int lineNum);

    string getStringVal(const string &symbol, int lineNum);

    int getIntegerVal(const string &symbol, int lineNum);

    bool getBoolVal(const string &symbol, int lineNum);

    FuncDecl getFuncVal(const string &symbol, int lineNum);

    bool exist(const string &symbol);

};

#endif //HW3COMPI_TABLESTACK_H
