//
// Created by Xiaomi on 11.05.2021.
//
#include "debug.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <map>
class AbstractSyntaxTree
{
public:

    enum Modes
    {
        DEFAULT     = 0,
        SHOW        = 1,
        DELETE_PNG  = 10,
        DELETE_TXT  = 100,
        DETAILED    = 1000,
    };

    class Node
    {
        friend class AbstractSyntaxTree;

    public:

        int   type      =  Unexpected; //Что это вообще такое
        int   ivalue    =  0;          // Если переменная или число то ее тзначении int
        float fvalue    =  0;          // Если переменная или число ее значение float
        char* svalue    =  nullptr;    // Названия функции или коментария будет разбирать интопретатор
        int   data_type =  NO_TYPE;    // Что из этого говна выбиратть

        enum TypeOfDate {
            NO_TYPE,
            INT_TYPE,
            FLOAT_TYPE,
            CHAR_TYPE,
        };

        enum  TypeLexem{
            Number,                 // число
            Identifier,             // переменная
            LeftParen,              // левая скобка (
            RightParen,             // правая скобка )
            LeftSquare,             // {
            RightSquare,            // }
            LeftCurly,              // [
            RightCurly,             // ]
            LessThan,               // <
            GreaterThan,            // >
            Equal,                  // ==
            Plus,                   // +
            Minus,                  // -
            Asterisk,
            Slash,
            Hash,
            Dot,
            Comma,                  // ,
            Colon,                  // :
            Semicolon,              // ;
            SingleQuote,
            DoubleQuote,
            Comment,                // coment
            Pipe,
            End,                    // конец программы
//          мое если что
            POW,                    // возведение в степень
            MULTIPLICATION,         // умножение
            DIVISION,               // деление
            NotEqual,               // !=
            ASSIGNMENT,             // присвоить
            Line,                   // конец строки
            START,                  // начало програмы
            Paren,                  // Скобки законченые ()
            Curly,                  // {}
            Square,                 // []
            Unexpected,             // неизвестно
        };

        Node* parent = nullptr;
        Node* left   = nullptr;
        Node* right  = nullptr;


        Node(int type, int   ivalue);
        Node(int type, float fvalue);
        Node(int type, char* svalue);
        ~Node();

        // стирание
        void flush();

        // подсоеденить другой корень к левой или правой ссылке
        void leftConnect(Node* left);
        void leftConnect(AbstractSyntaxTree* left);

        void rightConnect(Node* right);
        void rightConnect(AbstractSyntaxTree* right);

        // увеличиваю количество нодов
        void fixContainer();

//        типо рисунок
        int dumper          (std::ofstream& file, int mode);
        const char* colorize();
        void write          (std::ofstream& out);
        void print          ();

        std::map<int, char*> Lexem_map {
                {Number         , "Number"        },
                {Identifier     , "Identifier"    },
                {LeftParen      , "LeftParen"     },
                {RightParen     , "RightParen"    },
                {LeftSquare     , "LeftSquare"    },
                {RightSquare    , "RightSquare"   },
                {LeftCurly      , "LeftCurly"     },
                {RightCurly     , "RightCurly"    },
                {LessThan       , "LessThan"      },
                {GreaterThan    , "GreaterThan"   },
                {Equal          , "Equal"         },
                {Plus           , "Plus"          },
                {Minus          , "Minus"         },
                {Asterisk       , "Asterisk"      },
                {Slash          , "Slash"         },
                {Hash           , "Hash"          },
                {Dot            , "Dot"           },
                {Comma          , "Comma"         },
                {Colon          , "Colon"         },
                {Semicolon      , "Semicolon"     },
                {SingleQuote    , "SingleQuote"   },
                {DoubleQuote    , "DoubleQuote"   },
                {Comment        , "Comment"       },
                {Pipe           , "Pipe"          },
                {End            , "End"           },
                {POW            , "POW"           },
                {MULTIPLICATION , "MULTIPLICATION"},
                {DIVISION       , "DIVISION"      },
                {NotEqual       , "NotEqual"      },
                {ASSIGNMENT     , "ASSIGNMENT"    },
                {Line           , "Line"          },
                {START          , "START"         },
                {Paren          , "Paren"         },
                {Curly          , "Curly"         },
                {Square         , "Square"        },
                {Unexpected     , "Unexpected"}


        };

    private:
        AbstractSyntaxTree* container = nullptr;
    };

    AbstractSyntaxTree ();
    ~AbstractSyntaxTree();

    int dumper(const char* filename, int mode, const char* title);

    Node* createNode(int type, int   ivalue);
    Node* createNode(int type, float fvalue);
    Node* createNode(int type, char* svalue);

    Node* head = nullptr;

private:
    unsigned long long int nodes_count = 0;
};


typedef AbstractSyntaxTree AST;
typedef AST::Node ASN;


bool isLetter (char  symbol);
bool isNumber (char  symbol);
bool isOperand(char  symbol);
bool isEnd    (char  symbol);

bool isInteger(char* string);
bool isFloat  (char* string);



