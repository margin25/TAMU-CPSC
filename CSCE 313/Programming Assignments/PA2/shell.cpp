#include <iostream>
#include <cstring>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <vector>
#include <string>

#include "Tokenizer.h"
// include for open rd_only
#include <sys/stat.h>
#include <fcntl.h>

// all the basic colours for a shell prompt
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define WHITE "\033[1;37m"
#define NC "\033[0m"

using namespace std;

int main()
{
    // create copies of stdin/stdout;
    int the_stdin = dup(0);
    int the_stdout = dup(1);
    vector<int> bg_pid;
    char curr_directory[256];
    char prev_directory[256];
    getcwd(prev_directory, 256);
    getcwd(curr_directory, 256);
    while (true)
    {
        for (size_t k = 0; k < bg_pid.size(); k++)
        {
            if (waitpid(bg_pid[k], 0, WNOHANG) != 0) // if it returns zero then its not done, if it returns zero then its done
            {
                cout << "background process done" << endl;
                bg_pid.erase(bg_pid.begin() + k);
                k--;
            }
        }
        // implement iteration over vector of bg pid (vector also declared outside loop)
        // waitpid() - using flag for non-blocking

        // implement date/time 
        time_t clock = time(NULL);
        char* current_time = ctime(&clock);
        char* username = getenv("USER"); // implement username with getenv("USER")
        current_time[strlen(current_time)-1] = '\0';
        cout << YELLOW << current_time << username << curr_directory << " "; // need date/time, username, and absolute path to current dir

        // get user inputted command
        string input;
        getline(cin, input);

        if (input == "exit")
        { // print exit message and break out of infinite loop
            cout << RED << "Now exiting shell..." << endl
                 << "Goodbye" << NC << endl;
            break;
        }

        // implement cd with chdir()
        // if dir (cd <dir>) is '-', then go to previous working directory
        // variable storing previous working directory(it needs to be declared outside loop)

        // get tokenized commands from user input
        Tokenizer tknr(input);
        if (tknr.hasError())
        { // continue to next prompt if input had an error
            continue;
        }

        // // print out every command token-by-token on individual lines
        // prints to cerr to avoid influencing autograder
        /* for (auto cmd : tknr.commands)
        {
            for (auto str : cmd->args)
            {
                cerr << "|" << str << "| ";
            }
            if (cmd->hasInput())
            {
                cerr << "in< " << cmd->in_file << " ";
            }
            if (cmd->hasOutput())
            {
                cerr << "out> " << cmd->out_file << " ";
            }
            cerr << endl;
        } */
        // for piping
        // for cmd : commands
        //   call pipe() to make pipe
        //   fork() - in child, redirect stdout, in parent redirect stdin
        //   ^ is already written
        // add checks for first/last command

        // || cd ||
        if (tknr.commands.at(0)->args[0] == "cd")
        {
            if (tknr.commands.at(0)->args.size() > 1)
            { // if multiple arguments present
                if (tknr.commands.at(0)->args[1] == "-")
                {
                    getcwd(curr_directory, 256); // takes current working directory and puts it in the curr_directory variable
                    chdir(prev_directory);       // changes directory to prev_directory
                    for (size_t i = 0; i < 256; i++)
                    {
                        prev_directory[i] = curr_directory[i]; // deep copy because we cant just set prev directory = curr directory
                    }
                    getcwd(curr_directory, 256); // path of current directory
                }
                else
                {                                // if not cd -  , cd <path>
                    getcwd(prev_directory, 256); // takes current working directory and puts it in the prev_directory variable
                    chdir(tknr.commands.at(0)->args[1].c_str());
                    getcwd(curr_directory, 256); // takes current working directory and puts it in the curr_directory variable
                }
            }
            continue; // you dont want exec to call the cd
        }

        else if (tknr.commands.at(0)->args[0] == "pwd")
        {
            cout << curr_directory << endl;
            continue;
        }
        for (size_t m = 0; m < tknr.commands.size(); m++)
        {

            // fork to create child
            int fd[2]; // in n out
            pipe(fd);
            pid_t pid = fork();
            if (pid < 0)
            { // error check
                perror("fork");
                exit(2);
            }

            // add check for bg process - add pid to vector if bg and don't waitpid() in parent

            if (pid == 0)
            { // if child, exec to run command
                // implement multiple arguments - iterate over args of current command to make
                //            char* array
                int num_flags = tknr.commands.at(m)->args.size(); // num of arguments/flags (for example, 'ls -ls' has two arguments)
                char **args = new char *[num_flags + 1];          // dynamically allocated array , +1 for to account for null termination , pointer to each individual unchangeable c string element
                for (size_t i = 0; i < tknr.commands.at(m)->args.size(); i++)
                {
                    char *buf = new char[tknr.commands.at(m)->args.at(i).size() + 1];
                    memcpy(buf, tknr.commands.at(m)->args.at(i).c_str(), (tknr.commands.at(m)->args.at(i).size()) + 1); // size +1 to account for nullbyte at end of each element
                    args[i] = buf;
                }
                args[num_flags] = nullptr;

                // if current command is redirected, then open file and dup2 std(in/out) that's being redirected
                // implement it safely for both at same time

                // || INPUT REDIRECTION ||
                if (tknr.commands.at(m)->hasInput())
                {
                    int fds = open(tknr.commands.at(m)->in_file.c_str(), O_RDONLY); // opens file so we can dup
                    if (fds == -1)
                    {
                        perror("open");
                        exit(1);
                    }
                    // redirected output
                    if (dup2(fds, 0) == -1)
                    {
                        perror("dup2");
                        exit(1);
                    }
                }
                // || OUTPUT REDIRECTION ||
                if (tknr.commands.at(m)->hasOutput())
                {
                    int fds = open(tknr.commands.at(m)->out_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // opens file so we can dup
                    if (fds == -1)
                    {
                        perror("open");
                        exit(1);
                    }
                    // redirected output
                    if (dup2(fds, 1) == -1)
                    {
                        perror("dup2");
                        exit(1);
                    }
                }
                // am i at last command (piping)
                if (m < (tknr.commands.size() - 1))
                {
                    dup2(fd[1], 1);
                    close(fd[0]);
                }

                if (execvp(args[0], args) < 0) // child killed
                {                              // error check
                    perror("execvp");
                    exit(2);
                }
            }
            else // if parent, wait for child to finish
            {
                // check for background
                if (tknr.commands.at(m)->isBackground() == true)
                {
                    bg_pid.push_back(pid);
                }
                else
                {
                    if (m < (tknr.commands.size() - 1))
                    {
                        dup2(fd[0], 0);                   
                        close(fd[1]);
                    }
                    int status = 0;
                    waitpid(pid, &status, 0);
                    if (status > 1)
                    { // exit if child didn't exec properly
                        exit(status);
                    }
                }
            }
        }
        // restore stdin/stdout (variable would be outside the loop)
        dup2(the_stdin, 0);
        dup2(the_stdout, 1);
    }
}
