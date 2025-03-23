#include "lexer.h"

using namespace deta;

bool lexer_t::next() {
  switch(ch) {
    
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

void lexer_t::read() {
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

