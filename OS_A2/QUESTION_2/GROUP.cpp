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

int main(int argc, char* argv[]) {

    key_t key = 6274;
    // attack to segement
    int shm_id = shmget(key, size, IPC_CREAT | 0666);
    char* shm_ptr = (char* )shmat(shm_id, NULL, 0);
    
    string groupName = argv[1];
    strcpy(shm_ptr, ("WELCOME TO " + groupName + "!\n").c_str());
    string text = "";
    string prev = "";
    while (true) {
        text = shm_ptr; // retive messge from memory
        if (text != prev)
            cout << text << endl;
        prev = text;
        //set prev to text to checkin next iteration
        //print only if new text
    }
    return 0;
}

