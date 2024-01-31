#ifndef LEXER
#define LEXER

#include <token.h>
#include <vector>
#include <string>

/**
 * @brief The Lexer class is responsible for tokenizing and parsing an expression.
 */
class Lexer {
    public:
        /**
         * @brief Default constructor for the Lexer class.
         */
        Lexer();

        /**
         * @brief Overloaded constructor that initializes the Lexer with a list of tokens.
         * 
         * @param expression A list of tokens to be parsed.
         */
        Lexer(std::vector<std::string> expression);

        /**
         * @brief Method for processing the 'expr' grammar rule.
         */
        void expr();

        /**
         * @brief Method for processing the 'expr1' grammar rule.
         */
        void expr1();

        /**
         * @brief Method for processing the 'lexpr' grammar rule.
         */
        void lexpr();

        /**
         * @brief Method for processing the 'pexpr' grammar rule.
         */
        void pexpr();

        /**
         * @brief Checks if all tokens have been processed.
         * 
         * @return true if all tokens have been processed.
         * @return false if there are still tokens left to process.
         */
        bool isEmpty();

        /**
         * @brief Returns the current token without consuming it.
         * 
         * @return The current token.
         */
        std::string peek();

        /**
         * @brief Moves to the next token in the list.
         */
        void consume();
        
    private:
        int index = 0; // The current position
        int openBrackets = 0; // The number of open brackets
        std::vector<std::string> expression;
};

#endif