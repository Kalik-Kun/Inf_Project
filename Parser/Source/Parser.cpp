#include "../Headers/Parser.h"

Parser::Parser(std::pair<int, char*> *data, long long size) {
    this->data = new std::pair<int, char*> [size];
    this->data = data;
    this->data_size = size;
}

Parser::~Parser() {
    std::cerr << "Parser deleted" << std::endl;
    delete this->data;
}

std::pair<int, char*> Parser::NextElem() {
    if (this->data[numb_elem].first == END)
        return std::pair<int, char*>{END, "END"};

    this->numb_elem++;
    return this->data[numb_elem];
}






AST* Parser::GetAST()
{
    int type = data[numb_elem].first;
    char* string = data[numb_elem].second;

    if (type != START) {                                // if This don't start with START
        DEBUG
        return nullptr;
    }

    AST* My_AST = new AST();
    ASN* Total_ASN = My_AST->createNode(type, string);  // Create root node and tie to our AST

    Total_ASN->rightConnect(ParBlock(type, string));
    NextElem();

    while(this->data[numb_elem].first != END && this->numb_elem < this->data_size) {
        ASN* new_line = ParLine(this->data[numb_elem].first,
                                this->data[numb_elem].second);
        // new_line tie to right side of old_line
        Total_ASN->rightConnect(new_line);
        Total_ASN = new_line;
    }

    ASN* end_node = new ASN(END, "END");
    Total_ASN->rightConnect(end_node);

    return  My_AST;
}

// Parsing all program. Also create AST and fill it.
ASN* Parser::ParBlock(int type, char* string)
{

}
// Parsing Line. New Node tie to left side of line node;
ASN* Parser::ParLine(int type, char* string)
{
    ASN* new_node = ParAssignment(type, string);

    if ()


    if (this->data[numb_elem].first == RIGHTPAREN   ||
    this->data[numb_elem].first == RIGHTCOMMENT     ||
    this->data[numb_elem].first == RIGHTSQURE       ||
    this->data[numb_elem].first == RIGHTCURLY        ) {
        ASN* wrong_line_node = new ASN(LINE, "LINE");   // I do this specially that three will be beautiful
        wrong_line_node->leftConnect(new_node);
        return new_node;
    }
    if (this->data[numb_elem].first != LINE) {
        DEBUG
        return nullptr;
    }

    ASN* Line_node = new ASN(LINE, this->data[numb_elem].second);
    NextElem();

    Line_node->leftConnect(new_node);

    return Line_node;
}

// Parsing assignment, This has less priority in program;
ASN* Parser::ParAssignment(int type, char* string)
{
    if (type == ASSIGNMENT)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParLogic(type, string);

    if(this->data[numb_elem].first == ASSIGNMENT)
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
    if (type == EQUAL || type == NOTEQUAL)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParCmp(type, string);

    if(this->data[numb_elem].first == EQUAL ||
       this->data[numb_elem].first == NOTEQUAL)
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
    if (type == LESSTHAN || type == GRESTERTHAN)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParAddSub(type, string);

    if(this->data[numb_elem].first == LESSTHAN ||
       this->data[numb_elem].first == GRESTERTHAN)
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
    if (type == PLUS || type == MINUS)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN* new_node_left = ParMuliDiv(type, string);

    if(this->data[numb_elem].first == PLUS ||
       this->data[numb_elem].first == MINUS)
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

    if (type == MULTIPLICATION || type == DIVISION)
    {
        ASN* new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }


    ASN* new_node_left = ParPow(type, string);

    if (this->data[numb_elem].first == MULTIPLICATION ||
        this->data[numb_elem].first == DIVISION)
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
    if (type != POW) {
        ASN* new_node_left = ParDot(type, string);

        if (this->data[numb_elem].first == POW) {
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
    if (type == DOT) {
        ASN *new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN *new_left_node = ParComma(type, string);

    if (this->data[numb_elem].first == DOT) {
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
    if (type == COMMA) {
        ASN *new_node = new ASN(type, string);
        NextElem();
        return new_node;
    }

    ASN *new_left_node = ParIdentifier(type, string);

    if (this->data[numb_elem].first == COMMA) {
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
    if (type != IDENTIFIER) {
        ASN* new_node = ParNumber(type, string);
        if (this->data[numb_elem].first == IDENTIFIER) {
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
    if (type != NUMBER) {
        ASN* new_node =  ParParen(type, string);
        if (this->data[numb_elem].first == NUMBER) {
            DEBUG
            return nullptr;
        }

        return new_node;
    }

    ASN* new_node = new ASN(type, string);
    NextElem();

    return new_node;
}

//
ASN* Parser::ParParen(int type,  char* string) {
     // Открывает новый рекурсионный цикл
    if (type == LEFTPAREN) {
        ASN* new_node_bracket = new ASN(PAREN, "()");
        NextElem();

//        ASN* new_in_node = ParBlock(this->data[numb_elem].first, this->data[numb_elem].second);

        ASN* help_node = nullptr;
        while (this->data[numb_elem].first != RIGHTPAREN) {
            if (this->data[numb_elem].first == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(this->data[numb_elem].first,
                                          this->data[numb_elem].second);
            if(help_node) help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        new_node_bracket->leftConnect(help_node);
        NextElem();                                             // because in Parline in if I don't move numb_elem that
                                                                // I can verify to close bracket
        return new_node_bracket;
    }
     // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == RIGHTPAREN) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParCurly(type, string);
    return new_node;

}

ASN* Parser::ParCurly(int type,  char* string) {
    // Открывает новый рекурсионный цикл
    if (type == LEFTCURLY) {
        ASN* new_node_bracket = new ASN(CURLY, "{}");
        NextElem();

        ASN* help_node = nullptr;
        while (this->data[numb_elem].first != RIGHTCURLY) {
            if (this->data[numb_elem].first == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(this->data[numb_elem].first,
                                          this->data[numb_elem].second);
            if(help_node) help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        new_node_bracket->leftConnect(help_node);
        NextElem();                                      // because in Parline in if I don't move numb_elem that
                                                         // I can verify to close bracket

        return new_node_bracket;
    }
    // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == RIGHTCURLY) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParSquare(type, string);
    return new_node;

}

ASN* Parser::ParSquare(int type,  char* string) {
    // Открывает новый рекурсионный цикл
    if (type == LEFTSQUARE) {
        ASN* new_node_bracket = new ASN(SQUARE, "[]");
        NextElem();

        ASN* help_node = nullptr;
        while (this->data[numb_elem].first != RIGHTSQURE) {
            if (this->data[numb_elem].first == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(this->data[numb_elem].first,
                                          this->data[numb_elem].second);
            if(help_node) help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        new_node_bracket->leftConnect(help_node);
        NextElem();                                      // because in Parline in if I don't move numb_elem that
                                                         // I can verify to close bracket

        return new_node_bracket;

    }
    // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == RIGHTSQURE) {
        DEBUG
        return nullptr;
    }

    // Если это не скобка
    ASN* new_node = ParComment(type, string);
    return new_node;
}

ASN* Parser::ParComment(int type, char *string) {

    if (type == LEFTCOMMENT) {
        ASN* new_node_bracket = new ASN(COMMENT, "/**/");
        NextElem();

        ASN* help_node = nullptr;
        while (this->data[numb_elem].first != RIGHTCOMMENT) {
            if (this->data[numb_elem].first == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(this->data[numb_elem].first,
                                          this->data[numb_elem].second);
            if(help_node) help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        new_node_bracket->leftConnect(help_node);
        NextElem();                                     // because in Parline in if I don't move numb_elem that
                                                        // I can verify to close bracket

        return new_node_bracket;
    }


    if (type == RIGHTCOMMENT) {
        DEBUG
        return nullptr;
    }

    ASN* new_node = ItsEnd(type, string);
    return new_node;
}

ASN* Parser::ItsEnd(int type, char *string) {
    DEBUG
    return nullptr;
}
