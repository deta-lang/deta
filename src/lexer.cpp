#include "lexer.h"

#include <ctype.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace deta;

std::unordered_map<std::string, keyword_t> keywords = {
{"if", keyword_t::IF}, {"in", keyword_t::IN}, {"do", keyword_t::DO}, {"fn", keyword_t::FN},
{"for", keyword_t::FOR}, {"var", keyword_t::VAR}, {"new", keyword_t::NEW},
{"else", keyword_t::ELSE}, {"type", keyword_t::TYPE}, {"enum", keyword_t::ENUM},
{"match", keyword_t::MATCH}, {"const", keyword_t::CONST}, {"while", keyword_t::WHILE}, {"break", keyword_t::BREAK},
{"return", keyword_t::RETURN}, {"delete", keyword_t::DELETE}, {"import", keyword_t::IMPORT}, {"export", keyword_t::EXPORT}, {"public", keyword_t::PUBLIC}, {"static", keyword_t::STATIC},
{"private", keyword_t::PRIVATE},
{"continue", keyword_t::CONTINUE},
{"protected", keyword_t::PROTECTED},
};

std::unordered_map<std::string, op_t> operators = {
{"+", op_t::ADD}, {"+=", op_t::ADDEQ}, {"-", op_t::MINEQ}, {"*", op_t::MUL}, {"*=", op_t::MULEQ}, {"/", op_t::DIVEQ}, {"%", op_t::MOD}, {"%=", op_t::MODEQ}, {"**", op_t::POW}, {"**=", op_t::POWEQ},
{"=", op_t::ASSIGN}, {"==", op_t::EQ}, {"!=", op_t::NEQ}, {"<", op_t::LT}, {"<=", op_t::LTEQ}, {">", op_t::GT}, {">=", op_t::GTEQ}, {"&&", op_t::AND}, {"||", op_t::OR}, {"!", op_t::NOT},
{"&", op_t::BITAND}, {"|", op_t::BITOR}, {"^", op_t::BITXOR}, {"~", op_t::BITNOT}, {"->", op_t::FNRETTYPE}, {":", op_t::COLON}, {";", op_t::SEMI}, {",", op_t::COMMA},
{"[", op_t::LBRACKET}, {"]", op_t::RBRACKET}, {"{", op_t::LBRACE}, {"}", op_t::RBRACE}, {"(", op_t::LPAREN}, {")", op_t::RPAREN},
{"++", op_t::INCR}, {"--", op_t::DECR}, {"..", op_t::RANGE_INCL}, {"..=", op_t::RANGE_EXCL}, {".", op_t::DOT}, {"...", op_t::SPREAD}, {"?", op_t::QMARK},
};

std::vector<char> operators_chars = {'+', '-', '*', '/', '%', '!', '=', '<', '>', '.'};

bool lexer_t::next() {
  token.line = line;
  char c = *ch;
  if(isalpha(c) || c == '_') {
    std::string s;
    do {
      s += c;
      updateLine();
    } while(isalnum(c = read()) || c == '_');

    if(keywords.find(s) != keywords.end()) {
      token.type = type_t::KEYWORD;
      token.value = keywords[s];
    } else if(s == "true" || s == "false") {
      token.type = type_t::BOOL;
      token.value = s == "true";
    } else if(s == "null") {
      token.type = type_t::NULL_T;
      token.value = false;
    } else {
      token.type = type_t::IDENTIFIER;
      token.value = s;
    }
  } else if(isdigit(c)) {
    std::string s;
    do {
      s += c;
      updateLine();
    } while(isdigit(c = read()));
    if(c == '.') {
      s += c;
      updateLine();

      while(isdigit(c = read())) {
        s += c;
        updateLine();
      }
      token.type = type_t::FLOAT;
    } else {
      token.type = type_t::INT;
    }

    token.value = std::stod(s);
  } else if(c == '"') {
    std::string s;
    updateLine();

    while((c = read()) != '"') {
      updateLine();
      if(c == '\\') {
        updateLine();
        c = read();
        s += c; // temporary solution
      } else {
        s += c;
      }
    }

    read();
    token.type = type_t::STRING;
    token.value = s;
  } else if(c == '\'') {
    updateLine();
    if(read() == '\\') {
      updateLine();
      token.value = read(); // temporary solution
    } else {
      token.value = c;
    }

    read();
    token.type = type_t::CHAR;
  } else {
    std::string s(1, c);
    read();

    if(std::find(operators_chars.begin(), operators_chars.end(), c) != operators_chars.end()) {
      while(std::find(operators_chars.begin(), operators_chars.end(), read()) != operators_chars.end()) {
        s += *ch;
      }
    }

    if(operators.find(s) != operators.end()) {
      token.type = type_t::OPERATOR;
      token.value = operators[s];
    } else {
      throw std::runtime_error("Unknown token: " + s);
    }
  }
}

char lexer_t::peek() {
  if(ch == ichiBuffer + 1024)
    return niBuffer[0];
  else if(ch == niBuffer + 1024)
    return ichiBuffer[0];
  else
    return ch[1];
}

char lexer_t::read() {
  if(ch == ichiBuffer + 1024) {
    ch = niBuffer;
    readBuffer();
  } else if(ch == niBuffer + 1024) {
    ch = ichiBuffer;
    readBuffer();
  } else {
    ++ch;
  }
  
  return *ch;
}

void lexer_t::readBuffer() {
  std::streamsize bytesRead = 1;
  if(*niBuffer == '\0') {
    file.read(ichiBuffer, sizeof(ichiBuffer));
    ch = ichiBuffer;
    bytesRead = file.gcount();
  } else {
    ch = niBuffer;
  }

  if(bytesRead > 0) {
    file.read(niBuffer, sizeof(niBuffer));
    bytesRead = file.gcount();
  }

  if(bytesRead == 0) {
    ch = NULL;
    eof = true;

    if(file.fail()) {
      throw std::runtime_error("Failed to read file");
    }
  }
}

void lexer_t::getTokenType(std::stringstream &ss) const {
  switch(token.type) {
    case type_t::IDENTIFIER:
      ss << "[Identifier] ";
      break;
    case type_t::KEYWORD:
      ss << "[Keyword] ";
      break;
    case type_t::OPERATOR:
      ss << "[Operator] ";
      break;
    case type_t::STRING:
      ss << "[String] ";
      break;
    case type_t::INT:
      ss << "[Integer] ";
      break;
    case type_t::FLOAT:
      ss << "[Float] ";
      break;
    case type_t::FSTRING:
      ss << "[Format String] ";
      break;
    case type_t::NULL_T:
      ss << "[Null] ";
      break;
    case type_t::BOOL:
      ss << "[Boolean] ";
      break;
    case type_t::CHAR:
      ss << "[Character] ";
      break;
  }
}

void lexer_t::getTokenValue(std::stringstream &ss) const {
  switch(token.type) {
    case type_t::IDENTIFIER:
      ss << std::get<std::string>(token.value);
      break;
    case type_t::KEYWORD:
      ss << "KEYWORD";
      break;
    case type_t::OPERATOR:
      ss << "OPERATOR";
      break;
    case type_t::STRING:
      ss << '"' << std::get<std::string>(token.value) << '"';
      break;
    case type_t::INT:
      ss << (unsigned long) std::get<double>(token.value);
      break;
    case type_t::FLOAT:
      ss << std::get<double>(token.value);
      break;
    case type_t::FSTRING:
      ss << "FSTRING";
      break;
    case type_t::NULL_T:
      ss << "null";
      break;
    case type_t::BOOL:
      ss << (std::get<bool>(token.value) ? "true" : "false");
      break;
    case type_t::CHAR:
      ss << std::get<char>(token.value);
      break;
  }
}

void lexer_t::getTokenLine(std::stringstream &ss) const {
  ss << token.line;
}