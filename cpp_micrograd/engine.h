#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

namespace CMG {
template<typename T>
struct ValueHash;

template<typename T>
struct ValueEqual;

template <typename T>
struct Value {

  Value<T>(T _d, std::vector<Value<T>>* _children = nullptr,
           std::string op = "")
      : data(_d), _op(op), grad(0) {
    if (_children != nullptr) {
      for (const auto& c : *_children) {
        this->_prev.insert(c);
      }
    }
  }

  ~Value() {
    if (children != nullptr) {
      delete children;
    }
  }

 public:
  template <typename T>
  Value<T> operator+(const Value<T>& other) {
    Value<T> out(data + other.data, new std::vector<Value<T>>{this, other},
                 "+");
    _backward = [&]() {
      this->grad += out.grad;
      other.grad += out.grad;
    };
    out._backgrad = _backward;
    return out;
  }

  template <typename T>
  bool operator>(const Value<T>& other) {
    return this->data > other.data;
  }

  template <typename T>
  bool operator<(const Value<T>& other) {
    return this->data < other.data;
  }

 public:
  T data;
  double grad;
  std::function<void()> _backward;
  std::unordered_set<Value<T>,ValueHash<T>, ValueEqual<T>> _prev;
  std::string _op;
  std::vector<Value<T>>* children = nullptr;
};

// Hash function for Value<T>
template <typename T>
struct ValueHash {
  std::size_t operator()(const Value<T>& v) const {
    return std::hash<T>()(v.data);
  }
};

// Equality function for Value<T>
template <typename T>
struct ValueEqual {
  bool operator()(const Value<T>& v1, const Value<T>& v2) const {
    return v1.data == v2.data;
  }
};

}  // namespace CMG

#endif  // !__ENGINE_H__
