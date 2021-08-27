#include "../Headers/Parser.h"

Parser::Parser(std::pair<int, char*> *data, long long size) {
    this->data = new std::pair<int, char*> [size];
    for (long long i = 0; i < size; i++) {
        this->data[i] = data[i];
    }
    this->data_size = size;
}

Parser::~Parser() {
    std::cerr << "Parser deleted" << std::endl;
    delete this->data;
}

std::pair<int, char*> Parser::NextElem() {
    if (_TYPE_DATA_ == END)
        return std::pair<int, char*>{END, "END"};

    this->numb_elem++;
    return this->data[this->numb_elem];
}






AST* Parser::GetAST()
{
    int type = data[this->numb_elem].first;
    char* string = data[this->numb_elem].second;

    if (type != START) {                                // if This don't start with START
        DEBUG
        return nullptr;
    }

    AST* My_AST = new AST();
    ASN* Total_ASN = My_AST->createNode(type, string);  // Create root node and tie to our AST
    NextElem();

    while(_TYPE_DATA_ != END && this->numb_elem < this->data_size) {
        ASN* new_line = ParLine(_TYPE_DATA_,
                                _CHAR_DATA_);
        // new_line tie to right side of old_line
        Total_ASN->rightConnect(new_line);
        Total_ASN = new_line;
    }

    ASN* end_node = new ASN(END, "END");
    Total_ASN->rightConnect(end_node);

    return  My_AST;
}

// Parsing all program. Also create AST and fill it.

// Parsing Line. New Node tie to left side of line node;
ASN* Parser::ParLine(int type, char* string)
{
    if (type == LINE) {
        ASN* Line_node = new ASN(LINE, _CHAR_DATA_);
        NextElem();
        return Line_node;
    }

    ASN* new_node = ParComment(type, string);

    if (_TYPE_DATA_ == RIGHTPAREN   ||
    _TYPE_DATA_ == RIGHTCOMMENT     ||
    _TYPE_DATA_ == RIGHTSQURE       ||
    _TYPE_DATA_ == RIGHTCURLY        ) {
        ASN* wrong_line_node = new ASN(LINE, "LINE");   // I do this specially that three will be beautiful
        wrong_line_node->leftConnect(new_node);
        return new_node;
    }
    if (_TYPE_DATA_ != LINE) {
        DEBUG
        return nullptr;
    }

    ASN* Line_node = new ASN(LINE, _CHAR_DATA_);
    NextElem();

    Line_node->leftConnect(new_node);

    return Line_node;
}

ASN* Parser::ParComment(int type, char *string) {

    if (type == COMMENT) {
        while (data[this->numb_elem].first != LINE && data[this->numb_elem].first != END) {
            NextElem();
        }
        return nullptr;
    }

    if (type == LEFTCOMMENT) {
        while (data[this->numb_elem].first != RIGHTCOMMENT) {
            if (NextElem().first == END) {
                DEBUG
                return nullptr;
            }
        }
        DEBUG
        return nullptr;
    }

    ASN* new_node = ParAssignment(type, string);


    if (_TYPE_DATA_ == COMMENT) {
        while (data[this->numb_elem].first != LINE && data[this->numb_elem].first != END) {
            NextElem();
        }
    }

    if (_TYPE_DATA_ == LEFTCOMMENT) {
        while (data[this->numb_elem].first != RIGHTCOMMENT) {
            if (NextElem().first == END) {
                DEBUG
                return nullptr;
            }
        }
        return new_node;
    }

    return  new_node;
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

    if(_TYPE_DATA_ == ASSIGNMENT)
    {
        ASN* new_node = ParAssignment(_TYPE_DATA_,
                                      _CHAR_DATA_);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParLogic(_TYPE_DATA_,
                                       _CHAR_DATA_);
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

    if(_TYPE_DATA_ == EQUAL ||
       _TYPE_DATA_ == NOTEQUAL)
    {
        ASN* new_node = ParLogic(_TYPE_DATA_,
                                 _CHAR_DATA_);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParCmp(_TYPE_DATA_,
                                     _CHAR_DATA_);
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

    if(_TYPE_DATA_ == LESSTHAN ||
       _TYPE_DATA_ == GRESTERTHAN)
    {
        ASN* new_node = ParCmp(_TYPE_DATA_,
                               _CHAR_DATA_);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParAddSub(_TYPE_DATA_,
                                        _CHAR_DATA_);
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

    if(_TYPE_DATA_ == PLUS ||
       _TYPE_DATA_ == MINUS)
    {
        ASN* new_node = ParAddSub(_TYPE_DATA_,
                                  _CHAR_DATA_);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParMuliDiv(_TYPE_DATA_,
                                         _CHAR_DATA_);
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

    if (_TYPE_DATA_ == MULTIPLICATION ||
        _TYPE_DATA_ == DIVISION)
    {
        ASN* new_node = ParMuliDiv(_TYPE_DATA_,
                                   _CHAR_DATA_);
        new_node->leftConnect(new_node_left);

        ASN* new_node_right = ParPow(_TYPE_DATA_,
                                     _CHAR_DATA_);
        new_node->rightConnect(new_node_right);

        return new_node;
    }

    return new_node_left;

}



ASN* Parser::ParPow(int type, char* string) {
    if (type != POW) {
        ASN* new_node_left = ParDot(type, string);

        if (_TYPE_DATA_ == POW) {
            ASN* new_node = ParPow(_TYPE_DATA_,
                                   _CHAR_DATA_);
            new_node->leftConnect(new_node_left);

            ASN* new_node_right = ParDot(_TYPE_DATA_,
                                         _CHAR_DATA_);
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

    if (_TYPE_DATA_ == DOT) {
        ASN* new_node = ParDot(_TYPE_DATA_,
                               _CHAR_DATA_);
        new_node->leftConnect(new_left_node);

        ASN* new_right_node = ParComma(_TYPE_DATA_,
                                       _CHAR_DATA_);
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

    if (_TYPE_DATA_ == COMMA) {
        ASN* new_node = ParComma(_TYPE_DATA_,
                               _CHAR_DATA_);
        new_node->leftConnect(new_left_node);

        ASN* new_right_node = ParIdentifier(_TYPE_DATA_,
                                       _CHAR_DATA_);
        new_node->rightConnect(new_right_node);

        return new_node;
    }

    return new_left_node;
}









ASN* Parser::ParIdentifier(int type, char *string) {
    if (type != IDENTIFIER) {
        ASN* new_node = ParNumber(type, string);
        if (_TYPE_DATA_ == IDENTIFIER) {
            DEBUG
            return nullptr;
        }

        return  new_node;
    }



    ASN* new_node = new ASN(type, string);
    NextElem();

    if (_TYPE_DATA_ == LEFTPAREN) {
        ASN* in_func_node = ParParen(type, string);
        if (_TYPE_DATA_ == IDENTIFIER) {
            DEBUG
            return nullptr;
        }

//        ASN* in_func_node.


    }

    return new_node;
}

ASN* Parser::ParNumber(int type, char *string) {
    if (type != NUMBER) {
        ASN* new_node =  ParParen(type, string);
        if (_TYPE_DATA_ == NUMBER) {
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

//        ASN* new_in_node = ParBlock(_TYPE_DATA_, _CHAR_DATA_);

        ASN* help_node = nullptr;
        while (_TYPE_DATA_ != RIGHTPAREN) {
            if (_TYPE_DATA_ == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(_TYPE_DATA_,
                                          _CHAR_DATA_);
            if (!help_node) {
                help_node = new_in_bracket;
                new_node_bracket->leftConnect(help_node);
                continue;
            }
            help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        NextElem();                                             // because in Parline in if I don't move this->numb_elem that
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
        ASN* new_node_bracket = new ASN(CURLY, "ParCurly");
        NextElem();

        ASN* help_node = nullptr;
        while (_TYPE_DATA_ != RIGHTCURLY) {
            if (_TYPE_DATA_ == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }

            ASN* new_in_bracket = ParLine(_TYPE_DATA_,
                                          _CHAR_DATA_);
            if (!help_node) {
                help_node = new_in_bracket;
                new_node_bracket->leftConnect(help_node);
                continue;
            }
            help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        NextElem();                                      // because in Parline in if I don't move this->numb_elem that
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
        while (_TYPE_DATA_ != RIGHTSQURE) {
            if (_TYPE_DATA_ == END || this->numb_elem == this->data_size) {
                DEBUG
                break;
            }


            ASN* new_in_bracket = ParLine(_TYPE_DATA_,
                                          _CHAR_DATA_);
            if (!help_node) {
                help_node = new_in_bracket;
                new_node_bracket->leftConnect(help_node);
                continue;
            }
            help_node->rightConnect(new_in_bracket);
            help_node = new_in_bracket;
        }

        NextElem();                                      // because in Parline in if I don't move this->numb_elem that
                                                         // I can verify to close bracket

        return new_node_bracket;

    }
    // оно не должно доходить до праой скобки потому что правой скобке нечего возвращать
    if (type == RIGHTSQURE) {
        DEBUG
        return nullptr;
    }
    // Если это не скобка
    ASN* new_node = ItsEnd(type, string);
    return new_node;
}




ASN* Parser::ItsEnd(int type, char *string) {
    std::cerr <<std::endl<< type << " " << string << std::endl;
    DEBUG
    return nullptr;
}
