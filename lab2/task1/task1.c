#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
void processChild() {
    	int i;
  for (i = 0; i < 4; i++) {
    printf("Child pid %i\n", getpid());
    printf("Child ppid %i\n", getppid());
    printf("Child gid %i\n", getgid());
    printf("Child egid %i\n",  getegid());
    printf("Child sid %i\n", getsid(0));
    printf("Child uid %i\n",getuid());
    printf("Child euid %i\n\n", geteuid());
  }
    printf("Child process ended\n");
    exit(EXIT_SUCCESS);
}
void processParent() {
    
    int i;
  for (i = 0; i < 4; i++) {
    printf("Parent pid %i\n", getpid());
    printf("Parent ppid %i\n", getppid());
    printf("Parent gid %i\n", getgid());
    printf("Parent egid %i\n",  getegid());
    printf("Parent sid %i\n", getsid(0));
    printf("Parent uid %i\n",getuid());
    printf("Parent euid %i\n\n", geteuid());
  }
}

int main() {
  pid_t pid, gid, sid;
  pid = getpid();
  gid = getgid();
  sid = getsid(0);
  if (sid == -1) {
    printf("Error occured while trying to get sid of process");
  }
  printf("Before fork:\npid: %d\ngid: %d\nsid: %d\n", pid, gid, sid);
    pid_t childProcessPID = fork();
    if(childProcessPID < 0)
    {    
        fprintf(stderr, "%s: %s\n", "Fork failed", strerror(errno));
    exit(1);
    }
    if (childProcessPID == 0) {
        processChild();
    } else {
        printf("Parent process started\n");
        processParent();
        wait(NULL);
        printf("Parent process ended\n");
        exit(EXIT_SUCCESS);
    }

}
