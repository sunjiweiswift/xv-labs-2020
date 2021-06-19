#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int parent_fd[2], child_fd[2];
  if (pipe(parent_fd) < 0){
    printf("pingpong: pipe failed\n");
    exit(1);
  }
  if (pipe(child_fd) < 0){
    printf("pingpong: pipe failed\n");
    exit(1);
  }

  char buf[64];
  if (fork()) {
    // Parent
    write(parent_fd[1], "ping", strlen("ping"));
    read(child_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
  } else {
    // Child
    read(parent_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(child_fd[1], "pong", strlen("pong"));
  }
  exit(0);
}