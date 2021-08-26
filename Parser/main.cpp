//#include <iostream>
//#include <cstring>
//#include "Headers/Parser.h"
//#include <string>
//
//
//#define DIR "//home//arlik_null//Документы//GitHub//Inf_Project//Parser//"
//char* a(char* s) {
//    return s;
//}
//
//
//
//int main() {
//
//    std::pair <int , char* > *data = new std::pair<int, char*> [18];
//    data[0] = {ASN::START, "START"};
//    data[1] = {ASN::Identifier, "x"};
//    data[2] = {ASN::ASSIGNMENT, "="};
//    data[3] = {ASN::Number, "y"};
//    data[4] = {ASN::MULTIPLICATION, "*"};
//    data[5] = {ASN::Number, "5"};
//    data[6] = {ASN::Minus, "+"};
//    data[7] = {ASN::Identifier, "7"};
//    data[8] = {ASN::Line, "LINE"};
//    data[9] = {ASN::Identifier, "y"};
//    data[10] = {ASN::ASSIGNMENT, "="};
//    data[11] = {ASN::Identifier, "x"};
//    data[12] = {ASN::DIVISION, "/"};
//    data[13] = {ASN::Number, "5"};
//    data[14] = {ASN::Minus, "-"};
//    data[15] = {ASN::Number, "7"};
//    data[16] = {ASN::Line, "LINE"};
//    data[17] = {ASN::End, "END"};
//
//    Parser  My_parser(data, 18);
//
//    AST* My_AST = My_parser.GetAST();
//    My_AST->dumper("//home//arlik_null//Документы//GitHub//Inf_Project//Parser//Output", 0, "Proga");
//
//    delete[] data;
//    return 0;
//}


#include <iostream>
#include <fstream>
#include "Headers/Parser.h"

int main () {
        std::ifstream fin(FILENAME);

        if (!fin) {
            std::cerr << "EROOR in testLexer.cpp in read file ";
            throw(1);
        }

    Lexer my_lex(fin);
    std::cout << my_lex << std::endl;
//    Parser  My_parser(my_lex.get_data(), my_lex.get_size_data());
//    AST* My_AST = My_parser.GetAST();
//    My_AST->dumper(OUTAST, MODE, NAMEAST);

    return 0;
}