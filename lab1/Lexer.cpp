#include "Lexer.h"

using namespace std;

Lexer::Lexer(string filename)
{
    ifstream in;
    string line;

    in.open(filename);
    while (getline(in, line))
    {
        this->data += line + '\n';
    }
    data += '~';
    in.close();

    // define map between ints and automata
    this->num_automaton[0] = "COMMA";
    this->num_automaton[1] = "PERIOD";
    this->num_automaton[2] = "Q_MARK";
    this->num_automaton[3] = "LEFT_PAREN";
    this->num_automaton[4] = "RIGHT_PAREN";
    this->num_automaton[5] = "COLON";
    this->num_automaton[6] = "COLON_DASH";
    this->num_automaton[7] = "MULTIPLY";
    this->num_automaton[8] = "ADD";
    this->num_automaton[9] = "SCHEMES";
    this->num_automaton[10] = "FACTS";
    this->num_automaton[11] = "RULES";
    this->num_automaton[12] = "QUERIES";
    this->num_automaton[13] = "ID";
    this->num_automaton[14] = "STRING";
    this->num_automaton[15] = "COMMENT";
    this->num_automaton[16] = "COMMENT";
    this->num_automaton[17] = "WHITESPACE";
    this->num_automaton[18] = "EOF";
    this->num_automaton[19] = "UNDEFINED";
    this->num_automaton[20] = "UNDEFINED";
    this->num_automaton[21] = "UNDEFINED";

    // initialize line number
    this->line_number = 1;
}

//===== Automata ===== //
vector<int> Lexer::Dliteral(char c)
{
    vector<int> output;
    if (this->data[0] == c)
    {
        output.push_back(1);
    }
    else { output.push_back(0); }

    //no increment of line number
    output.push_back(0);
    return output;
}
vector<int> Lexer::Dword(string str)
{
    vector<int> output;
    if (this->data.substr(0, str.length()) == str)
    {
        output.push_back(str.length());
    }
    else { output.push_back(0); }
    output.push_back(0);
    return output;
}
vector<int> Lexer::Dcomma()
{
    return this->Dliteral(',');
}
vector<int> Lexer::Dperiod()
{
    return this->Dliteral('.');
}
vector<int> Lexer::Dq_mark()
{
    return this->Dliteral('?');
}
vector<int> Lexer::Dleft_paren()
{
    return this->Dliteral('(');
}
vector<int> Lexer::Dright_paren()
{
    return this->Dliteral(')');
}
vector<int> Lexer::Dcolon()
{
    return this->Dliteral(':');
}
vector<int> Lexer::Dcolon_dash()
{
    vector<int> output;
    if (this->data[0] == ':')
    {
        if (this->data[1] == '-')
        {
            output.push_back(2);
        }
        else { output.push_back(0); }
    }
    else { output.push_back(0); }
    output.push_back(0);
    return output;
}
vector<int> Lexer::Dmultiply()
{
    return this->Dliteral('*');
}
vector<int> Lexer::Dadd()
{
    return this->Dliteral('+');
}
vector<int> Lexer::Dschemes()
{
    return this->Dword("Schemes");
}
vector<int> Lexer::Dfacts()
{
    return this->Dword("Facts");
}
vector<int> Lexer::Drules()
{
    return this->Dword("Rules");
}
vector<int> Lexer::Dqueries()
{
    return this->Dword("Queries");
}
vector<int> Lexer::Did()
{
    vector<int> output;
    int id_counter = 0;
    if (isalpha(this->data[0]))
    { // first character is alpha, increment character count
        id_counter++;
        for (char &c : this->data.substr(1))
        {
            if (isalnum(c))
            {  // read any alphanumeric character
                id_counter++;
            }
            else 
            { 
                output.push_back(id_counter);
                break;
            }
        }
    }
    else { output.push_back(0); }
    output.push_back(0);
    return output;
}
vector<int> Lexer::Dstring()
{
    vector<int> output;
    int str_counter = 0;
    int line_counter = 0;
    if (this->data[0] == '\'')
    {
        str_counter++;
        for (unsigned int i = 1; i < this->data.length(); i++)
        {
            if (i == this->data.length()-1)
            {  // EOF character => invalid
                output.push_back(0);
            }
            else if (this->data[i] == '\n')
            {  // increment line count and character count.
                line_counter++;
                str_counter++;
            }
            else if (this->data[i] == '\'')
            {  // end of string found, or an escaped apostrophe.
                str_counter++;
                if (this->data[i + 1] == '\'')
                {  // found escaped apostrophe, increment i and character count.
                    str_counter++;
                    i++;
                }
                else
                {  // end of string.
                    output.push_back(str_counter);
                    break;
                }
            }
            else
            {  // any other character.
                str_counter++;
            }
        }
    }
    else { output.push_back(0); }
    output.push_back(line_counter);
    return output;
}
vector<int> Lexer::Dsingle_comment()
{
    vector<int> output;
    int comment_counter = 0;
    if (this->data.substr(0, 2) == "#|")
    { // this is a multiline comment, not a single
        output.push_back(0);
    }
    else if (this->data[0] == '#')
    { // single comment
        comment_counter++;
        for (char &c : this->data.substr(1))
        {
            if (c == '\n')
            { // end of comment (but don't read the \n)
                output.push_back(comment_counter);
                break;
            }
            else
            { // any other character
                comment_counter++;
            }
        }
    }
    else { output.push_back(0); }
    output.push_back(0); // line will never be incremented
    return output;
}
vector<int> Lexer::Dmulti_comment()
{
    vector<int> output;
    int counter = 0;
    int line_counter = 0;
    if (this->data[0] == '#')
    {
        if (this->data[1] == '|')
        {  // multiline comment
            counter += 2;
            for (unsigned int i = 2; i < this->data.length(); i++)
            {
                if (this->data[i] == '|')
                {  // found |
                    counter++;
                    if (this->data[i+1] == '#')
                    { // is the next character a #?
                        counter++;
                        output.push_back(counter);
                        break;
                    }
                }
                else if (this->data[i] == '\n')
                {  // increment line and character count
                    line_counter++;
                    counter++;
                }
                else if (i == this->data.length()-1)
                {  // hit end of file => invalid
                    output.push_back(0);
                    break;
                }
                else
                {  // any other character
                    counter++;
                }
            }
        }
    }
    else
    {
        output.push_back(0);
    }
    output.push_back(line_counter);
    return output;
}
vector<int> Lexer::Dwhitespace()
{
    vector<int> output;
    int new_line = 0;

    if (isspace(this->data[0]))
    {
        if (data[0] == '\n')
        { // increment line
            new_line++;
        }
        output.push_back(1); // read one character
    }
    else { output.push_back(0); }
    output.push_back(new_line);
    return output;
}
vector<int> Lexer::Dstring_undef()
{
    vector<int> output;
    int str_counter = 0;
    int line_counter = 0;
    if (this->data[0] == '\'')
    {
        str_counter++;
        for (unsigned int i = 1; i < data.length(); i++)
        {
            if (i == this->data.length()-1)
            { // don't read the EOF character, but return how many characters
              // were read previously.
                output.push_back(str_counter);
            }
            else if (data[i] == '\n')
            { // increment line count and character count
                line_counter++;
                str_counter++;
            }
            else if (data[i] == '\'')
            { // potential string ending
                str_counter++;
                if (data[i + 1] == '\'')
                { // escaped apostrophe found, move on.
                    str_counter++;
                    i++;
                }
                else
                { // valid string found, reject
                    output.push_back(0);
                    break;
                }
            }
            else
            {  // any other character
                str_counter++;
            }
        }
    }
    else { output.push_back(0); }
    output.push_back(line_counter);
    return output;
}
vector<int> Lexer::Dcomment_undef()
{
    vector<int> output;
    int counter = 0;
    int line_counter = 0;
    if (this->data[0] == '#')
    {
        if (this->data[1] == '|')
        { // multiline comment
            counter += 2;
            for (unsigned int i = 2; i < this->data.length(); i++)
            {
                if (this->data[i] == '|')
                { // potentially found the end
                    counter++;
                    if (this->data[i + 1] == '#')
                    { // found end of valid comment => reject
                        counter++;
                        output.push_back(0);
                        break;
                    }
                }
                else if (this->data[i] == '\n')
                { // increment line and character count
                    line_counter++;
                    counter++;
                }
                else if (i == this->data.length()-1)
                { // found EOF, return count (but don't read EOF character)
                    output.push_back(counter);
                    break;
                }
                else
                { // any other character
                    counter++;
                }
            }
        }
    }
    else
    {
        output.push_back(0);
    }
    output.push_back(line_counter);
    return output;
}
vector<int> Lexer::Deof()
{
    vector<int> output;
    if (this->data[0] == '~' && this->data.length() == 1)
    {
        output.push_back(1);
    }
    else { output.push_back(0); }
    output.push_back(0);
    return output;
}
vector<int> Lexer::Dchar_undef()
{  // if everything else is 0, this will get chosen
    vector<int> output;
    output.push_back(1);  // one character will be called undefined
    output.push_back(0);
    return output;
}

//======= Generating Tokens =======//

void Lexer::generate_tokens()
{  // populate this->tokens with tokens
    while (this->data != "")
    {
        Token t = this->gen_token();
        if (t.type != "WHITESPACE")
        {
            if (t.type == "EOF")
            {
                t.chars = "";
            }
            this->tokens.push_back(t);
        }
    }
}
Token Lexer::gen_token()
{
    // see how many characters each automaton can read.
    vector<vector<int>> read = this->chars_read();

    // decide which automaton read the most.
    int index = find_max(read);

    // store the characters that were read.
    string characters = this->data.substr(0, read[index][0]);

    // delete the characters that were read.
    this->data = this->data.substr(read[index][0]);

    string label = this->num_automaton[index];

    // initialize token
    Token t = Token(label, characters, this->line_number);

    // increment line_number if necessary.
    this->line_number += read[index][1];

    return t;
}
int Lexer::find_max(vector<vector<int>> list)
{ // finds the maximum number and the minimum index
    int max_value = list[0][0];
    int index = 0;
    for (unsigned int i = 0; i < list.size(); i++)
    {
        if (list[i][0] > max_value)
        {
            max_value = list[i][0];
            index = i;
        }
    }

    return index;
}
vector<vector<int>> Lexer::chars_read()
{ // creates the list of characters read
    vector<vector<int>> output;
    output.push_back(this->Dcomma());
    output.push_back(this->Dperiod());
    output.push_back(this->Dq_mark());
    output.push_back(this->Dleft_paren());
    output.push_back(this->Dright_paren());
    output.push_back(this->Dcolon());
    output.push_back(this->Dcolon_dash());
    output.push_back(this->Dmultiply());
    output.push_back(this->Dadd());
    output.push_back(this->Dschemes());
    output.push_back(this->Dfacts());
    output.push_back(this->Drules());
    output.push_back(this->Dqueries());
    output.push_back(this->Did());
    output.push_back(this->Dstring());
    output.push_back(this->Dsingle_comment());
    output.push_back(this->Dmulti_comment());
    output.push_back(this->Dwhitespace());
    output.push_back(this->Deof());
    output.push_back(this->Dstring_undef());
    output.push_back(this->Dcomment_undef());
    output.push_back(this->Dchar_undef());
    return output;
}
string Lexer::toStr()
{  // print details of this->tokens.
    stringstream ss;
    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        ss << tokens[i].toStr() << '\n';
    }
    ss << "Total Tokens = " << tokens.size();
    return ss.str();
}
