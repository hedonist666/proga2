#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <memory>
#include <functional>
#include <numeric>
#include <cmath>
#include <complex>
#include <algorithm>



template <typename T>
struct Node {
  using child = std::shared_ptr<Node<T>>;
  child left;
  child right;
  size_t num;
  T val;
  bool red;
};

template <typename T, typename Inserter>
struct RedBlack {
  using node_t = std::shared_ptr<Node<T>>;
  RedBlack(std::initializer_list<T> lst) : insert {deft_insert} {

  } //TODO

  template <typename Container>
  RedBlack(Inserter f, Container lst) : insert {f} {
    for (auto& e : lst) {
      insert(e); 
      ++size;
    }
  }

  bool verify() {
    assert(!head.red);
    return check(head);       
  }

  void deft_insert(const T e) {
    for (auto* cur_p = &head;;) {
      if (!*(cur_p)) {
        *cur_p = std::make_shared<Node<T>>(e, size);
        return;
      }
      else {
        if (e < (*cur_p)->val) {
          cur_p = &(*cur_p)->left;
        }
        else {
          cur_p = &(*cur_p)->right;
        }
      }
    }
  }

private:
  bool check(node_t cur) {
    if (!cur) return true;
    if (cur->red && cur->left  && cur->left->red  == true) return false;
    if (cur->red && cur->right && cur->right->red == true) return false;
    if (height(cur->left) != height(cur->right)) return false;
    check(cur->left) & check(cur->right);
  }
  size_t height(node_t cur) {
    if (!cur) return 0;
    if (cache[cur->num]) return cache[cur->num];
    if (cur->red) return (cache[cur->num] = std::max(height(cur->left), height(cur->right)));
    return (cache[cur->num] = 1 + std::max(height(cur->left), height(cur->right)));
  }

  size_t size;
  node_t head;
  Inserter insert;
  std::vector<size_t> cache;

};


inline void nop(auto x) { }




int main() {
  using namespace std;
  return 0;
}
