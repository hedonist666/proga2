#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <numeric>
#include <cmath>
#include <complex>
#include <algorithm>
#include <memory>


template <typename T>
struct Node {
  using child = std::shared_ptr<Node<T>>;
  Node(T e) : left {}, right {}, val {e} { }
  child left;
  child right;
  T val;
};


template <typename T>
struct AVL {
  using node_t = std::shared_ptr<Node<T>>;

  AVL(std::initializer_list<T> lst) : head {} {
    for (auto e : lst) {
      insert(e);
    }
  }

  void insert(const T e) {
    for (auto* cur_p = &head;;) {
      if (!*(cur_p)) {
        *cur_p = std::make_shared<Node<T>>(e);
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

  bool verify() {
    return check(head);
  }
  void show() const {
    print(head);
  }
private:
  bool check(node_t cur) {
    if (!cur) return true;
    if (abs(height(cur->left) - height(cur->right)) > 1) {
      return false;
    }
    return check(cur->left) & check(cur->right);
  } 
  size_t height(node_t cur) {
    if (!cur) return 0;
    return 1 + std::max(height(cur->left), height(cur->right));
  }
  void print(node_t cur) const {
    if (!cur) return;
    std::cout << "element: " << cur->val << "; children: ";
    if (cur->left) std::cout << cur->left->val;
    else std::cout << '_';
    std::cout << ", ";
    if (cur->right) std::cout << cur->right->val;
    else std::cout << '_';
    std::cout << std::endl;
    print(cur->left);
    print(cur->right);
  }

  node_t head;
};




/*
int main() {
  using namespace std;
  AVL<int> tr {2, 3, 1, 4, 0, 1, 6, 8};
  tr.show();
  cout << boolalpha << tr.verify();
  return 0;
}
*/
