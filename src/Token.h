#ifndef __TOKEN__
#define __TOKEN__

enum TOKEN_TYPE { NUM, ADD, SUB, MUL, DIV, LP, RP, END, QUIT };

class Token {
  private :
    TOKEN_TYPE _type;
    double _val;
  public :
    Token(TOKEN_TYPE type, double val = 0) {
      _type = type;
      _val = val;
    }

    TOKEN_TYPE getType() {
      return _type;
    }

    double getVal() {
      return _val;
    }
};

#endif
