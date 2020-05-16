#if 0
g++ --std=c++14 "$0" -o ../cpp-BT && ../cpp-BT
exit
#endif

#include <iostream>
#include <fstream>
  
int main(void) {
  std::system("bluetoothctl");
  std::system("connect 00:19:5D:25:05:E5");
  return 0;
}
