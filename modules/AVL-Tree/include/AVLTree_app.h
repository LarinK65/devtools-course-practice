// Copyright 2023 Larin Konstantin
#pragma once
#include <string>

#include "AVLTree.h"

class application {
 public:
  std::string operator()(int argc, const char** argv);

 private:
  void add(int64_t value);
  void remove(int64_t value);
  int64_t min();
  int64_t max();

  AVLTree<int64_t> set;
};
