#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shelpers.hpp"

void initShell();

using namespace std;

int main() {
    pid_t child_pid;
    string input;
    vector<string> command;
    vector<Command> commands;
    int stat_loc;

    initShell();

    while(true) {
        get_input(input);
        command = tokenize(input);
        commands = getCommands(command);

        if(command[0] == "exit") {
            return 0;
        }
        child_pid = fork();

        if (child_pid == 0) {
            // Child
            execvp(commands[0].execName.c_str(), const_cast<char* const*>(commands[0].argv.data()));
            exit(0);
        }
        else if (child_pid > 0) {
            // Parent
            waitpid(child_pid, &stat_loc, WUNTRACED);
            /*cout << "DEBUG" << endl;
            cout << (cout, commands[0]) << endl;*/
        }
        else {
            // Error
            perror("Fork failed, the program will now exit.");
            exit(1);
        }
    }


    return 0;
}

void initShell() {
    system("clear");
    cout << "*=======================================================*" << endl;
    cout << " ██▓    ▒██   ██▒  ██████  ██░ ██ ▓█████  ██▓     ██▓    \n"
            "▓██▒    ▒▒ █ █ ▒░▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    \n"
            "▒██░    ░░  █   ░░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    \n"
            "▒██░     ░ █ █ ▒   ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    \n"
            "░██████▒▒██▒ ▒██▒▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒\n"
            "░ ▒░▓  ░▒▒ ░ ░▓ ░▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\n"
            "░ ░ ▒  ░░░   ░▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\n"
            "  ░ ░    ░    ░  ░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   \n"
            "    ░  ░ ░    ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░\n"
            "                                                         " << endl;
    cout << "*=============== Created by Anirudh Lath ===============*" << endl << endl;
}

void get_input(istream &in) {
    string input;
    while(getline(in, input)) {

    }
}

