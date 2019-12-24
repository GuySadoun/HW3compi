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