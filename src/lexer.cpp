#include "lexer.h"

#include <ctype.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace deta;

const std::unordered_map<std::string, keyword_t> keywords = {
{"if", keyword_t::IF}, {"in", keyword_t::IN}, {"do", keyword_t::DO}, {"fn", keyword_t::FN},
{"for", keyword_t::FOR}, {"var", keyword_t::VAR}, {"new", keyword_t::NEW},
{"else", keyword_t::ELSE}, {"type", keyword_t::TYPE}, {"enum", keyword_t::ENUM},
{"match", keyword_t::MATCH}, {"const", keyword_t::CONST}, {"while", keyword_t::WHILE}, {"break", keyword_t::BREAK},
{"return", keyword_t::RETURN}, {"delete", keyword_t::DELETE}, {"import", keyword_t::IMPORT}, {"export", keyword_t::EXPORT}, {"public", keyword_t::PUBLIC}, {"static", keyword_t::STATIC},
{"private", keyword_t::PRIVATE},
{"continue", keyword_t::CONTINUE},
{"protected", keyword_t::PROTECTED},
};

const std::unordered_map<std::string, op_t> operators = {
{"+", op_t::ADD}, {"+=", op_t::ADDEQ}, {"-", op_t::MINEQ}, {"*", op_t::MUL}, {"*=", op_t::MULEQ}, {"/", op_t::DIVEQ}, {"%", op_t::MOD}, {"%=", op_t::MODEQ}, {"**", op_t::POW}, {"**=", op_t::POWEQ},
{"=", op_t::ASSIGN}, {"==", op_t::EQ}, {"!=", op_t::NEQ}, {"<", op_t::LT}, {"<=", op_t::LTEQ}, {">", op_t::GT}, {">=", op_t::GTEQ}, {"&&", op_t::AND}, {"||", op_t::OR}, {"!", op_t::NOT},
{"&", op_t::BITAND}, {"|", op_t::BITOR}, {"^", op_t::BITXOR}, {"~", op_t::BITNOT}, {"->", op_t::FNRETTYPE}, {":", op_t::COLON}, {";", op_t::SEMI}, {",", op_t::COMMA},
{"[", op_t::LBRACKET}, {"]", op_t::RBRACKET}, {"{", op_t::LBRACE}, {"}", op_t::RBRACE}, {"(", op_t::LPAREN}, {")", op_t::RPAREN},
{"++", op_t::INCR}, {"--", op_t::DECR}, {"..", op_t::RANGE_INCL}, {"..=", op_t::RANGE_EXCL}, {".", op_t::DOT}, {"...", op_t::SPREAD}, {"?", op_t::QMARK},
};

const std::vector<const char *> operators_chars = {
  "+", "+=", "-", "-=", "*", "*=", "/", "/=", "%", "%=", "**", "**=",
  "=", "==", "!=", "<", "<=", ">", ">=", "&&", "||", "!",
  "&", "|", "^", "~", "->", ":", ";", ",", "[", "]", "{", "}", "(", ")",
  "++", "--", "..", "..=", ".", "...", "?",
};

bool lexer_t::next() {
  skipws();
  token.line = line;
  char c = *ch;
  if(isalpha(c) || c == '_') {
    std::string s;
    do {
      s += c;
      updateLine();
    } while(isalnum(c = read()) || c == '_');

    auto kwd = keywords.find(s);
    if(kwd != keywords.end()) {
      token.type = type_t::KEYWORD;
      token.value = kwd->second;
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
    std::string s;
    std::string s2;
    int len = 1;
    s = c;
    s2 = c;
    s2 += read();
    
    while(std::find(operators_chars.begin(), operators_chars.end(), s2) != operators_chars.end()) {
      s += s2[len];
      s2 += read();
      len++;
    }

    auto op = operators.find(s);
    if(op != operators.end()) {
      token.type = type_t::OPERATOR;
      token.value = op->second;
    } else if(eof) {
      return false;
    } else {
      throw std::runtime_error("Unknown token: '" + s + "'");
    }
  }

  return true;
}

char lexer_t::peek() {
  return '\0';
}

char lexer_t::read() {
  if(*ch == '\0' && eof) return '\0';
  if(ch == ichiBuffer + 1023) {
    ch = niBuffer;
    readBuffer();
  } else if(ch == niBuffer + 1023) {
    ch = ichiBuffer;
    readBuffer();
  } else {
    ++ch;
  }

  return (ch) ? *ch : '\0';
}

void lexer_t::readBuffer() {
  char *buf = nullptr;
  if(eof) {
    return;
  } else if(ch == ichiBuffer) {
    buf = niBuffer;
  } else if(ch == niBuffer) {
    buf = ichiBuffer;
  } else {
    throw std::runtime_error("Tries of reading buffer before all data are read");
  }

  const int bytesRead = fread(buf, 1, 1024, file);
  if(bytesRead != 1024) {
    eof = true;
  }
}

std::ostream &token_t::str(std::ostream &os) const {
  switch(type) {
    case type_t::INT:
      os << "(int       ) " << std::get<double>(value);
      return os;
    case type_t::FLOAT:
      os << "(float     ) " << std::get<double>(value);
      return os;
    case type_t::STRING:
      os << "(string    ) " << std::get<std::string>(value);
      return os;
    case type_t::CHAR:
      os << "(char      ) " << std::get<char>(value);
      return os;
    case type_t::BOOL:
      os << "(bool      ) " << std::get<bool>(value);
      return os;
    case type_t::NULL_T:
      os << "(null      ) null";
      return os;
    case type_t::IDENTIFIER:
      os << "(identifier) " << std::get<std::string>(value);
      return os;
    case type_t::KEYWORD: {
      keyword_t wanted = std::get<keyword_t>(value);
      for(const auto &[key, value] : keywords) {
        if(value == wanted) {
          os << "(keyword   ) " << key;
          return os;
        }
      }
      throw std::runtime_error("Unknown keyword");
    }
    case type_t::OPERATOR: {
      op_t wanted = std::get<op_t>(value);
      for(const auto &[key, value] : operators) {
        if(value == wanted) {
          os << "(operator  ) " << key;
          return os;
        }
      }
      throw std::runtime_error("Unknown operator");
    }
    case type_t::FSTRING:
      throw std::runtime_error("F-string not supported");
  }
}