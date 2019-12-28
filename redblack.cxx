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
  Node(T val, size_t num, bool red) : val {val}, num {num}, red {red} { }
};

template <typename T, typename Inserter>
struct RedBlack {
  using node_t = std::shared_ptr<Node<T>>;
  RedBlack(std::initializer_list<T> lst) : insert {deft_insert} {
    for (auto& e : lst ) {
      insert(e);
    }   
  };

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
    static bool flag = false;
    for (auto* cur_p = &head;;) {
      if (!*(cur_p)) {
        *cur_p = std::make_shared<Node<T>>(e, size, flag);
        flag = !flag;
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
    if (cur->left) {
      if (cur->left->val >= cur->val) return false;
    }
    if (cur->right) {
      if (cur->right->val >= cur->val) return false;
    }
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

  void print(node_t cur) const {
    if (!cur) return;
    std::cout << "element: " << cur->val 
              << " with color: " << (cur->red ? "red" : "black")
              << "; children: ";
    if (cur->left) std::cout << cur->left->val;
    else std::cout << '_';
    std::cout << ", ";
    if (cur->right) std::cout << cur->right->val;
    else std::cout << '_';
    std::cout << std::endl;
    print(cur->left);
    print(cur->right);
  }

  size_t size;
  node_t head;
  Inserter insert;
  std::vector<size_t> cache;

};


template <typename... T>
inline void nop(T... x) {return;}




int main() {
  using namespace std;
  nop(1,2,3);
  return 0;
}
