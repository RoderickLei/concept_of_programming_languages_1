#include <lexer.h>
#include <stdexcept>
#include <string>
#include <iostream>

// Default constructor for Lexer class
Lexer::Lexer(){}

// Constructor for Lexer class that takes a vector of strings as input
Lexer::Lexer(std::vector<std::string> expression){
    this->expression = expression;
}

void Lexer::expr(){
    lexpr();
    expr1();
}

void Lexer::expr1(){
    if (!isEmpty() && !(peek() == "BRACKET_CLOSE" && openBrackets > 0)) {
        lexpr();
        expr1();
    }
}

void Lexer::lexpr(){
    if (!isEmpty() && peek() == "BACKSLASH") {
        consume();
        if (!isEmpty() && peek() == "VARIABLE") {
            consume();
            if (isEmpty()) throw std::runtime_error("Error: Missing expression after lambda abstraction");
            expr(); 
        } else {
            throw std::runtime_error("Error: Missing variable after lambda");
        }
    } else {
        pexpr();
    }
}

void Lexer::pexpr(){
    if (!isEmpty() && peek() == "BRACKET_OPEN") {
        consume();
        openBrackets++;
        if (isEmpty() || (!isEmpty() && peek() == "BRACKET_CLOSE")) throw std::runtime_error("Error: Missing expression after opening parenthesis");
        expr();
        if (!isEmpty() && peek() == "BRACKET_CLOSE") {
            consume();
            openBrackets--;
        } else {
            throw std::runtime_error("Error: Missing closing parenthesis");
        }

    } else if (!isEmpty() && peek() == "VARIABLE") {
        consume();
    } else {
        throw std::runtime_error("Error: Missing variable");
    }
}

// Method to check if the expression is empty
bool Lexer::isEmpty() {
    return ((unsigned int) index >= expression.size());
}

// Method to peek at the next token in the expression
std::string Lexer::peek() {
    return expression[index];
}

// Method to move to the next token in the expression
void Lexer::consume() {
    index++;
}