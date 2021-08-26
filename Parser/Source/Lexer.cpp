#include "../Headers/Lexer.h"

Lexer::Lexer() {
    this->size_data = 0;
}

Lexer::Lexer(std::ifstream& fin) {
    std::string str;
    this->size_data = 0;
    this->data = nullptr;

    expand_value({START, "START"});

    while (getline(fin, str, _SEPARATOR_)) {
        get_lexemes(str);
        expand_value({LINE, "LINE"});
    }


    expand_value({END, "END"});
}
Lexer::~Lexer() {
    std::cerr << "Lexer deleted" << std::endl;
    this->size_data = 0;
    delete this->data;
}

void Lexer::get_lexemes(std::string& str) {

    for (auto it = str.begin(); it != str.end(); it++) {
        if (is_space(*it))
            continue;
        if (is_digit(*it)) {
            its_number(&it, str);
            continue;
        }
        if(is_identifier_char(*it)) {
            its_identifier(&it, str);
            continue;
        }
        its_other(&it, str);

    }

}

// нужно доработать хуй знает как это сработает
// +  работает хуево откровенно говоря нужно переходить на векторы по хорошему
void Lexer::expand_value(std::pair<int, char*> new_value) {
    this->size_data++;

    if (this->data == nullptr) {
        this->data = new std::pair<int, char*>;
        this->data[0] = new_value;
        return;
    }

    auto new_arr = new std::pair<int, char*>[this->size_data];
    for (long i = 0; i < this->size_data - 1; i ++) {
        new_arr[i] = this->data[i];
    }

    new_arr[this->size_data - 1] = new_value;
    delete this->data;

    this->data = new std::pair<int, char*>[this->size_data];
    for(long i = 0; i < this->size_data; i ++) {
        this->data[i] = new_arr[i];
    }
}

std::ostream& operator<< (std::ostream& in, const Lexer& my_class) {
    in << "This array of Lexemes" << std::endl << std::endl;
    in << "Size array of Lexemes:  " << my_class.size_data << std::endl;
    in << "Array elems: " << std::endl;
    in << "Lexeme     Name" << std::endl;

    for (long i = 0; i < my_class.size_data; i++) {
        if (my_class.data[i].first < 10) {
            in << my_class.data[i].first << "          " << my_class.data[i].second << std::endl;
            continue;
        }
        in << my_class.data[i].first << "         " << my_class.data[i].second << std::endl;
    }

    return in;
}


std::pair<int, char*>* Lexer::get_data() {
    return this->data;
}

long Lexer::get_size_data() {
    return this->size_data;
}













void Lexer::its_identifier(_ITER_SIMB* iter, std::string& str) {
    std::string new_iden;
    auto it = *iter;
    for (; it != str.end() && is_identifier_char(*it); it++) {
        new_iden += *it;
    }

    char* new_iden_char = new char[new_iden.length() + 1];
    strcpy(new_iden_char, new_iden.c_str());
    expand_value({IDENTIFIER, new_iden_char});
    // если мы передаем итератор то мы можем
    // его поменять в функции и он измениться вроде как
    it--; // чтобы считать разделитель
    *iter = it;
}

void Lexer::its_number(_ITER_SIMB *iter, std::string& str) {
    std::string new_iden;
    auto it = *iter;
    bool pointer_dot = false;
    for (; it != str.end() && !pointer_dot
                           && (is_digit(*it) || *it == '.'); it++) {

        if (*it == '.') pointer_dot = true;
        new_iden += *it;

    }

    char* new_iden_char = new char[new_iden.length() + 1];
    strcpy(new_iden_char, new_iden.c_str());
    expand_value({NUMBER, new_iden_char});
    it--;
    *iter = it;
}

void Lexer::its_other(_ITER_SIMB* it, std::string& str) {
    auto iter = *it; (*it)++;
    if (*iter == '=' && **it == '=') {
        expand_value({EQUAL, "=="});
        return;
    }
    if (*iter == '!' && **it == '=') {
        expand_value({NOTEQUAL, "!="});
        return;
    }
    if (*iter == '/' && **it == '/') {
        expand_value({COMMENT, "//"});
        return;
    }
    if (*iter == '/' && **it == '*') {
        expand_value({LEFTCOMMENT, "/*"});
        return;
    }
    if (*iter == '*' && **it == '/') {
        expand_value({LEFTCOMMENT, "*/"});
        return;
    }


    switch (*iter) {
        case '(':
            expand_value({LEFTPAREN, "("});
            break;
        case ')':
            expand_value({RIGHTPAREN, ")"});
            break;
        case '[':
            expand_value({LEFTSQUARE, "["});
            break;
        case ']':
            expand_value({RIGHTSQURE, "]"});
            break;
        case '{':
            expand_value({LEFTCURLY, "{"});
            break;
        case '}':
            expand_value({RIGHTCURLY, "}"});
            break;
        case '<':
            expand_value({LESSTHAN, "<"});
            break;
        case '>':
            expand_value({GRESTERTHAN, ">"});
            break;
        case '+':
            expand_value({PLUS, "+"});
            break;
        case '-':
            expand_value({MINUS, "-"});
            break;
        case '.':
            expand_value({DOT, "."});
            break;
        case ',':
            expand_value({COMMA, ","});
            break;
        case ':':
            expand_value({SEMICOLON, ":"});
            break;
        case ';':
            expand_value({COLON, ";"});
            break;
        case '\'':
            expand_value({SINGLEQUATE, "\'"});
            break;
        case '\"':
            expand_value({DOUBLEQUOTE, "\""});
            break;
        case '^':
            expand_value({POW, "^"});
            break;
        case '*':
            expand_value({MULTIPLICATION, "*"});
            break;
        case '/':
            expand_value({DIVISION, "/"});
            break;
        case '=':
            expand_value({ASSIGNMENT, "="});
            break;
        default:
            expand_value({UNEXPECTED, "UNEXPECTED"});
            break;
    }
    (*it)--;
}

//  переделать
bool Lexer::is_space(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\r':
            return true;
        default:
            return false;
    }
}

// переделать
bool Lexer::is_digit(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

//Переделать
bool Lexer::is_identifier_char(char c) {
    switch (c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '_':
            return true;
        default:
            return false;
    }
}


