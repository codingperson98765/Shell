//Author :Ahmedh Shamsudeen 30121541




#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <time.h>
#include<fcntl.h>	
#include <unistd.h>
#include <string.h>
#include <cstdio>
#include <sys/wait.h>
#include <iostream>
#include <cstring>
#include <strings.h>
#include <vector>
#include <ios>
using namespace std;


#define WRITE_END 1
#define READ_END 0


void loop(void);
char *read_line(void);

int main(int argc, char **argv)
{  
  loop();
  return EXIT_SUCCESS;
}

void loop(void)
{
  char *line;
  char **args;
  int test = 1;
  
//shell prompt
  do {
    cout << "#> ";
    read_line();
    } while (test);
}
char *read_line(void){
    vector<string> vect1;
    vector<string> beforeDelim;
    vector<string> afterDelim;
    int n;
    int i = 0;
    int valid;
    
    std::string delimiter = " $ ";
    std::string space = " ";
    size_t pos = 0;
    size_t posSpace = 0;
    std::string token;
    std::string subToken;
    
    std::string input;
    std::getline(std::cin, input);
    
    vect1.push_back(input);
    //parsing string input to see if $ used
    if ((input.find(delimiter)) != std::string::npos){
       while ((pos = input.find(delimiter)) != std::string::npos) 
    {
        token = input.substr(0, pos);
       
        if ((token.find(space)) != std::string::npos){
            while ((posSpace = token.find(space)) != std::string::npos){
              subToken = token.substr(0,posSpace);
              
              beforeDelim.push_back(subToken);
              token.erase(0, posSpace + space.length());
            }
            beforeDelim.push_back(token);
            
            input.erase(0, pos + delimiter.length());
            
        }
        else{
        
        beforeDelim.push_back(token);
        input.erase(0, pos + delimiter.length());
        }
       }
          

        if ((input.find(space)) != std::string::npos){
            while ((posSpace = input.find(space)) != std::string::npos){
              token = input.substr(0,posSpace);
              //item after pipe
              afterDelim.push_back(token);
              input.erase(0, posSpace + space.length());
            }
            afterDelim.push_back(input);
            
            
        }
        //item after pipe
        else{
        afterDelim.push_back(input);
        }

    int leftNum = beforeDelim.size();
    int rightNum = afterDelim.size();
    

    //case where cmd $ cmd cmd, code based of TA Alex
    if (leftNum == 1 && rightNum == 2){
      


      int fds[2];
      pipe(fds);

      pid_t pid = fork();

      if (pid == -1)
                printf("Error forking\n");
      //Child # 1 (This is the last child to run, it will run "cat", taking input from the pipe)
            else if (pid == 0)
            {
                //Redirect standard input to be the read end of the pipe
                dup2(fds[READ_END], fileno(stdin));

                //Close undeeded pipes
                close(fds[READ_END]);
                close(fds[WRITE_END]);

                
                // this execvp call so it will use stdin
                //However, stdin now points to the read end of the pipe so cat will use the contents of the pipe
                n = afterDelim[0].length();
                char command4[n + 1];
                strcpy(command4, afterDelim[0].c_str());
                char* right2[] = {command4, NULL};
                execvp(right2[0], right2);
                perror("Error executing command on the right of $");
                exit(EXIT_FAILURE);
            }
            //Parent
            else
            {
                pid_t pid2 = fork();
                //Error
                if (pid2 == -1)
                    perror("Error forking");
                //Child # 2 
                else if (pid2 == 0)
                {
                    //redirect output here 
                    dup2(fds[WRITE_END], fileno(stdout));

                    //Close undeeded pipes
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    n = beforeDelim[0].length();
                    char command3[n + 1];
                    strcpy(command3, beforeDelim[0].c_str());
                    char* right1[] = {command3, NULL};
                    execvp(right1[0], right1);
                    perror("Error executing command on left of $");
                    exit(EXIT_FAILURE);   
                }
                //Parent
                else
                {
                    int status;
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Wait for child 3
                        waitpid(pid2, &status, 0);
                }
                    int status;
                //Wait for child1
                waitpid(pid, &status, 0);
                }
        fds[2];
      pipe(fds);

      pid = fork();

      if (pid == -1)
                printf("Error forking\n");
      //Child # 1 (This is the last child to run, it will run "cat", taking input from the pipe)
            else if (pid == 0)
            {
                //Redirect standard input to be the read end of the pipe
                dup2(fds[READ_END], fileno(stdin));

                //Close undeeded pipes
                close(fds[READ_END]);
                close(fds[WRITE_END]);
                // this execvp call so it will use stdin
                //However, stdin now points to the read end of the pipe so cat will use the contents of the pipe 
                n = afterDelim[1].length();
                char command4[n + 1];
                strcpy(command4, afterDelim[1].c_str());
                char* right2[] = {command4, NULL};
                execvp(right2[0], right2);
                perror("Error executing 2nd command on the right of $");
                exit(EXIT_FAILURE);
            }
            //Parent
            else
            {
                pid_t pid2 = fork();
                //Error
                if (pid2 == -1)
                    perror("Error forking");
                //Child # 2 (This is the second child to run "ls", putting output into pipe)
                else if (pid2 == 0)
                {
                    dup2(fds[WRITE_END], fileno(stdout));
                    //Close undeeded pipes
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    n = beforeDelim[0].length();
                    char command3[n + 1];
                    strcpy(command3, beforeDelim[0].c_str());
                    char* right1[] = {command3, NULL};
                    execvp(right1[0], right1);
                    perror("Error executing command on left of $");
                    exit(EXIT_FAILURE);                    
                }
                //Parent
                else
                {
                    int status;
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    //Wait for child 3
                    waitpid(pid2, &status, 0);
                }
                    int status;
                //Wait for child1
                waitpid(pid, &status, 0);
                }
    }
    //if cmd cmd $ cmd exceute with execvp code based of TA Alex
    if (leftNum == 2 && rightNum == 1){

      int fds[2];
      pipe(fds);

      pid_t pid = fork();

      if (pid == -1)
                printf("Error forking\n");
      //Child # 1 (This is the last child to run, it will run "cat", taking input from the pipe)
            else if (pid == 0)
            {
                //Redirect standard input to be the read end of the pipe
                dup2(fds[READ_END], fileno(stdin));

                //Close undeeded pipes
                close(fds[READ_END]);
                close(fds[WRITE_END]);

                // this execvp call so it will use stdin
                //However, stdin now points to the read end of the pipe will use the contents of the pipe 
                n = afterDelim[0].length();
                char command4[n + 1];
                strcpy(command4, afterDelim[0].c_str());
                char* right1[] = {command4, NULL};
                execvp(right1[0], right1);
                perror("Error executing command on the right of $");
                exit(EXIT_FAILURE);
            }
            //Parent
            else
            {
                pid_t pid2 = fork();
                //Error
                if (pid2 == -1)
                    perror("Error forking");
                //Child # 2 (This is the second child to run "ls", putting output into pipe)
                else if (pid2 == 0)
                {
                    //Note we don't need to redirect output here because child#3 (whom runs first) already did it
                    dup2(fds[WRITE_END], fileno(stdout));
                    //Close undeeded pipes
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    //output will automatically go to pipe due to Child#3's redirection
                    n = beforeDelim[1].length();
                    char command3[n + 1];
                    strcpy(command3, beforeDelim[1].c_str());
                    char* left2[] = {command3, NULL};
                    execvp(left2[0], left2);
                    perror("Error executing 2nd command on left of $");
                    exit(EXIT_FAILURE);                    
                }
                //Parent
                else
                {
                    pid_t pid3 = fork();
                    //Error
                    if (pid3 == -1)
                        perror("Error forking");
                    //Child # 3 (This is the first child to run - it will run "pwd")
                    else if (pid3 == 0)
                    {
                        //Redirect stdout to fds[WRITE_END] so that execvp automatically writes to the pipe
                        dup2(fds[WRITE_END], fileno(stdout));
                        //Close uneeded fds
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Execvp command                      
                        n = beforeDelim[0].length();
                        char command2[n + 1];
                        strcpy(command2, beforeDelim[0].c_str());
                        char* left1[] = {command2, NULL};
                        execvp(left1[0], left1);
                        perror("Error executing 1st command on left of $");
                        exit(EXIT_FAILURE);
                    }
                    //Parent
                    else
                    {
                        int status;
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Wait for child 3
                        waitpid(pid3, &status, 0);
                    }
                    int status;
                    //Wait for child2
                    waitpid(pid2, &status, 0);
                }
                int status;
                //Wait for child1
                waitpid(pid, &status, 0);
            }      
    }
    //if cmd cmd $ cmd cmd then implement with execvp code based of TA Alex
    else if (leftNum == 2 && rightNum == 2){

      int fds[2];
      pipe(fds);

      pid_t pid = fork();

      if (pid == -1)
                printf("Error forking\n");
      //Child # 1 (This is the last child to run, it will run "cat", taking input from the pipe)
            else if (pid == 0)
            {
                //Redirect standard input to be the read end of the pipe
                dup2(fds[READ_END], fileno(stdin));
                //Close undeeded pipes
                close(fds[READ_END]);
                close(fds[WRITE_END]);
                // this execvp call so it will use stdin
                //However, stdin now points to the read end of the pipe so cat will use the contents of the pipe 
                n = afterDelim[0].length();
                char command4[n + 1];
                strcpy(command4, afterDelim[0].c_str());
                char* right1[] = {command4, NULL};
                execvp(right1[0], right1);
                perror("Error executing command on the right of $");
                exit(EXIT_FAILURE);
            }
            //Parent
            else
            {
                pid_t pid2 = fork();
                //Error
                if (pid2 == -1)
                    perror("Error forking");
                //Child # 2 (This is the second child to run "ls", putting output into pipe)
                else if (pid2 == 0)
                {
                    //Note we don't need to redirect output here because child#3 (whom runs first) already did it
                    dup2(fds[WRITE_END], fileno(stdout));
                    //Close undeeded pipes
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    //Run "ls", output will automatically go to pipe due to Child#3's redirection
                    n = beforeDelim[1].length();
                    char command3[n + 1];
                    strcpy(command3, beforeDelim[1].c_str());
                    char* left2[] = {command3, NULL};
                    execvp(left2[0], left2);
                    perror("Error executing 2nd command on left of $");
                    exit(EXIT_FAILURE);                    
                }
                //Parent
                else
                {
                    pid_t pid3 = fork();
                    //Error
                    if (pid3 == -1)
                        perror("Error forking");
                    //Child # 3 (This is the first child to run - it will run "pwd")
                    else if (pid3 == 0)
                    {
                        //Redirect stdout to fds[WRITE_END] so that execvp automatically writes to the pipe
                        dup2(fds[WRITE_END], fileno(stdout));
                        //Close uneeded fds
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Execvp command
                        n = beforeDelim[0].length();
                        char command2[n + 1];
                        strcpy(command2, beforeDelim[0].c_str());
                        char* left1[] = {command2, NULL};
                        execvp(left1[0], left1);
                        perror("Error executing 1st command on left of $");
                        exit(EXIT_FAILURE);
                    }
                    //Parent
                    else
                    {
                        int status;
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Wait for child 3
                        waitpid(pid3, &status, 0);
                    }
                    int status;
                    //Wait for child2
                    waitpid(pid2, &status, 0);
                }
                int status;
                //Wait for child1
                waitpid(pid, &status, 0);
            }


             fds[2];
      pipe(fds);

       pid = fork();

      if (pid == -1)
                printf("Error forking\n");
      //Child # 1 (This is the last child to run, it will run "cat", taking input from the pipe)
            else if (pid == 0)
            {
                //Redirect standard input to be the read end of the pipe
                dup2(fds[READ_END], fileno(stdin));

                //Close undeeded pipes
                close(fds[READ_END]);
                close(fds[WRITE_END]);
                //this execvp call so it will use stdin
                //However, stdin now points to the read end of the pipe so cat will use the contents of the pipe 
                n = afterDelim[1].length();
                char command4[n + 1];
                strcpy(command4, afterDelim[1].c_str());
                char* right1[] = {command4, NULL};
                execvp(right1[0], right1);
                perror("Error executing 2nd command on the right of $");
                exit(EXIT_FAILURE);
            }
            //Parent
            else
            {
                pid_t pid2 = fork();
                //Error
                if (pid2 == -1)
                    perror("Error forking");
                //Child # 2 (This is the second child to run "ls", putting output into pipe)
                else if (pid2 == 0)
                {
                    //Note we don't need to redirect output here because child#3 (whom runs first) already did it
                    dup2(fds[WRITE_END], fileno(stdout));
                    //Close undeeded pipes
                    close(fds[READ_END]);
                    close(fds[WRITE_END]);
                    // output will automatically go to pipe due to Child#3's redirection
                    n = beforeDelim[1].length();
                    char command3[n + 1];
                    strcpy(command3, beforeDelim[1].c_str());
                    char* left2[] = {command3, NULL};
                    execvp(left2[0], left2);
                    perror("Error executing 2nd command on left of $");
                    exit(EXIT_FAILURE);                    
                }
                //Parent
                else
                {
                    pid_t pid3 = fork();
                    //Error
                    if (pid3 == -1)
                    perror("Error forking");
                    //Child # 3 (This is the first child to run - it will run "pwd")
                    else if (pid3 == 0)
                    {
                        //Redirect stdout to fds[WRITE_END] so that execvp automatically writes to the pipe
                        dup2(fds[WRITE_END], fileno(stdout));
                        //Close uneeded fds
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Execvp command
                      
                        n = beforeDelim[0].length();
                        char command2[n + 1];
                        strcpy(command2, beforeDelim[0].c_str());
                        char* left1[] = {command2, NULL};
                        execvp(left1[0], left1);
                        perror("Error executing 1st command on left of $");
                        exit(EXIT_FAILURE);
                    }
                    //Parent
                    else
                    {
                        int status;
                        close(fds[READ_END]);
                        close(fds[WRITE_END]);
                        //Wait for child 3
                        waitpid(pid3, &status, 0);
                    }
                    int status;
                    //Wait for child2
                    waitpid(pid2, &status, 0);
                }
                int status;
                //Wait for child1
                waitpid(pid, &status, 0);
            }
    }

}
//If there is no dollar sign exceute with system
    else{
      n = vect1[0].length();
      char command[n + 1];
      strcpy(command, vect1[0].c_str());
      valid = system(command);
      if(valid != 0){ printf("Invalid Input, error occured\n");}
}
    return 0;   
}
