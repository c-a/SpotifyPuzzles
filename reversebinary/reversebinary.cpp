#include <iostream>

int main(int argc, char* argv[])
{
  unsigned int N, Nr;

  std::cin >> N;

  // Reads rightmost bit in N and appends it to Nr.
  Nr = 0;
  while (N != 0) {
    // Shift previous written bits to the left
    Nr <<= 1;
    // "Append" bit
    Nr |= N & 0x1;
    // Shift away just read bit
    N >>= 1;
  }

  std::cout << Nr << std::endl;

  return 0;
}