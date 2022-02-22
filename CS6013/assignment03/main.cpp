#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shelpers.hpp"

void initShell();

using namespace std;

int main() {
    string input;
    vector<string> command;
    vector<Command> commands;

    initShell();

    while(true) {
        get_input(input);
        command = tokenize(input);
        commands = getCommands(command);

        processManager(commands);
    }
}



