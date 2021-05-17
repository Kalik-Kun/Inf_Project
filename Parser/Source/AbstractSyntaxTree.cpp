
#include "../Headers/AbstractSyntaxTree.h"

ASN::Node(int type, int ivalue) {
    if (type != Number) {
        std::cerr << "ERROR\nfile: AbstractSyntaxTree.cpp\n"
                     " in func: ASN::Node(int, int)\n types is not equal\n";
        throw(1);
    }

    this->type = type;
    this->ivalue = ivalue;
    this->data_type = INT_TYPE;
}

ASN::Node(int type, float fvalue)
{
    if (type != Number) {
        std::cerr << "ERROR\nfile: AbstractSyntaxTree.cpp\n"
                     " in func: ASN::Node(int, int)\n types is not equal\n";
        throw(1);
    }
    this->fvalue = fvalue;
    this->type = type;
    this->data_type = FLOAT_TYPE;
}

ASN::Node(int type, char* svalue) {
    this->type = type;
    this->svalue = svalue;

//    if (isInteger(svalue))
//    {
//        this->ivalue = atoi(svalue);
//        this->data_type = INT_TYPE;
//    }
//    else if (isFloat(svalue))
//    {
//        this->fvalue = atoi(svalue);
//        this->data_type = FLOAT_TYPE;
//    }
//    else
//    {
//        this->svalue = svalue;
//        this->data_type = CHAR_TYPE;
//    }

}

ASN::~Node() {
    if (this -> left)
        delete this -> left;

    if (this -> right)
        delete this -> right;

    if (this -> svalue)
        delete[] this -> svalue;


    if (this -> container)
        (this -> container -> nodes_count)--;
}

void ASN::flush() {
    this->type = Unexpected;
    this->fvalue = 0;
    this->ivalue = 0;

    if(this->svalue) {
        delete this -> svalue;
        this -> svalue = nullptr;
    }

}

void ASN::leftConnect(ASN *left)
{
    this -> left = left;
    if (left)
    {
        left -> parent = this;
        if (this -> container)
        {
            if (this -> left -> container != this -> container)
            {
                this -> container -> nodes_count += 1;
                this -> left -> container = this -> container;
            }
            left -> fixContainer();
        }
    }
}

void ASN::rightConnect(ASN *right)
{
    this -> right = right;
    if (right)
    {
        right -> parent = this;
        if (this -> container)
        {
            if (this -> right -> container != this -> container)
            {
                this -> container -> nodes_count += 1;
                this -> right -> container = this -> container;
            }
            right -> fixContainer();
        }
    }
}

void ASN::fixContainer()
{
    if (this -> right)
    {
        if (this -> right -> container != this -> container)
        {
            this -> container -> nodes_count += 1;
            this -> right -> container = this -> container;
        }
        this -> right -> fixContainer();
    }

    if (this -> left)
    {
        if (this -> left -> container != this -> container)
        {
            this -> container -> nodes_count += 1;
            this -> left -> container = this -> container;
        }
        this -> left -> fixContainer();
    }
}





// Рисуем наш граф

const char* ASN::colorize()
{
    if (this -> type == START or this -> type == Identifier)
        return "green";

    else if (this -> type == Line)
        return "lightgray";

    else if (this -> type == Plus or this -> type == Minus or
             this -> type == MULTIPLICATION or this -> type == DIVISION or
             this -> type == POW)
        return "pink";

    else if (this -> type == Equal or this -> type == NotEqual or
             this -> type == LessThan or this -> type == GreaterThan)
        return "\"#F8AEFF\"";


    else if (this -> type == Number and this -> data_type == INT_TYPE)
        return "\"#D083FF\"";

    else if (this -> type == Number and this -> data_type == FLOAT_TYPE)
        return "\"#FF89A9\"";

    else if (this -> type == Identifier)
        return "\"#64ADFF\"";

//    else if (this -> type == FUNCCALL)
//        return "\"#0B8AFF\"";

    else
        return "white";
}


void ASN::print()
{
    if (this -> type == Unexpected)
    {
        printf("unknown operator");

        if (this -> svalue)
            printf(" (%s)", this -> svalue);
    }

    else if (this -> type == START)
        printf("START");

    else if (this -> type == Line)
        printf("%s", this -> svalue);

//    else if (this -> type == FUNC)
//        printf("function %s", this -> svalue);

    else if (this -> type == Identifier)
        printf("%s", this->svalue);

    else if (this -> type == Number)
        printf("%s", this -> svalue);

}



void ASN::write(std::ofstream& out)
{
    if (this -> type == Unexpected)
    {
        out << "unknown";

        if (this -> svalue)
            out << " | " << this -> svalue;
    }

    else if (this -> type == START)
        out << "START";

    else if (this -> type == Line)
    {
        out << "line ";
        out << " | " << this -> svalue;
    }

//    else if (this -> type == FUNC)
//        out << "function | " << this -> svalue << " | { Mem | " << this -> ivalue << " } ";


    else
        out << this -> Lexem_map[this -> type] << " | " << this -> svalue;
}


int AST::dumper(const char* filename, int mode, const char* title)
{
    char* cmd = new char[2 * strlen(filename) + 1 + 8 + 29];
    strcpy(cmd, filename);
    strcat(cmd, ".txt");
    std::ofstream file;
    file.open(cmd);
    file << "digraph G{\n";
    file << "graph [label=\"" << title << "\", labelloc=top, fontsize=30]";
    file << "root [shape = box, style = filled, fillcolor = orange, color = black,"
            " label = \" Root = " << this -> head << "\"]\n";
    file << "count [shape = box, style = filled, fillcolor = orange,"
            " color = black, label = \" Count of nodes = " << this -> nodes_count << "\"]\n";
    AbstractSyntaxTree::Node* element = this -> head;

    file << (long int) element << " [shape = record, style = filled, fillcolor = "
         << element -> colorize() << ", color = black, label = \" {";

    if ((mode / DETAILED) % 10 == 1)
    {
        file << "<adr> Address: " << element << " | Data: ";
    }

    element -> write(file);

    if ((mode / DETAILED) % 10 == 1)
    {
        file << " |{<left> " << element -> left << " | <right> " << element -> right << "}";
    }

    file << "}\"]\n";

    file << "root -> " << (long int) element << "\n [color = black]";	// element as int

    element -> dumper(file, mode);
    file << "}";
    file.close();

    strcpy(cmd, "dot -Tpng ");
    strcat(cmd, filename);
    strcat(cmd, ".txt -o ");
    strcat(cmd, filename);
    strcat(cmd, ".png");
    int result = system(cmd);

    if ((mode / DELETE_TXT) % 10 == 1)
    {
        strcpy(cmd, "rm ");
        strcat(cmd, filename);
        strcat(cmd, ".txt");
        result = system(cmd);
    }

    if ((mode / SHOW) % 10 == 1)
    {
        strcpy(cmd, "eog ");
        strcat(cmd, filename);
        strcat(cmd, ".png");
        result = system(cmd);
    }

    if ((mode / DELETE_PNG) % 10 == 1)
    {
        strcpy(cmd, "rm ");
        strcat(cmd, filename);
        strcat(cmd, ".png");
        result = system(cmd);
    }

    delete[] cmd;

    return 0;
}



int ASN::dumper(std::ofstream& file, int mode)
{

    if (this -> left)
    {
        file << (long int) this -> left << " [shape = record, style = filled, fillcolor = "
             << this -> left -> colorize() << ", color = black, label = \" {";

        if ((mode / DETAILED) % 10 == 1)
            file << "<adr> Address: " << this -> left << " | Data: ";

        this -> left -> write(file);

        if ((mode / DETAILED) % 10 == 1)
            file << " | <prev> Prev: " << this << " |{<left> "
                 << this -> left -> left << " | <right> " << this -> left -> right << "}";

        file << "}\"]\n";

        if ((mode / DETAILED) % 10 == 1)
        {
            file << (long int) this << ":<left> -> " << (long int) this -> left
                 << " [color = black]\n";
            file << (long int) this -> left << ":<prev> -> " << (long int) this
                 << " [color = gray]\n";
        }

        else
            file << (long int) this << " -> " << (long int) this -> left
                 << " [color = black]\n";

        this -> left -> dumper(file, mode);
    }

    if (this -> right)
    {
        file << (long int) this -> right << " [shape = record, style = filled, fillcolor = "
             << this -> right -> colorize() << ", color = black, label = \" {";

        if ((mode / DETAILED) % 10 == 1)
            file << "<adr> Address: " << this -> right << " | Data: ";

        this -> right -> write(file);

        if ((mode / DETAILED) % 10 == 1)
            file << " | <prev> Prev: " << this << " |{<left> " << this -> right -> left
                 << " | <right> " << this -> right -> right << "}";

        file << "}\"]\n";

        if ((mode / DETAILED) % 10 == 1)
        {
            file << (long int) this << ":<right> -> " << (long int) this -> right
                 << " [color = black]\n";
            file << (long int) this -> right << ":<prev> -> " << (long int) this
                 << " [color = gray]\n";
        }

        else
            file << (long int) this << " -> " << (long int) this -> right
                 << " [color = black]\n";

        this -> right -> dumper(file, mode);
    }

    return 0;
}








// Деревья все такое

AbstractSyntaxTree::AbstractSyntaxTree()
{
    this -> head = nullptr;
    this -> nodes_count = 0;
}

AbstractSyntaxTree::~AbstractSyntaxTree()
{
    if (this -> head)
        delete this -> head;
}


ASN* AST::createNode(int type, int ivalue)
{
    Node* new_node = new Node(type, ivalue);

    if (new_node->type == ASN::Unexpected)
    {
        delete new_node;
        return nullptr;
    }

    this->nodes_count++;
    new_node->container = this;
    if(not this->head)
        this->head = new_node;

    return new_node;
}

ASN* AST::createNode(int type, float fvalue)
{
    Node* new_node = new Node(type, fvalue);

    if (new_node->type == ASN::Unexpected)
    {
        delete new_node;
        return nullptr;
    }

    this->nodes_count++;
    new_node->container = this;
    if(not this->head)
        this->head = new_node;

    return new_node;
}

ASN* AST::createNode(int type, char* svalue)
{
    Node* new_node = new Node(type, svalue);

    if (new_node->type == ASN::Unexpected)
    {
        delete new_node;
        return nullptr;
    }

    this->nodes_count++;
    new_node->container = this;
    if(not this->head)
        this->head = new_node;

    return new_node;
}




bool isLetter(char symbol)
{
    return ((symbol >= 'A' and symbol <= 'Z') or (symbol >= 'a' and symbol <= 'z') or symbol == '.' or symbol == '_' or symbol == '\'' or symbol == '\"');
}

bool isNumber(char symbol)
{
    return ((symbol >= '0' and symbol <= '9'));
}

bool isOperand(char symbol)
{
    return (symbol == '>' or symbol == '<' or symbol == '=' or symbol == '!' or \
			symbol == '+' or symbol == '-' or symbol == '*' or symbol == '/' or \
			symbol == '%' or symbol == '|' or symbol == '&' or symbol == '^');
}

bool isEnd(char symbol)
{
    return (symbol == ' ' or symbol == '\t' or symbol == '\n' or symbol == '\0' or
            symbol == '(' or symbol == ')' or symbol == ',');
}

bool isInteger(char* string)
{
    bool result = true;

    while (*string != '\0')
    {
        if (not (isNumber(*string)))
            result = false;
        string++;
    }

    return result;
}

bool isFloat(char* string)
{
    bool result = true;

    while (*string != '\0')
    {
        if (not (isNumber(*string) or *string == '.'))
            result = false;
        string++;
    }

    return result;
}



