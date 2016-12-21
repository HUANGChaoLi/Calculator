#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "WordParser.h"
#include "Token.h"

WordParser::WordParser() {
  peek = ' ';
  isFinal = false;
}

void WordParser::resetParser() {
  peek = ' ';
  isFinal = false;
}

Token WordParser::newToken(TOKEN_TYPE type) {
  peek = getchar();
  return Token(type);
}

Token WordParser::getNextToken() {

  if (isFinal) return Token(END);

  // 去除空格和制表符
  while (peek == ' '|| peek == '\t') peek = getchar();

  // 换行符说明词法分析结束，需要reset才能重新分析
  if (peek == '\n') {
    isFinal = true;
    return Token(END);
  }

  switch (peek) {
    case '(' :
      return newToken(LP);
    case ')' :
      return newToken(RP);
    case '+' :
      return newToken(ADD);
    case '-' :
      return newToken(SUB);
    case '*' :
      return newToken(MUL);
    case '/' :
      return newToken(DIV);
    
    // 退出程序的Token
    case 'q' :
    case 'Q' :
      return newToken(QUIT);

    // 提取数字
    default :
      double num = 0;
      while (isdigit(peek)) {
        num = num * 10 + (peek - '0');
        peek = getchar();
      }
      if (peek == '.') {
        peek = getchar();
        double factor = 10;
        while (isdigit(peek)) {
          num += (peek - '0') * 1.0 / factor;
          factor *= 10;
          peek = getchar();
        }
      }
      return Token(NUM, num);
  }
}
