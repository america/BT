#include <iostream>
#include <cstdlib>
#include <ext/stdio_filebuf.h>
  
int main() {

  std::string cmd = "echo -e connect 00:19:5D:25:05:E5 | bluetoothctl";

  FILE *fp = popen(cmd.c_str(), "r");

  // streambufを作成し，istreamのコンストラクタに渡す
  __gnu_cxx::stdio_filebuf<char> *p_fb = new __gnu_cxx::stdio_filebuf<char>(fp, std::ios_base::in);
  std::istream input(static_cast<std::streambuf *>(p_fb));

  // getlineでストリームからコマンド出力を受け取る
  std::string buffer;
  while(getline(input, buffer)){
    std::cout << "out > " << buffer << std::endl;
  }

  // 最後に解放
  delete p_fb;
  pclose(fp);

  return 0;
}
