# Shell
Written in C++;

A linux based shell that parses user's input command line and starts up necessary processes needed to carry out these command(s). Properly handles creation/termination, inter-process communication, and basic file management. 
Additional features compared to standard linux terminal:
1. Can excecute up two commands piped($) as input to up to two commands, for example **myshell$ cmd1 cmd2 $ cmd3 cmd4**

Sample set of test cases for shell:
(mysh% is shell prompt)

mysh% date
mysh% gcc prog1.c
mysh% date > file.txt
mysh% ls -l > file.lst
mysh% wc -l < file.txt
mysh% ls -l | sort -r
mysh% cmd1 $ cmd2 cmd3
mysh% cmd1 cmd2 $ cmd3
mysh% cmd1 cmd2 $ cmd3 cmd4
mysh% cat < poem | grep are | wc -l > numberof.are
