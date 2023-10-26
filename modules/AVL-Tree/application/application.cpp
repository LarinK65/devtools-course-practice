// Copyright 2023 Larin Konstantin

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "include/AVLTree_app.h"

int main(int argc, const char** argv) {
  try {
    std::cout << application { } (argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }
  return 0;
}
