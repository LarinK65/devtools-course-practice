// Copyright 2023 Larin Konstantin
#ifndef MODULES_BIT_ARRAY_INCLUDE_BITARRAY_H_
#define MODULES_BIT_ARRAY_INCLUDE_BITARRAY_H_

#include <algorithm>
#include <cinttypes>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

template <typename alloc_t>
class bit_array;

namespace _bit_array_details {

template <typename array_t>
class bit_ref_proxy {
 public:
  bit_ref_proxy &operator=(bool value) {
    _array_ref.set_bit_value(value, _index);
    return *this;
  }

  bit_ref_proxy &operator=(const bit_ref_proxy &other) {
    return *this = static_cast<bool>(other);
  }

  operator bool() { return _array_ref.get_bit_value(_index); }

 protected:
  friend class bit_array<typename array_t::allocator_type>;

  bit_ref_proxy(array_t &arr, size_t index) : _index(index), _array_ref(arr) {}

  size_t _index;
  array_t &_array_ref;
};
}  // namespace _bit_array_details

template <typename alloc_t = std::allocator<uint64_t>>
class bit_array {
  using element_type = uint64_t;

 public:
  using value_type = bool;
  using allocator_type = alloc_t;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = _bit_array_details::bit_ref_proxy<bit_array>;
  using const_reference = bool;

  bit_array(const bit_array &other) = default;
  bit_array(bit_array &&other) = default;
  bit_array &operator=(const bit_array &other) = default;
  bit_array &operator=(bit_array &&other) = default;

  explicit bit_array(size_type count = 0, bool value = false,
                     const allocator_type &alloc = allocator_type{})
      : _size(count), _container(elements_count(count), element_value(value)) {}

  void assign(size_type count, bool value) {
    _size = count;
    _container.assign(elements_count(count), element_value(value));
  }

  const_reference operator[](size_type index) const noexcept {
    return get_bit_value(index);
  }

  reference operator[](size_type index) noexcept {
    return reference(*this, index);
  }

  void clear() noexcept {
    _size = 0;
    _container.clear();
  }

  size_type size() const noexcept { return _size; }

  size_type capacity() const noexcept {
    return _container.capacity() * bits_per_element;
  }

  void reserve(size_type ncapacity) {
    _container.reserve(elements_count(ncapacity));
  }

  void resize(size_type nsize, bool value = false) {
    _container.resize(elements_count(nsize), element_value(value));

    for (size_t i = _size; i % bits_per_element != 0 && i < nsize; i++) {
      set_bit_value(value, i);
    }

    _size = nsize;
  }

  void push_back(bool value) {
    if (_size % bits_per_element == 0) {
      _container.push_back(0);
    }

    set_bit_value(value, _size);
    _size++;
  }

  void pop_back() {
    _size--;
    if (_size % bits_per_element == 0) {
      _container.pop_back();
    }
  }

 protected:
  friend class _bit_array_details::bit_ref_proxy<bit_array>;
  static constexpr size_t bits_per_byte = 8;
  static constexpr size_t bits_per_element =
      sizeof(element_type) * bits_per_byte;

  static size_t element_index(size_t index) { return index / bits_per_element; }

  static size_t bit_index(size_t index) { return index % bits_per_element; }

  static size_t elements_count(size_t bits_count) {
    return (bits_count + bits_per_element - 1) / bits_per_element;
  }

  static element_type element_value(bool value) {
    return element_type(-1) + 1 - value;
  }

  void set_bit_value(bool value, size_t index) {
    size_t i = element_index(index);
    size_t bit = bit_index(index);

    _container[i] &= ~(element_type(1) << bit);
    _container[i] |= element_type(value) << bit;
  }

  bool get_bit_value(size_t index) {
    size_t i = element_index(index);
    size_t bit = bit_index(index);

    return _container[i] & (element_type(1) << bit);
  }

  size_t _size = 0;
  std::vector<uint64_t, alloc_t> _container;
};

#endif  // MODULES_BIT_ARRAY_INCLUDE_BITARRAY_H_
