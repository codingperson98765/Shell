# Shell
Written in C++;

A linux based shell that parses user's input command line and starts up necessary processes needed to carry out these command(s). Properly handles creation/termination, inter-process communication, and basic file management. 
Additional features compared to standard linux terminal:
1. Can excecute up two commands piped($) as input to up to two commands, for example **myshell$ cmd1 cmd2 $ cmd3 cmd4**, if cmd1 is ls, cmd2 is pwd, cmd 3 is wc and cmd4 is cat, then ls and pwd will both be given as input to word count and to cat. This feature cannot be done with the regular linux terminal as it cannot handle piping of multiple inputs to multiple outputs in a single line of input from the user. 


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
