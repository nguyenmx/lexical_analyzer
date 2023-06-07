#include "Lexer.h"
#include <iostream>

int main() {
  
   // Create the Lexer object
  Lexer lex{ "test.txt" };

  do {
    
    int tok = lex.lex();   // Retrieve next token
    std::string text = lex.getLexeme();  // Get corresponding lexeme

    // Print the token code and lexeme
    std::cout << "(" << tok << ") " << text << "\n";

  } while( lex.getNextToken() != END_OF_INPUT );
}