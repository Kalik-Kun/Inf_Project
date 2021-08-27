//
// Created by Xiaomi on 11.05.2021.
//
#include <map>
#include "Lexer.h"

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

        int   type      =  UNEXPECTED; //Что это вообще такое
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
                {NUMBER         , "NUMBER"        },
                {IDENTIFIER     , "IDENTIFIER"    },
                {LEFTPAREN      , "LEFTPAREN"     },
                {RIGHTPAREN     , "RIGHTPAREN"    },
                {LEFTSQUARE     , "LEFTSQUARE"    },
                {RIGHTSQURE     , "RIGHTSQURE"    },
                {LEFTCURLY      , "LEFTCURLY"     },
                {RIGHTCURLY     , "RIGHTCURLY"    },
                {LEFTCOMMENT    , "LEFTCOMMENT"   },
                {RIGHTCOMMENT   , "RIGHTCOMMENT"  },
                {LESSTHAN       , "LESSTHAN"      },
                {GRESTERTHAN    , "GRESTERTHAN"   },
                {EQUAL          , "EQUAL"         },
                {PLUS           , "PLUS"          },
                {MINUS          , "MINUS"         },
                {SLASH          , "SLASH"         },
                {HASH           , "HASH"          },
                {DOT            , "DOT"           },
                {COMMA          , "COMMA"         },
                {COLON          , "COLON"         },
                {SEMICOLON      , "SEMICOLON"     },
                {SINGLEQUATE    , "SINGLEQUATE"   },
                {DOUBLEQUOTE    , "DOUBLEQUOTE"   },
                {COMMENT        , "COMMEMT"       },
                {PIPE           , "PIPE"          },
                {END            , "END"           },
                {POW            , "POW"           },
                {MULTIPLICATION , "MULTIPLICATION"},
                {DIVISION       , "DIVISION"      },
                {NOTEQUAL       , "NOTEQUAL"      },
                {ASSIGNMENT     , "ASSIGNMENT"    },
                {LINE           , "LINE"          },
                {START          , "START"         },
                {PAREN          , "PAREN"         },
                {CURLY          , "CURLY"         },
                {SQUARE         , "SQUARE"        },
                {UNEXPECTED     , "UNEXPECTED"    },


        };

    private:
        AbstractSyntaxTree* container = nullptr;                   // what does AST have this Node.
    };

    AbstractSyntaxTree ();
    ~AbstractSyntaxTree();

    int dumper(const char* filename, int mode, const char* title); // Do PND

    Node* createNode(int type, int   ivalue);
    Node* createNode(int type, float fvalue);
    Node* createNode(int type, char* svalue);                      //Create Node and tie to this AST

    Node* head = nullptr;                                          //root AST( From this start program)

private:
    unsigned long long int nodes_count = 0;                        //Counts of Nodes belongs to Whis AST
};


typedef AbstractSyntaxTree AST;
typedef AST::Node          ASN;


bool isLetter (char  symbol);
bool isNumber (char  symbol);
bool isOperand(char  symbol);
bool isEnd    (char  symbol);

bool isInteger(char* string);
bool isFloat  (char* string);



