#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int pipefd[2];

int do_parent() {
  
  int status;
  int ret = 0;
  
  close(pipefd[0]); //読み込みをクローズ

  char *s = "connect 00:19:5D:25:05:E5";

  errno = 0;
  if(write(pipefd[1], s, strlen(s)) < 0) {
    perror("write");
    printf("%s\n", strerror(errno));
  }
  
  close(pipefd[1]);

  sleep(10);
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
    printf("親プロセス終了\n");
  } else {
    ret = -1;
  }
  return ret;
}

int do_child() {
  printf("子プロセス開始\n");
  
  int ret = 0;

  close(pipefd[1]); //書き込みをクローズ

  dup2(pipefd[0], STDIN_FILENO); //パイプの読み込みを標準入力につなぐ
  close(pipefd[0]);              //つないだらパイプはクローズする

  errno = 0;
  execl("/usr/bin/bluetoothctl", "/usr/bin/bluetoothctl", NULL);
  if(errno != 0) {
    perror("execl");
    printf("%s\n", strerror(errno));
    ret = 1;
  }

  printf("子プロセス終了\n");
  return ret;
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
    if(do_child()) return -1;
  } else {
    // 親プロセス
    if(do_parent()) return -1;
  }
  return 0;
}
