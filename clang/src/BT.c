#include <stdio.h>

int main()
{
  const char *command01 = "bluetoothctl";
    // "                 connect 00:19:5D:25:05:E5";
  
  char *command02 = "connect 00:19:5D:25:05:E5";

  
  system(command01);
  printf("%s", command02);
  // system(command02);
  return 0;

}
