#include "token.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <string>

// Default constructor for TokenString class
TokenString::TokenString() {
    this->splitInputString = {{}};
    this->tokenStrings = {{}};
}

// Method to get token strings
std::vector<std::vector<std::string>> TokenString::getTokenStrings() {
    return tokenStrings;
}

// Method to tokenize input string
void TokenString::tokenize(std::string input) {
    for (int i = 0; (unsigned int) i < input.length(); i++) {
        std::vector<std::string> expressionTokenString = {};
        std::vector<std::string> expressionSplitString = {};
        switch (input[i]) {
            case ' ':
                break;
            case '\r':
            case '\n':
                // Push the tokenized and split strings to their respective vectors
                splitInputString.push_back(expressionSplitString);
                tokenStrings.push_back(expressionTokenString);
                break;
            case '(':
                splitInputString.back().push_back("(");
                tokenStrings.back().push_back("BRACKET_OPEN");
                break;
            case ')':
                splitInputString.back().push_back(")");
                tokenStrings.back().push_back("BRACKET_CLOSE");
                break;
            case '\\':
                splitInputString.back().push_back("\\");
                tokenStrings.back().push_back("BACKSLASH");
                break;
            default: 
                tokenizeHelperVariableCase(i, input);
                tokenStrings.back().push_back("VARIABLE");
        }
    }
}

// Helper method to handle variable tokenization
void TokenString::tokenizeHelperVariableCase(int &i, std::string input) {
    // Throw error if variable does not start with a letter
    if (!(input[i]  >= 'A' && input[i] <= 'Z') && !(input[i]  >= 'a' && input[i] <= 'z')) {
        throw std::runtime_error("Error: Variable not starting with letter from latin alphabet");
    }

    std::string variableString = "";
    // Continue adding to variable string as long as alphanumeric characters are encountered
    while ((input[i]  >= 'A' && input[i] <= 'Z') || (input[i]  >= 'a' && input[i] <= 'z') || (input[i]  >= '0' && input[i] <= '9')) {
        variableString += input[i];
        i++;
    } 
    // Push the variable string to the split input string vector
    splitInputString.back().push_back(variableString);

    i--;
}

// Method to print the tokenized strings
void TokenString::print() {
    std::string s;

    for (int i = 0; (unsigned int) i < splitInputString.size(); i++) {
        for (int j = 0; (unsigned int) j < splitInputString[i].size(); j++) {
            s = splitInputString[i][j];
            std::cout << s;

            if (s != "(" && s != "\\") {
                if ((unsigned int) j+1 < splitInputString[i].size() &&
                    splitInputString[i][j+1] != ")" && splitInputString[i][j+1] != "(")
                    std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Method to disambiguate all strings in the tokenStrings vector
void TokenString::disambiguateStrings() {
    int j = 0;
    int varCount = 0;

    // Loop through each string in the tokenStrings vector
    for (int i = 0; (unsigned int) i < getTokenStrings().size(); i++) {
      disambiguateString(i, j, varCount);
      j = 0;
      varCount = 0;
    }
}

// Method to disambiguate a single string in the tokenStrings vector
void TokenString::disambiguateString(int& i, int& j, int& varCount) {
    if (varCount >= 3) {
        putBrackets(i, j, varCount);
    }
    if ((unsigned int) j < tokenStrings[i].size() && tokenStrings[i][j] == "VARIABLE") { 
        j++;
        varCount++;
        disambiguateString(i, j, varCount);
    }
    else {
        varCount = 0;
        
        if ((unsigned int) j < tokenStrings[i].size() && tokenStrings[i][j] == "BACKSLASH") {
            tokenStrings[i].insert(tokenStrings[i].begin() + j, "BRACKET_OPEN");
            tokenStrings[i].insert(tokenStrings[i].end(), "BRACKET_CLOSE"); //lambda means everything else after backslash
            
            splitInputString[i].insert(splitInputString[i].begin() + j, "(");
            splitInputString[i].insert(splitInputString[i].end(), ")");
            j += 2;
            disambiguateString(i, j, varCount);
        }
        j += 2;
    } 
}

// Method to put brackets around a sequence of variables
void TokenString::putBrackets(int i, int& j, int varCount) {
    int add = 0;

    if (varCount >= 4)
        add = varCount - 3;
    if (tokenStrings[i][j-varCount-add-1] == "BACKSLASH")
        return;
    tokenStrings[i].insert(tokenStrings[i].begin() + j-varCount-add, "BRACKET_OPEN");
    tokenStrings[i].insert(tokenStrings[i].begin() + j, "BRACKET_CLOSE");

    splitInputString[i].insert(splitInputString[i].begin() + j-varCount-add, "(");
    splitInputString[i].insert(splitInputString[i].begin() + j, ")");
    j += 2;
}