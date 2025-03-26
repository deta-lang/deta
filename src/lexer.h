#pragma once

#include <cstdint>
#include <cstring>
#include <cstdio> // C FS is better than C++ FS
#include <ctype.h>
#include <string>
#include <variant>
#include <sstream>
#include <iostream>

namespace deta {
  enum class type_t : uint8_t {
    NULL_T, BOOL, INT, FLOAT, CHAR, STRING, FSTRING, IDENTIFIER, KEYWORD, OPERATOR
  };
  
  enum class keyword_t : uint8_t {
    IF, IN, DO, FN,
    FOR, VAR, NEW,
    ELSE, TYPE, ENUM,
    MATCH, CONST, WHILE, BREAK,
    RETURN, DELETE, IMPORT, EXPORT, PUBLIC, STATIC,
    PRIVATE,
    CONTINUE,
    PROTECTED,
  };

  enum class op_t : uint8_t {
    ADD, ADDEQ, MINEQ, MUL, MULEQ, DIVEQ, MOD, MODEQ, POW, POWEQ,
    ASSIGN, EQ, NEQ, LT, LTEQ, GT, GTEQ, AND, OR, NOT,
    BITAND, BITOR, BITXOR, BITNOT, FNRETTYPE, COLON, SEMI, COMMA,
    LBRACKET, RBRACKET, LBRACE, RBRACE, LPAREN, RPAREN,
    INCR, DECR, RANGE_INCL, RANGE_EXCL, DOT, SPREAD, QMARK
  };
  
  struct token_t {
    type_t type;
    std::variant<std::string, double, keyword_t, op_t, char, bool> value;
    uint32_t line;

    token_t(): type(type_t::NULL_T), value((double) 0.0), line(1) {}

    std::ostream &str(std::ostream &os) const; // to_str(), for debugging aids
  };

  struct lexer_t {
    FILE *file;
    const char *filename;

    uint32_t line;
    token_t token;
    char ichiBuffer[1024], niBuffer[1024];
    char *ch;
    bool eof;

    lexer_t(FILE *file, const char *filename):
      file(file), filename(filename), line(1), ch(nullptr)
    {
      std::memset(ichiBuffer, 0, sizeof(ichiBuffer));
      std::memset(niBuffer, 0, sizeof(niBuffer));

      int bytesRead = fread(ichiBuffer, sizeof(char), sizeof(ichiBuffer), file);
      if(bytesRead == sizeof(ichiBuffer)) {
        bytesRead += fread(niBuffer, sizeof(char), sizeof(niBuffer), file);
      }
      if((unsigned long) bytesRead < 2 * sizeof(ichiBuffer)) {
        eof = true;
      }
      ch = ichiBuffer;
    }

    // User facing APIs
    bool next();

    // Lexer APIs
  private:
    void readBuffer();
    char peek();
    char read();
    inline void updateLine() {
      if (ch && *ch == '\n') {
        line++;
      }
    }

    void skipws() {
      while (ch && isspace(*ch)) {
        read();
      }
    }
  };
}