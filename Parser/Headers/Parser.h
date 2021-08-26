#include <iostream>
#include "AbstractSyntaxTree.h"
#include <iterator>




class Parser {
private:
    std::pair<int, char*> *data = nullptr;
    long numb_elem = 0;
    long data_size = 0;
public:

    Parser(std::pair<int, char* >*  , long long size);
    ~Parser();

    std::pair<int, char*> NextElem();

    AST* GetAST         ();

private:
    // Line tio to right node, other tio to left node
    ASN* ParBlock       (int type, char* string); // Разделяет на блоки
    ASN* ParLine        (int type, char* string); // Парсит Строку
    ASN* ParAssignment  (int type, char* string); // =
    ASN* ParLogic       (int type, char* string); // == , !=
    ASN* ParCmp         (int type, char* string); // < , >
    ASN* ParAddSub      (int type, char* string); // +, -       // тут вроде нет ошибки
    ASN* ParMuliDiv     (int type, char* string); // *, /       // в приоритете я проверил на опыте
    ASN* ParPow         (int type, char* string); // ^
    ASN* ParDot         (int type, char* string); // .
    ASN* ParComma       (int type, char* string); // ,
    ASN* ParIdentifier  (int type, char* string); // переменная какое либо значение и тд
    ASN* ParNumber      (int type, char* string); // Число
    // Скобки
    ASN* ParParen       (int type, char* string); // ()
    ASN* ParCurly       (int type, char* string); // {}
    ASN* ParSquare      (int type, char* string); // []
    ASN* ParComment     (int type, char* string); // /* */
    ASN* ItsEnd         (int type, char* string); // for DEBAG

};

