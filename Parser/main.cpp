#include <iostream>
#include <cstring>
#include "Headers/Parser.h"
char* a(char* s) {
    return s;
}


int main() {

    std::pair <int , char* > *data = new std::pair<int, char*> [10];
    data[0] = {ASN::START, "START"};
    data[1] = {ASN::Identifier, "x"};
    data[2] = {ASN::ASSIGNMENT, "="};
    data[3] = {ASN::Identifier, "y"};
    data[4] = {ASN::MULTIPLICATION, "*"};
    data[5] = {ASN::Number, "5"};
    data[6] = {ASN::Plus, "+"};
    data[7] = {ASN::Number, "7"};
    data[8] = {ASN::Line, "LINE"};
    data[9] = {ASN::End, "END"};

    Parser  My_parser(data, 10);

    AST* My_AST = My_parser.GetAST();
    My_AST->dumper("C:\\Users\\Xiaomi\\CLionProjects\\Parser\\Output", 1, "Hui");

    delete[] data;
    return 0;
}
