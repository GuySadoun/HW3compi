//
// Created by guy-pc on 14/12/2019.
//

#ifndef HW3COMPI_TABLESTACK_H
#define HW3COMPI_TABLESTACK_H

#include "offsetStack.h"

using std::string;
using std::stack;
using std::cout;
using std::endl;

class TblErr : public std::exception {
public:
    TblErr(const string msg) : m_msg(msg) {}
    const char* what() const throw () override {
        cout << "TblErr - what:" << m_msg << endl;
        return m_msg.c_str();
    }
    const string m_msg;
};

class TableStack {
    class Table {
        struct TableEntry {
            string name;
            string type;
            int offset;

            TableEntry(string name, string type, int offset) : name(name), type(type), offset(offset) {}
        };
        stack<TableEntry> scopeTable;
    public:
        Table() = default;
        void newLine(string name, string type, int off);
        void removeTopTable();
    };
    stack<Table> tablesStuck;
public:
    void newVar(string name, string type, int off);
    void newScope();
    void endScope();
};

#endif //HW3COMPI_TABLESTACK_H
