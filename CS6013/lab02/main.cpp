// Created by Anirudh Lath

#include <iostream>
#include <unistd.h>

void printError(int sc, char *message) {
    if(sc < 0) {
        perror(message);
        exit(1);
    }
}

void forkPipe(char *argv) {
    int fds[2]; // Read and Write
    int pipeCode = pipe(fds);
    if(pipeCode == -1) {
        perror("Pipe creation failed! Program will now exit!");
        exit(1);
    }

    int reader = fds[0];
    int writer = fds[1];

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed! System will now exit!");
        exit(1);
    } else if (pid == 0) {
        // CHILD PROCESS
        sleep(1);
        printf("child\n");

        // Read Size
        int size[1];
        int sc = read(reader, size, sizeof(size));
        printError(sc, "Reading size failed!");

        // Create array of size and read the string
        char str[size[0]];
        sc = read(reader, str, sizeof(str));
        printError(sc, "Reading data failed!");

        // Print the string
        for(int i = 0; i < size[0]; i++) {
            std::cout << str[i];
        }

        // Exit child process upon completion
        exit(0);

    } else {
        // PARENT PROCESS
        printf("parent\n");

        // Data
        char temp[strlen(argv)];

        for(int i = 0; i < strlen(argv); i++) {
            temp[i] = argv[i];
        }

        int size[1];
        size[0] = strlen(argv);

        // Write
        int sc = write(writer, size, sizeof(size));
        printError(sc, "Writing size failed!");
        sc = write(writer, temp, sizeof(temp));
        printError(sc, "Writing data failed!");

        // Wait
        int status;
        sc = waitpid(pid, &status, 0);
        printError(sc, "Waiting for child failed!");

    }

}

int main(int argc, char **argv) {
    forkPipe(argv[1]);
    return 0;
}
