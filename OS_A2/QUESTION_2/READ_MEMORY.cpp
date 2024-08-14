#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define size 1024
using namespace std;

int main() {
    key_t key = 6274;
    // attach
    int shm_id = shmget(key, size, IPC_CREAT | 0666);
    char* shm_ptr = (char* )shmat(shm_id, NULL, 0);
    strcpy(shm_ptr, "***************\nCHAT VISTA\n***************\n");
    string text = "";
    string same = "";
    while (1) {
        // loop to read and output messages writen to shared memory
        text = shm_ptr;
        if (text != same)
            cout << text << endl;
        same = text;
    }
    return 0;
}
