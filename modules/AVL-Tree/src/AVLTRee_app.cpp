// Copyright 2023 Larin Konstantin
#include <cassert>
#include <cinttypes>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

#include "include/AVLTree.h"
#include "include/AVLTree_app.h"

enum class operations { add = 0, remove, min, max, err };

operations parse_op(const std::string& op) {
  if (op == "add") {
    return operations::add;
  } else if (op == "remove") {
    return operations::remove;
  } else if (op == "min") {
    return operations::min;
  } else if (op == "max") {
    return operations::max;
  } else {
    return operations::err;
  }
}

std::string application::operator()(int argc, const char** argv) {
  std::string result;

  for (size_t i = 1; i < size_t(argc); i++) {
    switch (parse_op(argv[i])) {
      case operations::add: {
        i++;
        int64_t value = atoll(argv[i]);
        add(value);
        break;
      }
      case operations::remove: {
        int64_t value = atoll(argv[i + 1]);
        i++;
        remove(value);
        break;
      }
      case operations::min: {
        result += "min value: " + std::to_string(min()) + "\n";
        break;
      }
      case operations::max: {
        result += "max value: " + std::to_string(max()) + "\n";
        break;
      }
      default: {
        throw std::logic_error("bad input");
        break;
      }
    }
  }

  return result;
}

void application::add(int64_t value) { set.insert(value); }

void application::remove(int64_t value) { set.remove(value); }

int64_t application::min() { return set.find_min(); }

int64_t application::max() { return set.find_max(); }
