#include <iostream>
#include <fstream>
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
  Container v;
  std::vector<Node<Container>> children;
  template <typename InitContainer>
  Node(InitContainer lst) : v(lst.begin(), lst.end()) { }
  template <typename Iter>
  Node(Iter i1, Iter i2) : v(i1, i2) {}
};


template <typename T, typename Cr>
struct Completion {
  
  std::vector<Cr> res;
  std::vector<Node<Cr>> head;
  T terminator;

  Completion(std::istream& is, T terminator) : terminator {terminator}, res {}, head {} {
    Cr str;
    size_t pop;    
    std::vector<std::pair<Cr, size_t>> tmp {};
    while (is >> str >> pop) {
      tmp.push_back(std::make_pair(str, pop)); 
    }
    construct(tmp);
  }

  void construct(std::vector<std::pair<Cr, size_t>> v) {
    sort(v.begin(), v.end(), [](auto x, auto y) {
        return x.second < y.second;
        });
    for (auto& e : v) {
      insert(head, e.first.begin());
    }
  }

  template <typename Iter>
  bool insert(std::vector<Node<Cr>>& cur, Iter input) {
    for (auto& e : cur) {
      if (*e.v.begin() != *input) {
        continue;
      }
      auto e_it = e.v.begin();
      for (;*input == *e_it && e_it != e.v.end() && *input != terminator; ++e_it, ++input);
      if (*input == terminator && e_it == e.v.end()) {
        return true;
      }
      if (e_it == e.v.end()) {
        if (insert(e.children, input)) return true;
        return false;
      }
      else {
        auto _input = input;
        while (*_input != terminator) ++_input;
        Cr tmp(input, _input + 1);
        Cr tmp1(e_it, e.v.end());
        e.v.resize(e_it - e.v.begin());
        e.children.push_back(tmp);
        e.children.push_back(tmp1);
        return true;
      }
    }
    auto _input = input;
    while (*_input != terminator) ++_input;
    cur.push_back(Node<Cr>{input, _input + 1});
    return true;
  }

  void show_tree() {
    _show_tree(head);
  }
  void _show_tree(std::vector<Node<Cr>> node) {
      for (auto& e : node) {
      std::cout << e.v << ' ';
      _show_tree(e.children);
      std::cout << std::endl;
    }
  }

  template <typename Iter>
  void show(Iter input) {
    Cr tmp {};
    for (auto& e : head) {
      run(input, e, tmp);
    }
    for (auto& e : res) {
      std::cout << e << std::endl;
    }
  }


  template <typename Iter>
  void run(Iter input, Node<Cr>& cur, Cr tmp) {
    if (*input != terminator) {
      auto cur_it = cur.v.begin();
      for (;cur_it != cur.v.end() && *cur_it == *input && *input != terminator; ++cur_it, ++input);
      if (cur_it == cur.v.end()) {
        for (auto& e : cur.v) {
          tmp.push_back(e);
        }
        if (cur.children.empty()) {
          res.push_back(tmp);
        }
        else {
          for (auto& e : cur.children) {
            run(input, e, tmp);
          }
        }
      }
    }
    else {
      for (auto& e : cur.v) {
        tmp.push_back(e);
      } 
      if (cur.children.empty()) {
        res.push_back(tmp);
        return;
      }
      for (auto& e : cur.children) {
        run(input, e, tmp);
      }
    }
  }

};



int main() {
  using namespace std;
  ifstream ifs("input");  
  char term = '1';
  Completion<char, string> comp (ifs, '1');
  string input {"w"};
  input.push_back(term);
  comp.show(input.begin());
  cout << "===============" << endl;
  comp.show_tree();
  return 0;
}
