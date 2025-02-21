#include <iostream>
#include <string>
#include <sstream>

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
  std::stringstream ss(arg);
  std::string tok;

  // parse tokens
  while (std::getline(ss, tok)){
    std::cout << tok << "\n";
  }
  return 0;
}
