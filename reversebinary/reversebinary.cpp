#include <iostream>

int main(int argc, char* argv[])
{
  unsigned int N, Nr;

  std::cin >> N;
  Nr = 0;
  while (N != 0) {
    Nr <<= 1;
    Nr |= N & 0x1;
    N >>= 1;
  }

 std::cout << Nr << std::endl;

  return 0;
}