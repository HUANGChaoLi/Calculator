#include <iostream>

#include "WordParser.h"
#include "Token.h"

using namespace std;

// 初始化词法分析器，和Token头
WordParser wordParser;
Token head(END);

double expression();

double factor() {
  TOKEN_TYPE type = head.getType();
  double syn = head.getVal();
  head = wordParser.getNextToken();

  switch (type) {
    case NUM :
      return syn;
    case LP :
      return expression();
    case SUB:
      return -1 * factor();
    default :
      cout << "Error in factor ." << endl;
      return 0;
  }

}

double term_(double inh) {
  TOKEN_TYPE type = head.getType();
  double syn;

  switch (type) {
    case MUL :
    case DIV :
      head = wordParser.getNextToken();
      syn = (type == MUL ? inh * factor() : inh / factor());
      return term_(syn);

    case ADD :
    case SUB :
    case RP :
    case END :
      return inh;

    default :
      cout << "Error in term' ." << endl;
      return 0;
  }
}

double term() {
  TOKEN_TYPE type = head.getType();
  double syn;

  switch (type) {
    case NUM :
    case LP :
    case SUB :
      syn = factor();
      return term_(syn);

    default :
      cout << "Error in term ." << endl;
      return 0;
  }
}

double expression_(double inh) {
  TOKEN_TYPE type = head.getType();
  head = wordParser.getNextToken();
  double syn;

  switch (type) {
    case ADD :
    case SUB :
      syn = (type == ADD ? inh + term() : inh - term());
      return expression_(syn);

    case RP :
    case END :
      return inh;

    default :
      cout << "Error in expression' ." << endl;
      return 0;
  }
}

double expression() {
  TOKEN_TYPE type = head.getType();
  double syn;

  switch (type) {
    case LP :
    case NUM :
    case SUB :
      syn = term();
      return expression_(syn);

    default :
      cout << "Error in expression ." << endl;
      return 0;
  }
}


int main(int argc, char const *argv[]) {

  cout << "Welcome，请输入算数表达式，输入Q或q退出程序!" << endl;

  head = wordParser.getNextToken();

  while (head.getType() != QUIT) {
    cout << "= " << expression() << endl;
    wordParser.resetParser();
    head = wordParser.getNextToken();
  }
  
  return 0;
}
