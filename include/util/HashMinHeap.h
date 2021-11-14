#ifndef GUARD_F2BA6310_FE94_4349_985B_1B0CE68E8517
#define GUARD_F2BA6310_FE94_4349_985B_1B0CE68E8517

#include <algorithm>
#include <cstdint>
#include <exception>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

namespace util {
/**
 * \brief MinHeap implementation with the key-based access. Internal hash stores
 * key mappings to the indexes in the heap.
 *
 * \tparam Key type of the key
 * \tparam T type of values to store in the heap
 */
template <typename Key, typename T> class HashMinHeap {
public:
  using Index = size_t;

  /**
   * \brief Construct a new Hash Min Heap object
   *
   * @param capacity maximum heap size
   */
  HashMinHeap(size_t capacity) : _capacity(capacity) {
    _arr.resize(capacity);
    _size = 0;
  }

  /**
   * \brief Add new element to the heap. Use value for comparison. Re-calculates
   * internal index hash with new indexes. Complexity log(size).
   *
   * @throws exception if the heap is full
   *
   * @param key index to insert
   * @param value stored in the heap
   */
  void insert(Key key, T value) {
    if (isFull()) {
      throw "Size overflow";
    }

    _arr[_size] = {key, value};
    _keyMap[key] = _size;

    size_t i = _size;
    _size++;

    while (i != 0 && _arr[parent(i)].second > _arr[i].second) {
      _keyMap[_arr[parent(i)].first] = i;
      _keyMap[key] = parent(i);
      std::swap(_arr[parent(i)], _arr[i]);
      i = parent(i);
    }
  }

  /**
   * \brief Get the current heap size
   *
   * @return size_t size
   */
  size_t getSize() const { return _size; }

  /**
   * \brief Check is the heap is full
   *
   * @return true if heap is full
   * @return false otherwise
   */
  bool isFull() const { return _size == _capacity; }

  /**
   * \brief Get the value by the key. Works like the hash.
   *
   * @param i key value
   * @return T value associated with the key
   */
  T get(Key i) { return _arr[_keyMap[i]].second; }

  /**
   * \brief Check whether heap contains the specified key.
   *
   * @param key key value
   * @return true if the heap already contains the key
   * @return false otherwise
   */
  bool hasKey(Key key) const { return _keyMap.find(key) != _keyMap.end(); }

  /**
   * \brief Change the value in the heap by the key. Will trigger heapify.
   * Complexity log(size).
   *
   * @param key key value
   * @param newValue new value of the element
   */
  void change(Key key, T newValue) {
    Index i = _keyMap[key];
    _arr[i].second = newValue;
    while (i != 0 && _arr[parent(i)].second > _arr[i].second) {
      _keyMap[_arr[parent(i)].first] = i;
      _keyMap[key] = parent(i);
      std::swap(_arr[parent(i)], _arr[i]);
      i = parent(i);
    }
    heapify(i);
  }

  /**
   * \brief Extract minimum (top) element from the heap. Trigger heapify.
   * Complexity log(size).
   *
   * @return T extracted value
   */
  T extractMin() {
    if (_size == 0)
      throw "empty size";

    _keyMap.erase(_arr[0].first);

    if (_size == 1) {
      _size = 0;
      return _arr[0].second;
    }

    T root = _arr[0].second;
    _arr[0] = _arr[_size - 1];
    _keyMap[_arr[0].first] = 0;
    _size--;
    heapify(0);

    return root;
  }

private:
  Index parent(Index i) { return (i - 1) / 2; }
  Index left(Index i) { return i * 2 + 1; }
  Index right(Index i) { return i * 2 + 2; }

  void heapify(Index i) {
    int r = right(i);
    int l = left(i);
    int min = i;

    if (r < _size && _arr[r].second < _arr[min].second) {
      min = r;
    }
    if (l < _size && _arr[l].second < _arr[min].second) {
      min = l;
    }

    if (min != i) {
      _keyMap[_arr[min].first] = i;
      _keyMap[_arr[i].first] = min;
      std::swap(_arr[i], _arr[min]);
      heapify(min);
    }
  }

  std::vector<std::pair<Key, T>> _arr;
  std::unordered_map<Key, Index> _keyMap;
  size_t _capacity;
  size_t _size;
};

} // namespace util

#endif /* GUARD_F2BA6310_FE94_4349_985B_1B0CE68E8517 */
