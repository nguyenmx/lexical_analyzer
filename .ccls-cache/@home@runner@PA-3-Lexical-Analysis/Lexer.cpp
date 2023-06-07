#include "Lexer.h"
using std::string;
#include <iostream>
#include <cctype>
#include <cstdlib>

Lexer::Lexer( const string & fileName ): 
    nextToken{END_OF_INPUT}, charClass{UNKNOWN}, nextChar{' '} {
  inputStream.open( fileName.c_str(), std::ifstream::in ); 
  if( !inputStream ) {
    std::cout << "Unable to open file: " << fileName << "\n";
    exit(1);
  }
}

Lexer::~Lexer() {
  inputStream.close();
}

int Lexer::getNextToken() const {
  return nextToken;
}

string Lexer::getLexeme() const {
  return lexeme;
}

// lookup - a function to lookup operators and parentheses
//          and return the token
int Lexer::lookup(char ch)
{
   switch( ch )
  {
    case '(': 
      addChar(); 
      nextToken=LEFT_PAREN; 
      break;
    case ')': 
      addChar(); 
      nextToken=RIGHT_PAREN; 
      break;
    case '+': 
      addChar(); 
      nextToken=ADD_OP; 
      break;
    case '-': 
      addChar(); 
      nextToken=SUB_OP; 
      break;
    case '*': 
      addChar(); 
      nextToken=MULT_OP; 
      break;
    case '/': 
      addChar(); 
      nextToken=DIV_OP; 
    case '=':
      addChar();
      nextToken = ASSIGN_OP;
      break;
    default:  
      addChar(); 
      nextToken=END_OF_INPUT; 
      break;
  }
  return nextToken;
}

// addChar() - a function to add nextChar to lexeme
void Lexer::addChar()
{
  lexeme.push_back(nextChar);
}

// getChar() - a function to get the next character of
//             input and determine its character class
void Lexer::getChar()
{
  nextChar = inputStream.get();

  if( inputStream.good() ) {
    if( isalpha(nextChar)) charClass=LETTER;
    else if( isdigit(nextChar) ) charClass=DIGIT;
    else charClass=UNKNOWN; 
  } else {
    charClass = END_OF_INPUT;
  }
}

// getNonBlank - a function to call getChar until it
//               returns a non-whitespace character
void Lexer::getNonBlank()
{
  while( isspace(nextChar) ) {
    getChar();
    }
}

// lex() - a simple lexical analyzer
int Lexer::lex()
{
  getNonBlank();
  lexeme = "";

  switch( charClass )
  {
    case LETTER: 
        addChar(); 
        getChar(); 
        while( charClass == LETTER || charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
        } 
        nextToken=IDENT; 
        break; // identifiers
    case DIGIT: 
        addChar(); 
        getChar(); 
        while( charClass == DIGIT ){ 
          addChar(); 
          getChar(); 
        } 
        nextToken=INT_LIT; 
        break; // integers
    case UNKNOWN: 
        lookup(nextChar); 
        getChar(); 
        break; // Other characters
    case END_OF_INPUT: 
        nextToken = END_OF_INPUT;   
        lexeme = "END_OF_INPUT";
        break;
  }

  return nextToken;
}

