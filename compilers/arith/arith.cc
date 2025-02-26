#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

enum class TokenType {
  NUM,
  END,
};

struct Token {
  TokenType type;
  std::string value;
};

bool is_num(std::string& str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), [](char c) {
        return std::isdigit(c);
      });
}

// return a vector of tokens from input
std::vector<Token> tokenize(std::stringstream& input) {
  std::vector<Token> res;
  std::string tok;
  const char del = ' ';

  while(std::getline(input, tok, del)) {
    if (is_num(tok)) {
      res.push_back({TokenType::NUM, tok});
    }
  }

  return res;
}

int main(int argc, char *argv[]) {
  // remove executable itself
  argc--;
  // no argument passed from the command line.
  if (argc < 1) {
    std::cerr << "no argument is passed\n";
    return 0;
  }

  // convert C-style string to std::string
  std::string arg = argv[1];
  std::stringstream input(arg);

  // tokenize input
  std::vector<Token> tokens = tokenize(input);
  // parse tokens
  for (auto& t : tokens) {
    std::cout << t.value << '\n';
  }
  return 0;
}
