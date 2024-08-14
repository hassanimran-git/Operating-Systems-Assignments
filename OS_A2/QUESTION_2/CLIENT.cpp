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

int main()
{
    key_t key = 6274;
    // attack mem
    int shm_id = shmget(key, size, 0666);
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    string name = "";

    cout << "ENTER NAME : ";
    getline(cin, name);
    string output;
    output = name + " CONNECTED!\n";
    // write message to memory indincatiin client connection
    strncpy(shm_ptr, output.c_str(), size);
    shm_ptr[size - 1] = '\0';
    string msg = "";
    cout << "Write \"Leave\" to leave the Chat\n";
    while (1)
    {
        //loop to write typed messages to shared memory
        cout << "TYPE MESSAGE : ";
        getline(cin, msg);

        output = name + ": " + msg + "\n";
        strncpy(shm_ptr, output.c_str(), size);
        shm_ptr[size - 1] = '\0';
    }
    return 0;
}
