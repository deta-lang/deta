#include <iostream>

#include "lexer.h"

using namespace deta;

int main(void) {
  std::ifstream file("main.dt");
  if(!file) {
    std::cerr << "Failed to open file: main.dt" << std::endl;
    return 1;
  }

  const std::ifstream &file_ref = file;
  
  lexer_t lexer(file_ref, "main.dt");

  while(lexer.next()) {
    std::cout << lexer.getTokenType() << '\n';
  }

  file.close();
  return 0;
}