#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

class OpenFileError {};

class SyntaxError {};

enum command_t
{
    C_ARITHMETIC, C_PUSH, C_POP, C_LABEL,
    C_GOTO, C_IF, C_FUNCTION, C_RETURN, C_CALL
};

class Parser
{
    ifstream prog;
    string currentLine;
    command_t type;
    string cmd, arg_1;
    int arg_2;

public:
    Parser(string fileName);
    bool hasMoreCommands();
    void advance();
    command_t commandType();
    string arg1();
    int arg2();
    ~Parser();
};

class CodeWriter
{
    int label_num;
    ofstream out;
    string vmFileName;
    string functionName;
    void gotoAddress(const string &segment, int index);

public:
    CodeWriter(string asmFileName);
    void setFileName(string fileName);
    void writeInit();
    void writeArithmetic(string cmd);
    void writePushPop(command_t type, string segment, int index);
    void writeLabel(string label);
    void writeGoto(string label);
    void writeIf(string label);
    void writeCall(string functionName, int numArgs);
    void writeReturn();
    void writeFunction(string functionName, int numLocals);
    void close();
    ~CodeWriter();
};