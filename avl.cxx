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
  Node(T e, size_t num = 0) : left {}, right {}, val {e}, num {num} { }
  child left;
  child right;
  T val;
  size_t num; //ne kruto
};


template <typename T>
struct AVL {
  using node_t = std::shared_ptr<Node<T>>;

  AVL(std::initializer_list<T> lst) : head {}, size {} {
    for (auto e : lst) {
      insert(e);
      ++size;
    }
  }

  void insert(const T e) {
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

  bool verify() {
    cache.clear();
    cache.resize(size, 0);
    return check(head);
  }
  void show() const {
    std::cout << "AVL-tree, size: " << size << std::endl;
    print(head);
  }
  void pretty_show() const {
        
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
    if (abs(height(cur->left) - height(cur->right)) > 1) {
      return false;
    }
    return check(cur->left) & check(cur->right);
  } 
  size_t height(node_t cur) {
    if (!cur) return 0;
    if (cache[cur->num]) return cache[cur->num];
    return (cache[cur->num] = 1 + std::max(height(cur->left), height(cur->right)));
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
  size_t size;
  std::vector<size_t> cache;
};





int main() {
  using namespace std;
  AVL<int> tr {2, 3, 1, 4, 0, 1, 6, 8};
  tr.show();
  cout << boolalpha << tr.verify();
  return 0;
}

