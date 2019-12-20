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

class Table {
    vector<TableEntry> scopeTable;
public:

    struct TableEntry {
        string name;
        types type;
        int offset;
        Types val;
        TableEntry(string name, string type, int offset, Types value) : name(name), type(type), offset(offset) {}
        TableEntry( TableEntry toCopy){
             name = toCopy.name;
             type = toCopy.type;
             offset = toCopy.offset;
             val = toCopy.val;
        }
        ~TableEntry();
    };


    Table() = default;
    void newLine(string name, string type, int off);
    bool existInTable(string name);
    Table::TableEntry getEntryfromScope(string name);
    ~Table();
};

class symbolTable {

    vector<Table*> tablesStack;
    OffsetStack offsetStack;

public:
    symbolTable() = default;
    void newVar(string symbol, string type, Types value);
    Table::TableEntry getSymbolEntry (string symbol);
    void newScope();
    void endScope();
    bool exist(string symbol);
    Types &findSymbol(string symbol);
    void updateSymbolValue( string symbol, Types value );
    types getType( string symbol);
};

#endif //HW3COMPI_TABLESTACK_H
