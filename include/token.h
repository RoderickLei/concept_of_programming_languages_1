#ifndef TokenHVar
#define TokenHVar

#include <vector>
#include <string>

class TokenString {
    public:
        /**
         * @brief Default constructor for the TokenString class.
         */
        TokenString();

        /**
         * @brief Retrieves the tokenized expressions.
         * 
         * @return A 2D vector containing the tokenized expressions.
         */
        std::vector<std::vector<std::string>> getTokenStrings();

        /**
         * @brief Breaks down the input string into tokens.
         * 
         * @param input The string to be tokenized.
         */
        void tokenize(std::string input);

        /**
         * @brief Helper function to handle variable token creation.
         * 
         * @param i Current index in the input string.
         * @param input The string being tokenized.
         */
        void tokenizeHelperVariableCase(int &i, std::string input);

        /**
         * @brief disambiguates an expression string line into output
         * 
         * @param i Index of the expression line.
         * @param j Index of the token within the expression line.
         * @param varCount Number of consecutive variables.
         */
        void disambiguateString(int& i, int& j, int& varCount);

        /**
         * @brief disambiguates all expression strings of file
         */
        void disambiguateStrings();

        /**
         * @brief Encloses a sequence of variables in parentheses.
         * 
         * @param i Index of the expression line.
         * @param j Index of the token within the expression line.
         * @param varCount Number of consecutive variables.
         */
        void putBrackets(int i, int& j, int varCount);

        /**
         * @brief prints out the output
         */
        void print();

    private:
        int index = 0;
        std::vector<std::vector<std::string>> splitInputString; // The input string split into lines and tokens.
        std::vector<std::vector<std::string>> tokenStrings; // The tokenized expressions.
};

#endif