// Copyright 2023 Ermolaev Danila

#include <gtest/gtest.h>

#include "include/bitarray.h"

TEST(bit_array, default_constructed_array_is_empty) {
  bit_array<std::allocator<uint64_t>> arr{};

  ASSERT_EQ(arr.size(), size_t(0));
  ASSERT_EQ(arr.capacity(), size_t(0));
}

TEST(bit_array, constructor_with_count_check_size) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  ASSERT_EQ(arr.size(), n);
}

TEST(bit_array, constructor_with_count_check_capacity) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  ASSERT_TRUE(arr.capacity() >= n);
}

TEST(bit_array, constructor_with_count_check_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  for (size_t i = size_t(0); i < n; i++) {
    ASSERT_FALSE(arr[i]);
  }
}

TEST(bit_array, constructor_with_count_check_size_and_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  ASSERT_EQ(arr.size(), n);
}

TEST(bit_array, constructor_with_count_check_capacity_and_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  ASSERT_TRUE(arr.capacity() >= n);
}

TEST(bit_array, constructor_with_count_check_value_and_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  for (size_t i = size_t(0); i < n; i++) {
    ASSERT_TRUE(arr[i]);
  }
}

TEST(bit_array, write_by_brackets) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  for (size_t i = size_t(0); i < n; i++) {
    arr[i] = true;
    ASSERT_TRUE(arr[i]);
  }
}

TEST(bit_array, assign_less_size) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  size_t new_size = 50;
  arr.assign(new_size, false);

  ASSERT_EQ(arr.size(), new_size);
}

TEST(bit_array, assign_greater_size) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  size_t new_size = 250;
  arr.assign(new_size, false);

  ASSERT_EQ(arr.size(), new_size);
}

TEST(bit_array, assign_less_size_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  size_t new_size = 50;
  arr.assign(new_size, false);

  for (size_t i = size_t(0); i < arr.size(); i++) {
    ASSERT_FALSE(arr[i]);
  }
}

TEST(bit_array, assign_greater_size_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n, true);

  size_t new_size = 250;
  arr.assign(new_size, false);

  for (size_t i = size_t(0); i < arr.size(); i++) {
    ASSERT_FALSE(arr[i]);
  }
}

TEST(bit_array, clear_empty_array) {
  bit_array<std::allocator<uint64_t>> arr;

  arr.clear();

  ASSERT_EQ(arr.size(), size_t(0));
}

TEST(bit_array, empty_after_clear) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  arr.clear();

  ASSERT_EQ(arr.size(), size_t(0));
}

TEST(bit_array, reserve_change_capacity) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  size_t new_capacity = 1000;
  arr.reserve(new_capacity);

  ASSERT_GE(arr.capacity(), new_capacity);
}

TEST(bit_array, resize_change_size) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  size_t new_capacity = 1000;
  arr.resize(new_capacity);

  ASSERT_EQ(arr.size(), new_capacity);
}

TEST(bit_array, push_back) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr;

  for (size_t i = size_t(0); i < n; i++) {
    arr.push_back(true);

    ASSERT_EQ(arr.size(), size_t(i + 1));
    ASSERT_TRUE(arr[arr.size() - size_t(1)]);
  }
}

TEST(bit_array, pop_back) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  for (size_t i = n; i > size_t(0); i--) {
    arr.pop_back();

    ASSERT_EQ(arr.size(), size_t(i - 1));
  }
}

TEST(bit_array, push_after_clear_size) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  arr.clear();

  arr.push_back(true);

  ASSERT_EQ(arr.size(), size_t(1));
}

TEST(bit_array, push_after_clear_value) {
  size_t n = 100;
  bit_array<std::allocator<uint64_t>> arr(n);

  arr.clear();

  arr.push_back(true);

  ASSERT_TRUE(arr[size_t(0)]);
}
