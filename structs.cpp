//
// Created by guy-pc on 24/12/2019.
//

#include "structs.h"

string typeToStr(types type) {
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

string FuncDecl::toStr() {
    vector<string> formls = formals.formalList.formalsToStr();
    return output::makeFunctionType(typeToStr(retType.type), formls);
}

FuncDecl::FuncDecl(RetType returnType, string name, Formals &formals, Statements &states) : statements(states),
                                                                                            formals(formals),
                                                                                            retType(returnType),
                                                                                            name(std::move(name)) {}

EnumType::EnumType(const string& id) {
    name = "enum " + id;
}

EnumeratorList::EnumeratorList(const Enumerator &e) {
    this->values.push_back(e);
}

EnumeratorList::EnumeratorList(const EnumeratorList &elist, const Enumerator &e) : values(elist.values) {
    this->values.push_back(e);
}

ExpList::ExpList(const ExpList &expList, Expression &exp) : args(expList.args) {
    this->args.emplace_back(exp);
}

ExpList::ExpList(Expression exp) {
    this->args.emplace_back(exp);
}

FormalsList::FormalsList(const FormalDecl &formalDecl, const FormalsList &list) : funDeclParams(list.funDeclParams ) {
    this->funDeclParams.push_back(formalDecl);
}

FormalsList::FormalsList(const FormalDecl &formalDecl) {
    this->funDeclParams.push_back(formalDecl);
}

vector<string> FormalsList::formalsToStr() {
    vector<string> ret;
    for (const auto& formalDecl : funDeclParams) {
        ret.insert(ret.begin(), typeToStr(formalDecl.type));
    }
    return ret;
}

Statements::Statements(const std::shared_ptr<Statement> &s) {
    this->statements.push_back(s);
}

Statements::Statements(Statements &statements, const std::shared_ptr<Statement> &s) {
    statements.statements = statements.statements;
    this->statements.push_back(s);
}

Funcs::Funcs(Funcs &funcs, const FuncDecl &fd) {
    funcDeclarations = funcs.funcDeclarations;
    funcDeclarations.push_back(fd);
}

void Enums::addEnumerator(const EnumDecl &enumerator) {
    declaredEnums[enumerator.namedType.name] = enumerator;
}
