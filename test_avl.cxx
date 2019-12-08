#define CATCH_CONFIG_MAIN
#include "libs/catch.hpp"
#include "avl.cxx"
#include <iostream>
#include <vector>
#include <utility>
#include <array>
#include <memory>





TEST_CASE("avl-tree") {
  SECTION("yields true with good avl tree") {
    AVL<char> tr {'c', 'b', 'd', 'a', 'e'};
    tr.show();
    std::cout << "--------------------" << std::endl;
    REQUIRE(tr.verify());
  }  
  SECTION("yields false with bad avl tree") {
    AVL<char> tr {'a', 'b', 'c', 'd', 'e'};
    tr.show();
    REQUIRE_FALSE(tr.verify());
  }  
}
