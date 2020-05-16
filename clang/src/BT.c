#include <stdio.h>
#include <stdlib.h>
  
int main(void) {
  FILE *fp, *outputfile;
  char ret[40];

  fp = popen("echo -e connect 00:19:5D:25:05:E5 | bluetoothctl", "r");
  while(fgets(ret, sizeof ret, fp) != NULL) {
    printf("%s", ret);
  }
  pclose(fp);

  outputfile = fopen("text.txt", "a");
  fprintf(outputfile, "%s\n", ret);
  fclose(outputfile);
  return 0;
}
