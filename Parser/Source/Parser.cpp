#include "../Headers/Parser.h"

Parser::Parser(std::pair<int, char*> *data, long long size) {
    this->data = new std::pair<int, char*> [size];
    this->data = data;
}

Parser::~Parser() {
    std::cerr << "Parser deleted" << std::endl;
    delete this->data;
}

std::pair<int, char*> Parser::NextElem() {
    if (this->data[numb_elem].first == ASN::End)
        return std::pair<int, char*>{ASN::End, "EXIT"};

    this->numb_elem++;

    if (this->data[numb_elem].first == ASN::End)
        return std::pair<int, char*>{ASN::End, "EXIT"};

    return this->data[numb_elem];
}





AST* Parser::ParBlock(int type, char* string)
{
    if (type != ASN::START) {
        DEBUG
        return nullptr;
    }

    AST* My_AST = new AST();
    ASN* Total_ASN = My_AST->createNode(type, string);
    NextElem();

    while(this->data[numb_elem].first != ASN::End) {

        ASN* new_line = ParLine(this->data[numb_elem].first,
                                this->data[numb_elem].second);
        Total_ASN->rightConnect(new_line);
        Total_ASN = new_line;
    }

    return  My_AST;
}
ASN* Parser::ParLine(int type, char* string)
{
    ASN* new_node = ParAssignment(type, string);
    if (this->data[numb_elem].first != ASN::Line) {
        DEBUG
        return nullptr;
    }

    ASN* Line_node = new ASN(ASN::Line, this->data[numb_elem].second);
    NextElem();

    Line_node->leftConnect(new_node);

    return Line_node;
}
ASN* Parser::ParAssignment(int type, char* string)
{
    if (type == ASN::ASSIGNMENT)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParLogic(type, string);

    if(this->data[numb_elem].first == ASN::ASSIGNMENT)
    {
        ASN* new_node = ParAssignment(this->data[numb_elem].first,
                                      this->data[numb_elem].second);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParLogic(this->data[numb_elem].first,
                                       this->data[numb_elem].second);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;
}

ASN* Parser::ParLogic(int type, char* string)
{
    if (type == ASN::Equal || type == ASN::NotEqual)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParCmp(type, string);

    if(this->data[numb_elem].first == ASN::Equal ||
       this->data[numb_elem].first == ASN::NotEqual)
    {
        ASN* new_node = ParLogic(this->data[numb_elem].first,
                                 this->data[numb_elem].second);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParCmp(this->data[numb_elem].first,
                                     this->data[numb_elem].second);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;
}

ASN* Parser::ParCmp(int type, char* string)
{
    if (type == ASN::LessThan || type == ASN::GreaterThan)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParAddSub(type, string);

    if(this->data[numb_elem].first == ASN::LessThan ||
       this->data[numb_elem].first == ASN::GreaterThan)
    {
        ASN* new_node = ParCmp(this->data[numb_elem].first,
                               this->data[numb_elem].second);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParAddSub(this->data[numb_elem].first,
                                        this->data[numb_elem].second);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;
}

ASN* Parser::ParAddSub(int type, char* string)
{
    if (type == ASN::Plus || type == ASN::Minus)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParMuliDiv(type, string);

    if(this->data[numb_elem].first == ASN::Plus ||
       this->data[numb_elem].first == ASN::Minus)
    {
        ASN* new_node = ParAddSub(this->data[numb_elem].first,
                                  this->data[numb_elem].second);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParMuliDiv(this->data[numb_elem].first,
                                         this->data[numb_elem].second);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;
}

ASN* Parser::ParMuliDiv(int type, char* string)
{

    if (type == ASN::MULTIPLICATION || type == ASN::DIVISION)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }


    ASN* new_node_left = ParPow(type, string);

    if (this->data[numb_elem].first == ASN::MULTIPLICATION ||
        this->data[numb_elem].first == ASN::DIVISION)
    {
        ASN* new_node = ParMuliDiv(this->data[numb_elem].first,
                                   this->data[numb_elem].second);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParPow(this->data[numb_elem].first,
                                     this->data[numb_elem].second);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;

}



ASN* Parser::ParPow(int type, char* string) {
    if (type != ASN::POW) {
        ASN* new_node_left = ParDot(type, string);

        if (this->data[numb_elem].first == ASN::POW) {
            ASN* new_node = ParPow(this->data[numb_elem].first,
                                   this->data[numb_elem].second);
            new_node->leftConnect(new_node_left);

            ASN* new_node_right = ParDot(this->data[numb_elem].first,
                                         this->data[numb_elem].second);
            new_node->rightConnect(new_node_right);

            return new_node;
        }

        return new_node_left;
    }

    ASN* new_node = new ASN(type, string);
    NextElem();

    return new_node;
}

ASN* Parser::ParDot(int type, char* string) {
    if (type == ASN::Dot) {
        ASN *new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN *new_left_node = ParComma(type, string);

    if (this->data[numb_elem].first == ASN::Dot) {
        ASN* new_node = ParDot(this->data[numb_elem].first,
                               this->data[numb_elem].second);
        new_node->leftConnect(new_left_node);

        ASN* new_right_node = ParComma(this->data[numb_elem].first,
                                       this->data[numb_elem].second);
        new_node->rightConnect(new_right_node);

        return new_node;
    }

    return new_left_node;
}

ASN* Parser::ParComma(int type, char* string) {
    if (type == ASN::Comma) {
        ASN *new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN *new_left_node = ParIdentifier(type, string);

    if (this->data[numb_elem].first == ASN::Comma) {
        ASN* new_node = ParComma(this->data[numb_elem].first,
                               this->data[numb_elem].second);
        new_node->leftConnect(new_left_node);

        ASN* new_right_node = ParIdentifier(this->data[numb_elem].first,
                                       this->data[numb_elem].second);
        new_node->rightConnect(new_right_node);

        return new_node;
    }

    return new_left_node;
}









ASN* Parser::ParIdentifier(int type, char *string) {
    if (type != ASN::Identifier) {
        ASN* new_node = ParNumber(type, string);
        if (this->data[numb_elem].first == ASN::Identifier) {
            DEBUG
            return nullptr;
        }

        return  new_node;
    }



    ASN* new_node = new ASN(type, string);
    NextElem();

    return new_node;
}

ASN* Parser::ParNumber(int type, char *string) {
    if (type != ASN::Number) {
        ASN* new_node =  ParParen(type, string);
        if (this->data[numb_elem].first == ASN::Number) {
            DEBUG
            return nullptr;
        }

        return new_node;
    }

    ASN* new_node = new ASN(type, string);
    NextElem();

    return new_node;
}


ASN* Parser::ParParen(int type,  char* string) {
     // Открывает новый рекурсионный цикл
    if (type == ASN::LeftParen) {
        ASN* new_node_Paren = new ASN(ASN::Paren, "()");
        NextElem();

        ASN* new_in_node = ParAssignment(this->data[numb_elem].first, this->data[numb_elem].second);

        if (this->data[numb_elem].first != ASN::RightParen) {
            DEBUG
            return nullptr;
        }

        new_node_Paren->leftConnect(new_in_node);

        return new_node_Paren;
    }
     // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == ASN::RightParen) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParCurly(type, string);
    return new_node;

}

ASN* Parser::ParCurly(int type,  char* string) {
    // Открывает новый рекурсионный цикл
    if (type == ASN::LeftCurly) {
        ASN* new_node_Paren = new ASN(ASN::Curly, "{}");
        NextElem();

        ASN* new_in_node = ParAssignment(this->data[numb_elem].first, this->data[numb_elem].second);

        if (this->data[numb_elem].first != ASN::RightCurly) {
            DEBUG
            return nullptr;
        }

        new_node_Paren->leftConnect(new_in_node);

        return new_node_Paren;
    }
    // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == ASN::RightCurly) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParSquare(type, string);
    return new_node;

}

ASN* Parser::ParSquare(int type,  char* string) {
    // Открывает новый рекурсионный цикл
    if (type == ASN::LeftSquare) {
        ASN* new_node_Paren = new ASN(ASN::Square, "[]");
        NextElem();

        ASN* new_in_node = ParAssignment(this->data[numb_elem].first, this->data[numb_elem].second);

        if (this->data[numb_elem].first != ASN::RightSquare) {
            DEBUG
            return nullptr;
        }

        new_node_Paren->leftConnect(new_in_node);

        return new_node_Paren;
    }
    // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == ASN::RightSquare) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParCurly(type, string);
    return new_node;
}


AST* Parser::GetAST() {
    return ParBlock(data[numb_elem].first, data[numb_elem].second);
}