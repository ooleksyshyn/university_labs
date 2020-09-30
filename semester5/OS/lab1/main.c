#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "include/demofuncs.h"

bool f_res, g_res;
bool f_ready = false, g_ready = false;

void* calc_f(void* args) {
    int* x = (int *) args;
    f_res = f_func_or(*x);
    f_ready = true;
    return NULL;
}

void* calc_g(void* args) {
    int* x = (int *) args;
    g_res = g_func_or(*x);
    g_ready = true;
    return NULL;
}

bool need_quit = false;
bool is_running = false;

void* check_quit_message(void* arg) {
    is_running = true;
    char answer;
    scanf("%s", &answer);
    if (answer == 'y') {
        need_quit = true;
        is_running = false;
        return NULL;
    }
    need_quit = false;
    is_running = false;
    return NULL;
}

bool show_quit_message() {
    printf("Are you sure you want to stop calculation?\n(y) yes\n(n) no\n");
    need_quit = false;

    pthread_t thread_check_quit;
    pthread_create(&thread_check_quit, NULL, check_quit_message, NULL);

    for (int i = 0; i < 15; ++i) {
        // wait 15 second for answer
        sleep(1);
        if (!is_running)
            break;
    }
    pthread_cancel(thread_check_quit);

    if (need_quit) {
        printf("Cancelling the calculations...\n");
        return true;
    } else {
        printf("Continue doing the calculations...\n");
        return false;
    }
}

void* parse_input(void* args) {
    char c;
    while (true) {
        scanf("%c", &c);
        if (c == 'q') {
            bool quit = show_quit_message();
            if (quit)
                return NULL;
        }
    }
}

void manager() {
    printf("Doing calculations....\n");
    bool f_ready_written = false;
    bool g_ready_written = false;
    while (true) {
        sleep(3);
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