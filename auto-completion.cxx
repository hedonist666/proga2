#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
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
        return x.second > y.second;
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
        e.children.push_back(tmp1);
        e.children.push_back(tmp);
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
    res.clear();
    Cr tmp {};
    for (auto& e : head) {
      run(input, e, tmp);
    }
    for (auto& e : res) {
      Cr str(e.begin(), e.end() - 1);
      std::cout << str << std::endl;
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
  char term = '_';
  ifstream ifs("input");  
  map<string, size_t> words;
  string buf;
  while (ifs >> buf) {
    words[buf]++;
  }
  stringstream ss{};
  for (auto [word, num] : words) {
    ss << word << term << ' ' << num;
    cout << word << ' ' << num << endl;
  }
  Completion<char, string> comp(ss, term);
  comp.show_tree();
  string word;
  cout << "===============" << endl;
  while (666) {
    cout << "type a word:" << endl;
    cin >> word;
    word += term;
    comp.show(word.begin());
  }
}
