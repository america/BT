#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int pipefd[2];

void do_parent() {
  int status;
  
  close(pipefd[0]); //読み込みをクローズ

  char *s = "connect 00:19:5D:25:05:E5";

  write(pipefd[1], s, strlen(s));
  close(pipefd[1]);

  sleep(3);
  // 子プロセスの状態変化を待つ
  wait(&status);

  // 終了ステータスのチェック
  if(WIFEXITED(status)) {
    printf("親プロセス：子プロセスは%dで正常終了しました\n",
	   WEXITSTATUS(status));
  }
  if (WIFSIGNALED(status)) {
    printf("親プロセス : 子プロセスはシグナル番号%dで終了しました\n",
	   WTERMSIG(status));
  }
}

void do_child() {

  close(pipefd[1]); //書き込みをクローズ

  dup2(pipefd[0], STDIN_FILENO); //パイプの読み込みを標準入力につなぐ
  close(pipefd[0]);              //つないだらパイプはクローズする

  execl("/usr/bin/bluetoothctl", "/usr/bin/bluetoothctl", NULL);
}

int main()
{
  
  if (pipe(pipefd) < 0) {
    perror("pipe");
    exit(-1);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(-1);
  } else if (pid == 0) {
    // 子プロセス
    do_child();
  } else {
    // 親プロセス
    do_parent();
  }
  return 0;
}
