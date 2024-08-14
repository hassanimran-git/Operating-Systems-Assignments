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
    int initial_clients;
    cout << "How many Clients? : ";
    cin >> initial_clients;
    int shm_id = shmget(key, size, IPC_CREAT | 0666);
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);

    pid_t pid = fork();
    if (pid == 0)
    {
        // opends terminal to read messages by running the file
        char *args[] = {"gnome-terminal", "--", "./READ_MEMORY", NULL};
        execvp(args[0], args);
        exit(1);
    }
    for (int i = 0; i < initial_clients; ++i)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            execlp("gnome-terminal", "gnome-terminal", "--", "./CLIENT", NULL);
            exit(1);
        }
    }
    int Choice = 1;
    while (Choice != 4)
    {
        cout << "1. ADD CLIENT\n2. CREATE GROUP\n3. REQUEST TO JOIN GROUP\n4. EXIT\nChoice: ";
        cin >> Choice;
        if (Choice == 1)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // foked process connects client by running file
                execlp("gnome-terminal", "gnome-terminal", "--", "./CLIENT", NULL);
                exit(1);
            }
        }
        else if (Choice == 2)
        {
            string name;
            getline(cin, name);
            cout << "GROUP NAME? : ";
            getline(cin, name);
            pid_t pid = fork();
            if (pid == -1)
            {
                cout << "Error forking group\n";
                exit(1);
            }
            else if (pid == 0)
            {
                // run group to create a group
                char group_arg[50];
                snprintf(group_arg, sizeof(group_arg), "%s", name.c_str());
                execlp("gnome-terminal", "gnome-terminal", "--", "./GROUP", group_arg, NULL);
                exit(1);
                exit(0);
            }
        }
        else if (Choice == 3)
        {
            string gname, name;
            getline(cin, name);
            cout << "ENTER USERNAME: ";
            getline(cin, name);
            cout << "ENTER GROUP NAME: ";
            getline(cin, gname);

            key_t key = 6274;
            int shm_id = shmget(key, size, 0666);
            char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
            string output = "\n" + name + " JOINED GROUP " + gname + "\n";
            strncpy(shm_ptr, output.c_str(), size);
            shm_ptr[size - 1] = '\0';
        }
        else if (Choice == 4)
        {

        }
        else {cout << "ERROR ! ENTER 1 TO 4!\n";}
    }
    // free memory 
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}
