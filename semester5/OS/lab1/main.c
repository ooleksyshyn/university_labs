#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "include/demofuncs.h"

bool f_res, g_res;
bool f_ready = false, g_ready = false;

pthread_mutex_t manager_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t something_happened = PTHREAD_COND_INITIALIZER;
bool something_happened_var = false;

void* calc_f(void* args) {
    int* x = (int *) args;
    f_res = f_func_or(*x);
    pthread_mutex_lock(&manager_mutex);

    f_ready = true;
    something_happened_var = true;

    pthread_mutex_unlock(&manager_mutex);

    pthread_cond_signal(&something_happened);
    return NULL;
}

void* calc_g(void* args) {
    int* x = (int *) args;
    g_res = g_func_or(*x);

    pthread_mutex_lock(&manager_mutex);

    g_ready = true;
    something_happened_var = true;

    pthread_mutex_unlock(&manager_mutex);

    pthread_cond_signal(&something_happened);
    return NULL;
}

bool need_quit = false;

pthread_cond_t wait_for_quit = PTHREAD_COND_INITIALIZER;
pthread_mutex_t wait_mutex = PTHREAD_MUTEX_INITIALIZER;
bool wait_mutex_var = false;


void* check_quit_message(void* arg) {
    char answer;
    printf("Do you you want to stop calculation?\n(y) yes\n(n) no\n");
    scanf("%s", &answer);
    if (answer == 'y') {
        pthread_mutex_lock(&manager_mutex);
        need_quit = true;
        something_happened_var = true;
        pthread_mutex_unlock(&manager_mutex);
        pthread_cond_signal(&something_happened);
        return NULL;
    }
    pthread_mutex_lock(&wait_mutex);
    need_quit = false;
    wait_mutex_var = true;
    pthread_mutex_unlock(&wait_mutex);

    pthread_cond_signal(&wait_for_quit);
    return NULL;
}

void* wait_for(void* arg) {
    sleep(15);
    pthread_mutex_lock(&wait_mutex);
    wait_mutex_var = true;
    need_quit = false;
    pthread_mutex_unlock(&wait_mutex);

    pthread_cond_signal(&wait_for_quit);
    return NULL;
}

bool show_quit_message() {
    need_quit = false;

    pthread_t thread_check_quit;
    pthread_create(&thread_check_quit, NULL, check_quit_message, NULL);
    pthread_t thread_wait_quit;
    pthread_create(&thread_wait_quit, NULL, wait_for, NULL);

    pthread_mutex_lock(&wait_mutex);
    while (!wait_mutex_var)
        pthread_cond_wait(&wait_for_quit, &wait_mutex);
    wait_mutex_var = false;

    pthread_cancel(thread_check_quit);
    pthread_cancel(thread_wait_quit);

    pthread_mutex_unlock(&wait_mutex);

    if (need_quit) {
        printf("Cancelling the calculations...\n");
        return true;
    } else {
        printf("Continue doing the calculations...\n");
        return false;
    }
}

pthread_mutex_t quit_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t quit_cond = PTHREAD_COND_INITIALIZER;
bool quit_var = false;

pthread_t* thread_read = NULL;

void* wait(void * arg) {
    sleep(15);
    pthread_mutex_lock(&quit_mutex);
    quit_var = true;
    pthread_mutex_unlock(&quit_mutex);
    pthread_cond_signal(&quit_cond);
    return NULL;
}

void* parse_q(void * arg) {
    char answer;
    while (true) {
        scanf("%s", &answer);
        if (answer == 'q') {
            pthread_mutex_lock(&quit_mutex);
            quit_var = true;
            pthread_mutex_unlock(&quit_mutex);
            pthread_cond_signal(&quit_cond);
            return NULL;
        }
    }
}


void* parse_input(void* args) {
    char c;
    while (true) {
        pthread_t thread_wait;
        pthread_t thread_parse_q;

        pthread_create(&thread_wait, NULL, wait, NULL);
        pthread_create(&thread_parse_q, NULL, parse_q, NULL);

        pthread_mutex_lock(&quit_mutex);
        while (!quit_var)
            pthread_cond_wait(&quit_cond, &quit_mutex);
        pthread_cancel(thread_wait);
        pthread_cancel(thread_parse_q);
        quit_var = false;
        bool quit = show_quit_message();
        pthread_mutex_unlock(&quit_mutex);
    }
}

void manager() {
    printf("Doing calculation of g(x) or f(x)....\n");
    bool f_ready_written = false;
    bool g_ready_written = false;
    while (true) {
        pthread_mutex_lock(&manager_mutex);
        while(!something_happened_var)
            pthread_cond_wait(&something_happened, &manager_mutex);
        something_happened_var = false;
        if (need_quit)
            return;
        if (g_ready && f_ready) {
            char* result = (g_res | f_res) ? "true" : "false";
            printf("result is ready: %s\n", result);
            return;
        }
        if (f_ready && !f_ready_written){
            f_ready_written = true;
            char* result = f_res ? "true" : "false";
            printf("f is ready: %s\n", result);
            if (f_res) {
                printf("Calculations result: true\n");
                return;
            }
        }
        if (g_ready && !g_ready_written) {
            g_ready_written = true;
            char* result = g_res ? "true" : "false";
            printf("g is ready: %s\n", result);
            if (g_res) {
                printf("Calculations result: true\n");
                return;
            }
        }

        pthread_mutex_unlock(&manager_mutex);
    }
}


int main() {
    printf("Starting program\nInput x:\n");
    int x;
    scanf("%d", &x);
    pthread_t thread_f;
    pthread_create(&thread_f, NULL, calc_f, (void*) &x);

    pthread_t thread_g;
    pthread_create(&thread_g, NULL, calc_g, (void*) &x);
    printf("press q to stop calculation\n");

    pthread_t quit_thread;
    pthread_create(&quit_thread, NULL, parse_input, NULL);

    manager();

    // make sure threads dont work anymore
    pthread_cancel(quit_thread);
    pthread_cancel(thread_f);
    pthread_cancel(thread_g);

    return 0;
}