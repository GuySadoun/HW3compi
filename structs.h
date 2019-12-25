//
// Created by guy-pc on 09/12/2019.
//

#ifndef HW3COMPI_STRUCTS_H
#define HW3COMPI_STRUCTS_H

#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <memory>
#include "hw3_output.hpp"

using std::unordered_map;
using std::string;
using std::vector;

struct Flow;
struct EnumType;
struct Enumerator;
struct EnumeratorList;
struct EnumDecl;
struct ExpList;
struct Call;
struct Expression;
struct Formals;
struct FormalDecl;
struct FormalsList;
struct Statement;
struct Statements;
struct returnExp;
struct ifStatement;
struct ifElseStatement;
struct whileStatement;
struct RetType;
struct FuncDecl;
struct Funcs;
struct Enums;
struct Program;


enum types {
    INT,
    BYTE,
    BOOL,
    VOID,
    STRING,
    ENUM,
    ENUMDEF,
    FUNC
};

string typeToStr(types type);


struct EnumType {
    string name;
    // the type of enum ID is set to be enumID
    explicit EnumType(const string& id);
    EnumType() { name = ""; }
};

struct Enumerator {
    string enumName;
};

struct EnumeratorList {
    vector<Enumerator> values;

    explicit EnumeratorList(const Enumerator& e);

    EnumeratorList(const EnumeratorList& elist, const Enumerator& e);

    EnumeratorList() { values = vector<Enumerator>(); }
};

struct EnumDecl {
    EnumType namedType;
    EnumeratorList values;

    EnumDecl() {}
    EnumDecl(string name, EnumeratorList vals) : namedType(EnumType(std::move(name))), values(std::move(vals)) {}
};

struct Call {
    string name;
    std::shared_ptr<ExpList> args;
    types returnType;

    Call(string id, std::shared_ptr<ExpList> expList) : args(std::move(expList)), name(std::move(id)) {}
    Call(string id) : name(std::move(id)){}
};

typedef union {
    string str;
    int integer;
    bool boolean;
    EnumType enumType;
    Call funType;
} Value;

struct Expression {

    Value val;
    string id;
    types type;

    bool isBool() { return type == BOOL; }

    bool isInt() { return type == INT; }

    bool isNumber() { return (type == INT || type == BYTE); }

    bool isByte() { return type == BYTE; }

    bool isString() { return type == STRING; }

    bool isEnum() { return type == ENUM; }

};

struct ExpList {
    vector<std::reference_wrapper<Expression>> args;

    ExpList() { args = vector<std::reference_wrapper<Expression>>(); }
    ExpList(const ExpList& expList, Expression &exp);
    explicit ExpList(Expression exp);
};

struct FormalDecl {
    types type;
    EnumType enumType;
    string id;
};

struct FormalsList {
    vector<FormalDecl> funDeclParams;

    FormalsList( const FormalDecl& formalDecl, const FormalsList& list);

    explicit FormalsList(const FormalDecl& formalDecl);

    vector<string> formalsToStr();
};

struct Formals {
    FormalsList formalList;

    explicit Formals(FormalsList &fl) : formalList(FormalsList(fl)) {}
};

struct Statements {
    vector<std::shared_ptr<Statement>> statements;
    explicit Statements(const std::shared_ptr<Statement>& s);
    Statements(Statements &statements, const std::shared_ptr<Statement>& s);
};

struct returnExp {
    bool ret;
    Expression retVal;
};

struct ifStatement {
    Expression cond;
    std::shared_ptr<std::reference_wrapper<Statement>> stat;
};

struct ifElseStatement {
    Expression cond;
    std::shared_ptr<std::reference_wrapper<Statement>> statIf;
    std::shared_ptr<std::reference_wrapper<Statement>> statElse;
};

struct whileStatement {
    Expression cond;
    std::shared_ptr<std::reference_wrapper<Statement>> whileScope;
};

struct Flow {
    bool isContinue;
    int line;
};

struct Statement {
    Statements code;
    FormalDecl formalDecl;
    EnumType enumType;
    EnumDecl enumDecl;
    Expression exp;
    Call call;
    returnExp retType;
    ifStatement ifStat;
    ifElseStatement ifElseStat;
    whileStatement whileStat;
    Flow breakStatement;
};

struct RetType {
    types type;
};

struct FuncDecl {
    RetType retType;
    string name;
    Formals formals;
    Statements statements;

    FuncDecl( RetType returnType, string name, Formals &formals, Statements &states);

    string toStr ();
};

struct Funcs {
    vector<FuncDecl> funcDeclarations;

    Funcs(Funcs& funcs, const FuncDecl& fd);
};

struct Enums {
    unordered_map<string, EnumDecl> declaredEnums;

    void addEnumerator(const EnumDecl& enumerator);
};

struct Program {
    Enums enums;
    Funcs funcs;
};

union Types{
    int integer;
    bool boolean;
    types type;
    EnumeratorList enumeratorList;
    Enumerator enumerator;
    string str;
    Call call;
    Expression exp;
    EnumDecl enumDecl;
    EnumType enumType;
    ExpList expList;
    FuncDecl funcDecl;
    Funcs funcs;
    Enums enums;
    RetType retType;
    Formals formals;
    FormalsList formalsList;
    FormalDecl formalDecl;
    Statements statements;
    Statement statement;
    Program program;

    Types() { memset( this, 0, sizeof( Types ) ); }
};

#define YYSTYPE Types

#endif //HW3COMPI_STRUCTS_H
