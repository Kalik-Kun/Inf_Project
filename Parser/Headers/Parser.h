#include "AbstractSyntaxTree.h"





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
//    ASN* ParBlock       (int , char* ); // Разделяет на блоки
    ASN* ParLine        (int , char* ); // Парсит Строку
    ASN* ParComment     (int , char* ); // /* */
    ASN* ParAssignment  (int , char* ); // =
    ASN* ParLogic       (int , char* ); // == , !=
    ASN* ParCmp         (int , char* ); // < , >
    ASN* ParAddSub      (int , char* ); // +, -       // тут вроде нет ошибки
    ASN* ParMuliDiv     (int , char* ); // *, /       // в приоритете я проверил на опыте
    ASN* ParPow         (int , char* ); // ^
    ASN* ParDot         (int , char* ); // .
    ASN* ParComma       (int , char* ); // ,
    ASN* ParIdentifier  (int , char* ); // переменная какое либо значение и тд
    ASN* ParNumber      (int , char* ); // Число
    // Brackets
    ASN* ParParen       (int , char* ); // ()
    ASN* ParCurly       (int , char* ); // {}
    ASN* ParSquare      (int , char* ); // []

    ASN* ParFunc        (int , char* ); // parsing smth functions
    ASN* ParArr         (int , char* ); // parsing smth functions
    // In the End It doesn't even matter
    ASN* ItsEnd         (int , char* ); // for DEBAG

};

