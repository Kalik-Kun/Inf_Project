#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <cstring>
#include "Defines.h"
#include "debug.h"

// lexems type of AST
enum  TypeLexem{
    NUMBER,                 // Number
    IDENTIFIER,             // variable or anther reserved world
    FUNC,                   // smth func
    ARRAY,                  // smth arrays
    LEFTPAREN,              // (
    RIGHTPAREN,             // )
    LEFTSQUARE,             // [
    RIGHTSQURE,             // ]
    LEFTCURLY,              // {
    RIGHTCURLY,             // }
    LEFTCOMMENT,            // /*
    RIGHTCOMMENT,           // */
    LESSTHAN,               // <
    GRESTERTHAN,            // >
    EQUAL,                  // ==
    PLUS,                   // +
    MINUS,                  // -
    //ASTERISK,               // *
    SLASH,                  //                          хуй его знает
    HASH,                   //                          хуй его знает
    DOT,                    // .
    COMMA,                  // ,
    COLON,                  // ;
    SEMICOLON,              // :
    SINGLEQUATE,            // ' '
    DOUBLEQUOTE,            // " "
    COMMENT,                // commentary
    PIPE,                   //                          хуй его знает
    POW,                    // ^
    MULTIPLICATION,         // a * b == multiplication
    DIVISION,               // A/B - Division
    NOTEQUAL,               // !=
    ASSIGNMENT,             // =
    LINE,                   // begin of line
    START,                  // Begging the program
    PAREN,                  // Скобки законченые ()
    CURLY,                  // {}
    SQUARE,                 // []
    UNEXPECTED,             // don't know what is it
    END,                    // End
};


// Class Lexer search input file and sort world  into king of lexemes
class Lexer {

private:

    std::pair<int, char*> *data = nullptr;         // this my stack(sure, array of pair)
    long size_data              = 0;               // this is size stack(array of pair in my case)

public:
    Lexer  ();                                     // first class constructor
    Lexer  (std::ifstream& fin);                   // second class constructor sort world into king of lexemes
    ~Lexer ();                                     // class's destructor

    void expand_value  (std::pair<int, char*>);     // expand one more lexemes in stack(array of pair in my case)
    void get_lexemes   (std::string& );             // find lexemes in line
    std::pair<int, char*>* get_data();
    long get_size_data();

    friend std::ostream& operator<< (std::ostream&, const Lexer&);






private:
    // help func for understood

    bool is_digit           (char);                 // define a number in my lang
    bool is_identifier_char (char);                 // define a reserved worlds in my lang
    bool is_space           (char);                 // define a space in  my lang (space don't write in lexemes



    // lexems
    // странная хуйня перепроверь в инете
    void its_identifier (_ITER_SIMB*, std::string&); // Write a reserved world in stack(array of pair in my case)
    void its_number     (_ITER_SIMB*, std::string&); // Write a number in stack(array of pair in my case)
    void its_other      (_ITER_SIMB*, std::string&); // write a other kind of Lexemes in stack(array of pair in my case)


};

// it use that expand our array with data





