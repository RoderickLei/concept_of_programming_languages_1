#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "token.h"
#include "lexer.h"

void openReadFile(std::ifstream &readFile, std::string readFileName) {
  readFile.open(readFileName);
  
  if (!readFile) { // file couldn't be opened
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "File: " << readFileName << " could not be opened"
              << std::endl;
    std::cerr << "Error: file could not be opened" << std::endl;
    readFile.close();
  }
}

int main(int argc, char* argv[]) {
    std::ifstream lambdaExpressionReadFile;
    openReadFile(lambdaExpressionReadFile, argv[1]);
    std::string result = "";
    
    if (lambdaExpressionReadFile.is_open()) {
        char symbol;
        while (lambdaExpressionReadFile.get(symbol)) {
            result += symbol;
        }
    }
    TokenString *t = new TokenString();
    int errorLine = 1;

    try {
      t->tokenize(result);

      for (int i = 0; (unsigned int) i < t->getTokenStrings().size(); i++) {
        Lexer *l = new Lexer(t->getTokenStrings()[i]);  
        l->expr();
        errorLine++;
      }
    } catch (const std::runtime_error& error) {
      // your error handling code here
      std::cout << error.what() << "\nFound at expression " << errorLine << std::endl;
      return 1;
    }
    t->disambiguateStrings();
    t->print();

    return 0;
}