#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
//for non blocking input
#include <termios.h>
#include <fcntl.h>
using namespace std;

int x1, y1, x2, y2; // Global variables for player coordinates
int object_x, object_y;
int score1 = 0, score2 = 0;

// Function to display the board
void displayBoard(char board[][100], int n)
{
    // Clear the board
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            board[i][j] = '*';
        }
    }

    // Set object position
    board[object_x][object_y] = 'X';
    // Set player positions
    board[x1][y1] = '1'; // Player 1
    board[x2][y2] = '2'; // Player 2

    // Display the board
    system("clear");
    cout << endl
         << "________________________________" << endl
         << endl
         << endl;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl
         << "________________________________" << endl;
    cout << "Player 1 Score: " << score1 << endl;
    cout << "Player 2 Score: " << score2 << endl;
}

// Function to process input for Player 1 and update player coordinates
void processInputPlayer1(char input, int &x, int &y)
{
    if (input == 'w' && x - 1 >= 0)
    {
        x--;
    }
    else if (input == 'a' && y - 1 >= 0)
    {
        y--;
    }
    else if (input == 's' && x + 1 < 100)
    {
        x++;
    }
    else if (input == 'd' && y + 1 < 100)
    {
        y++;
    }
}

// Function to process input for Player 2 and update player coordinates
void processInputPlayer2(char input, int &x, int &y, int n)
{
    if (input == 'i' && x - 1 >= 0)
    {
        x--;
    }
    else if (input == 'j' && y - 1 >= 0)
    {
        y--;
    }
    else if (input == 'k' && x + 1 < n)
    {
        x++;
    }
    else if (input == 'l' && y + 1 < n)
    {
        y++;
    }
}

//input without waiting for enter
// terminal to non-canonical + disables echoing 
//key presses are immediately detected. 
char getKeyPress()
{
    char keyPress = '\0';
    struct termios oldt, newt;
    int ch;
    int oldf;

    // Get current input mode
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Modify input mode to disable canonical mode (buffered i/o) and echo
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply new input mode immediately
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Set file descriptor to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Read a character from input
    ch = getchar();
    if (ch != EOF)
    {
        keyPress = ch;
    }

    // Restore old input mode and file descriptor settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return keyPress;
}

int main()
{
    // Generate board size
    srand(time(NULL));
    int n = rand() % 90 + 10; // Random number between 10 - 99
    n *= 3;                   // Multiply by last digit of roll number
    n = 813 / n;              // Divide your roll number by generated number
    n %= 25;                  // Take the mod of the result with 25
    if (n < 10)
    {
        n += 15;
    } // If num is less than 10, add 15 to it

    x1 = 0;
    y1 = 0;
    x2 = n - 1;
    y2 = n - 2;

    // Generate initial object position
    object_x = rand() % n;
    object_y = rand() % n;

    // Initialize the board with zeros
    char board[100][100];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            board[i][j] = '*';
        }
    }

    // Create pipes for communication with players
    int pipe_fd1[2];
    int pipe_fd2[2];
    if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1)
    {
        cout << "Error creating pipes." << endl;
        return 1;
    }

    cout << "Game Started " << endl;
    cout << "Board Size : " << n << "x" << n << endl;
    cout << "|wasd player1| - |ijkl player2|";

    int pid1 = fork();
    if (pid1 == -1)
    {
        cout << "Error forking first child." << endl;
        return 1;
    }
    else if (pid1 == 0)
    {
        // player 1
        close(pipe_fd1[0]); // close read end
        while (true)
        {
            char message = getKeyPress(); // get input
            if (message != '\0')
            {
                write(pipe_fd1[1], &message, sizeof(message));
                //input writen to pipe
            }
            usleep(10000); // Sleep for 10ms to avoid busy waiting
        }
        close(pipe_fd1[1]); // Close write end of the pipe
        return 0;
    }

    // Fork the second child
    int pid2 = fork();

    if (pid2 == -1)
    {
        cout<< "Error forking second child." << endl;
        return 1;
    }
    else if (pid2 == 0)
    {                       // Child process 2 (Player 2)
        close(pipe_fd2[0]); // Close read end of the pipe
        while (true)
        {
            char message = getKeyPress();
            if (message != '\0')
            {
                write(pipe_fd2[1], &message, sizeof(message));
            }
            usleep(10000); // Sleep for 10ms to avoid busy waiting
        }
        close(pipe_fd2[1]); // Close write end of the pipe
        return 0;
    }

    // Parent process
    close(pipe_fd1[1]); // Close write end of the pipe for player 1
    close(pipe_fd2[1]); // Close write end of the pipe for player 2

    char buffer1[100];
    char buffer2[100];

    displayBoard(board, n); // Pass player moves as parameters
    while (true)
    {
        // Read messages from both child processes
        // Process inputs and move players

        int nbytes1 = read(pipe_fd1[0], buffer1, sizeof(buffer1));
        if (nbytes1 > 0)
        {
            processInputPlayer1(buffer1[0], x1, y1); // Process player 1 input WASD
            if (x1 == object_x && y1 == object_y)
            {
                score1 += 10;
                object_x = rand() % n;
                object_y = rand() % n;
            }
            displayBoard(board, n); // Display the board
        }

        int nbytes2 = read(pipe_fd2[0], buffer2, sizeof(buffer2));
        if (nbytes2 > 0)
        {
            //IJKL
            processInputPlayer2(buffer2[0], x2, y2, n); // Process player 2 input
            if (x2 == object_x && y2 == object_y)
            {
                score2 += 10;
                object_x = rand() % n;
                object_y = rand() % n;
            }
            displayBoard(board, n); // Display the board
        }
    }

    close(pipe_fd1[0]); // Close read end of the pipe for player 1
    close(pipe_fd2[0]); // Close read end of the pipe for player 2

    cout << "Parent exiting." << endl;

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}
