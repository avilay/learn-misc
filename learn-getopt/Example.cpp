#include <format>
#include <getopt.h>
#include <iostream>

/*
The following are defined in getopt.h
extern char *optarg;
extern int optind, opterr, optopt;
*/

int main(int argc, char** argv) {
  int opt;
  while ((opt = getopt(argc, argv, "-:a::b:X")) != -1) {
    switch (opt) {
    case 'a':
      if (optarg) {
        std::cout << std::format("Option a has value {}", optarg) << std::endl;
      } else {
        std::cout << "Option a was provided without any value." << std::endl;
      }
      break;
    case 'b':
      std::cout << std::format("Option b has value {}", optarg) << std::endl;
      break;
    case 'X':
      std::cout << "Option X was provided." << std::endl;
      break;
    case '?':
      std::cout << std::format("{} is an unknown option!", optopt) << std::endl;
      break;
    case 1:
      std::cout << std::format("Positional argument {}", optarg) << std::endl;
    }
  }
  std::cout << "Done." << std::endl;
}