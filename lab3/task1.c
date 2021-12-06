#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

FILE *logFile;

void signal_handler(int signo, siginfo_t *sinfo, void *ucontext);

int main() {
    logFile = fopen("./log.txt", "a+t");
    printf("New process PID: %i\n", getpid());
    fprintf(logFile, "New process PID: %i\n", getpid());
    fflush(logFile);
    struct sigaction action;
    action.sa_handler = NULL;
    action.sa_sigaction = signal_handler;
    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGINT);
    action.sa_flags = SA_RESETHAND & SA_SIGINFO;
    struct sigaction oldHandler;
    sigaction(SIGHUP, &action, &oldHandler);

    while (1) {
        sleep(7);
        fprintf(logFile, "sleep\n");
        fflush(logFile);
    }
    exit(0);
}

void signal_handler(int signo, siginfo_t *sinfo, void *ucontext) {
    fprintf(logFile, "signal number: %i\n", sinfo->si_signo);
    fprintf(logFile, "signal code: %i\n", sinfo->si_code);
    fprintf(logFile, "signal value: %i\n", sinfo->si_value.sival_int);
    fprintf(logFile, "errno association: %i\n", sinfo->si_errno);
    fprintf(logFile, "process id: %i\n", sinfo->si_pid);
    fprintf(logFile, "user id: %i\n", sinfo->si_uid);
    fprintf(logFile, "siginfo address: %p\n", sinfo->si_addr);
    fprintf(logFile, "exit value: %i\n", sinfo->si_status);
    fprintf(logFile, "band event for SIGPOLL: %ld\n", sinfo->si_band);
    fflush(logFile);
}
