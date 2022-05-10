#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

pthread_t tid[NUM_THREADS];
void sig_func(int sig){
    float r = (float)rand()/(float)RAND_MAX;
    //printf("random number to base thread decision off of: %f\n", r);
    printf("Caught signal no = %d\n", sig);
    //signal(sig, sig_func);

    if (r> 0.513 && (sig == 2 || sig == 4 || sig == 6) ){
        printf("Sending signal to thread: 0\n");
        pthread_kill(tid[0], sig);
        pthread_kill(tid[3], sig);
        //pthread_kill(tid[0], SIGINT);
        //pthread_kill(tid[0], SIGILL);
        //pthread_kill(tid[0], SIGABRT);
    } else if (sig == 2 || sig == 4 || sig == 6) {
        pthread_kill(tid[3], sig);
        printf("Sending signal to thread: 3\n");
        //pthread_kill(tid[3], SIGINT);
        //pthread_kill(tid[3], SIGILL);
        //pthread_kill(tid[3], SIGABRT);
    }
    

    if ( (r > 0.5 && sig == 17) || sig == 11 || sig == 8 ){
        printf("Sending signal to thread: 1\n");
        pthread_kill(tid[1], sig);
        //pthread_kill(tid[1], SIGCHLD);
        //pthread_kill(tid[1], SIGSEGV);
        //pthread_kill(tid[1], SIGFPE);
    }

    if ( (r <= 0.5 && sig == 17) ||  sig == 1 || sig == 20 ){
        printf("Sending signal to thread: 2\n");
        pthread_kill(tid[2], sig);
        //pthread_kill(tid[2], SIGCHLD);
        //pthread_kill(tid[2], SIGHUP);
        //pthread_kill(tid[2], SIGTSTP);
    }
}

void sig_func2(int sig) {
    printf("Caught and handled signal no = %d, in thread 0\n", sig);
}

void sig_func3(int sig) {
    printf("Caught and handled signal no = %d, in thread 1\n", sig);
}

void sig_func4(int sig) {
    printf("Caught and handled signal no = %d, in thread 2\n", sig);
}

void sig_func5(int sig) {
    printf("Caught and handled signal no = %d, in thread 3\n", sig);
}

void *threadFunc (void *thread_id) {

    int id = *((int*)thread_id);
    // if (id == 0 ) {
    //     signal( SIGINT, sig_func2);
    //     signal( SIGABRT, sig_func2);
    //     signal( SIGILL, sig_func2);
    // } 
    // if (id == 1 ) {
    //     signal(SIGCHLD, sig_func3);
    //     signal(SIGSEGV, sig_func3);
    //     signal(SIGFPE, sig_func3);
    // }
    // if (id ==2 ) {
    //     signal(SIGHUP, sig_func4);
    //     signal(SIGTSTP, sig_func4);
    //     signal(SIGCHLD, sig_func4);
    // }
    // if (id == 3 ) {
    //     signal(SIGFPE, sig_func5);
    //     signal(SIGTSTP, sig_func5);
    //     signal( SIGINT, sig_func5);
    // }
    printf("Thread number %d \n", id);

}

int main () {

    //initializing random variable based off time. 
    srand(time(NULL));

    //print process id
    printf("process id: %d \n", getpid());
    
    signal(SIGINT, sig_func);
    signal(SIGABRT, sig_func);
    signal(SIGILL, sig_func);
    signal(SIGCHLD, sig_func);
    signal(SIGSEGV, sig_func);
    signal(SIGFPE, sig_func);
    signal(SIGHUP, sig_func);
    signal(SIGTSTP, sig_func);

    sleep(1);

    int ids[4];
    for (int i = 0; i < NUM_THREADS; i++){
        ids[i] = i;
        pthread_create(&tid[i], NULL, (void*)threadFunc, &ids[i]);
    }
    
sleep(20);

    //sending signals our program
    // kill(getpid(), SIGINT);
    // kill(getpid(), SIGABRT);
    // kill(getpid(), SIGILL);
    // kill(getpid(), SIGCHLD);
    // kill(getpid(), SIGSEGV);
    // kill(getpid(), SIGFPE);
    // kill(getpid(), SIGHUP);
    // kill(getpid(), SIGTSTP);

    sleep(1);
    
    for ( int i = 0; i < NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    // restore default behaviors
    signal(SIGINT, SIG_DFL);
    signal(SIGABRT, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    signal(SIGHUP, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);

    return 0;
}

