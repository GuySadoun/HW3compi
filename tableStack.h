//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_TABLESTACK_H
#define HW3COMPI_TABLESTACK_H

#include "offsetStack.h"
#include "structs.h"
#include <vector>

using std::vector;

class TblErr : public std::exception {
public:
    TblErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "TblErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

struct Table {
    struct TableEntry {
        string name;
        types type;
        int offset;
        Types val;

        TableEntry(string name, string type, int offset) : name(name), type(type), offset(offset) {}
    };
    vector<TableEntry*> scopeTable;
    Table() = default;
    void newLine(string name, types type, int off);
    bool existInTable(string name);
    ~Table();
};
class symbolTable {
    vector<Table*> tablesStack;
    OffsetStack offsetStack;
public:
    symbolTable() = default;
    void newVar(string name, string type);
    void newScope();
    void endScope();
    bool exist(string symbol);
    string getStringVal(string symbol);
    int getIntegerVal(string symbol);
    bool getBoolVal(string symbol);
    Call getCallVal( string symbol );
};

#endif //HW3COMPI_TABLESTACK_H
