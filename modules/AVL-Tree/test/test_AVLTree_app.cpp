// Copyright 2023 Larin Konstantin

#include <gtest/gtest.h>

#include "include/AVLTree.h"
#include "include/AVLTree_app.h"

TEST(AVLTree_app, test_avl_tree) {
  const char* args[] = {"app", "add",    "3",   "add", "2",   "add", "1",
                        "add", "6",      "add", "5",   "add", "4",   "remove",
                        "10",  "remove", "6",   "min", "max"};

  auto result = application { } (sizeof(args) / sizeof(args[0]), args);

  ASSERT_EQ(result, "min value: 1\nmax value: 5\n");
}

TEST(AVLTree_app, test_avl_tree_again) {
  const char* args[] = {"app", "add", "1",   "add", "1",   "add", "1",
                        "add", "1",   "add", "1",    "add", "1",   "remove",
                        "1",   "add", "5",   "min",  "max"};

  auto result = application { } (sizeof(args) / sizeof(args[0]), args);

  ASSERT_EQ(result, "min value: 5\nmax value: 5\n");
}

TEST(AVLTree_app, test_avl_tree_again_2) {
  const char* args[] = {"app", "add", "10",   "add", "20",   "add", "12",
                        "add", "15",   "add", "16",    "add", "18",   "remove",
                        "1",    "min",  "max"};

  auto result = application { } (sizeof(args) / sizeof(args[0]), args);

  ASSERT_EQ(result, "min value: 10\nmax value: 20\n");
}

TEST(AVLTree_app, test_avl_tree_bad_input) {
  const char* args[] = {"app", "wdcerfvxgthybjukniolp;[']"};

  EXPECT_ANY_THROW(application { } (sizeof(args) / sizeof(args[0]), args));
}
