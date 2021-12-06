#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <string.h>

struct processIDs {
    pid_t pid;
    pid_t ppid;
    gid_t gid;
    gid_t egid;
    pid_t sid;
    uid_t uid;
    uid_t euid;
};


void printprocessIDs(FILE *file, struct processIDs *s) {
    fprintf(file, "pid %i\n", s->pid);
    fprintf(file, "ppid %i\n", s->ppid);
    fprintf(file, "gid %i\n", s->gid);
    fprintf(file, "egid %i\n", s->egid);
    fprintf(file, "sid %i\n", s->sid);
    fprintf(file, "uid %i\n", s->uid);
    fprintf(file, "euid %i\n", s->euid);
}

struct processIDs getprocessIDs() {
    struct processIDs info;
    info.pid = getpid();
    info.ppid = getppid();
    info.gid = getgid();
    info.egid = getegid();
    info.sid = getsid(0);
    info.uid = getuid();
    info.euid = geteuid();
    return info;
}
struct tm *getDate() {
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

int main(int argc, char **argv) {
    FILE *logFile = fopen("./log.txt", "w");

    fprintf(logFile, "program started %s\n", asctime(getDate()));
    fflush(logFile);
    pid_t childPid = fork();
    if (childPid < 0) {
        fprintf(stderr, "Error while forking\n");
        exit(EXIT_FAILURE);
    } else if (childPid > 0) {
        fprintf(logFile, "create child with PID %i\n", childPid);
        exit(EXIT_SUCCESS);
    } else {
        pid_t sid = setsid();
        fprintf(logFile, "create child with SID %i\n", sid);
        if (sid < 0) {
            fprintf(stderr, "Error while set sid\n");
            exit(EXIT_FAILURE);
        }
        printf("Create new session %i\n", sid);
        if (chdir("/") < 0) {
            fprintf(stderr, "Error while chdir to \"/\"\n");
            exit(EXIT_FAILURE);
        }
        int fdMax = getdtablesize();
        for (int i = 0; i < fdMax; i++) {
            close(i);
        }
        freopen("/dev/null", "r", stdin);
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);

        struct processIDs info = getprocessIDs();
        FILE *newLogFile = fopen("./log.txt", "a");
        printprocessIDs(stdout, &info);
        printprocessIDs(newLogFile, &info);
        fflush(newLogFile);
        while (1) {
            sleep(1);
            fprintf(newLogFile, "Infinite cycle...\n");
            fflush(newLogFile);
        }
        fflush(newLogFile);
        fclose(newLogFile);
        exit(EXIT_SUCCESS);
    }
}
