#ifndef __WORDPARSER__
#define __WORDPARSER__

#include "Token.h"

class WordParser {
  private :
    bool isFinal;
    char peek;
    Token newToken(TOKEN_TYPE type);

  public :
    WordParser();
    void resetParser();
    Token getNextToken();
};

#endif
