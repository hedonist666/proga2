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

template <typename Container>
struct Node {
  std::vector<T> v;
  std::vector<Node<T>> children;
  template <typename Cont>
  Node(Cont lst) : v(lst.begin(), lst.end()) { }
};


template <typename T, typename Container>
struct Completion {
  
  std::vector<Container> res;
  std::vector<Node<T>> head;

  void cunstruct(std::vector<std::pair<Container, size_t>> v) {
    sort(v.begin(), v.end(), [](auto x, auto y) {
        return x.second > y.second;
        });
    for (auto& e : v) {
      insert(head, e.fisrt.begin());
    }
  }

  template <typename Iter>
  void insert(std::vector<Node<T>> cur, Iter input) {
    for (auto& e : cur) {
      auto _input = input;
      auto ch = cur.v.begin();
      for (;*_input == *ch, ch != cur.end(), *_input; ++ch, ++_input);
      if (ch == cur.v.end()) {
        
      }
    }
  }



  template <typename Iter>
  void run(Iter& input, Node<T>& cur, std::vector<T>& tmp) {
    if (*input) {
      auto ch     = cur.v.begin();
      auto _input = input;
      for (;ch != cur.v.end(), *ch == *_input; ++ch, ++_input);
      if (ch == cur.v.end()) {
        for (auto& e : cur.v) {
          tmp.push_back(e);
        }
        if (!*(cur.v.end() - 1)) {
          res.push_back(tmp);
          return;
        }
        else {
          for (auto& e : cur.children) {
            run(_input, e, tmp);
          }
        }
      }
    }
    else {
      for (auto& e : cur.v) {
        tmp.push_back(e);
      } 
      for (auto& e : cur.children) {
        run(input, e, tmp);
      }
    }
  }

};



int main() {
  using namespace std;

  return 0;
}
