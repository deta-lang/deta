#include <iostream>

#include "lexer.h"

using namespace deta;

int main(void) {
  FILE *file = fopen("future_src/main.dt", "r");
  if(file == NULL) {
    std::cerr << "Failed to open file future_src/main.dt\n";
  }
  
  lexer_t lexer(file, "future_src/main.dt");

  while(lexer.next()) {
    lexer.token.str(std::cout) << '\n';
  }

  fclose(file);
  return 0;
}