# homework3

To add additional features to the search program -  a search program in C program using system calls for files and 
directories. 

# description

**Additional features: **

1. -e "<unix-command with arguments>" 
For each file that matches the search criteria the UNIX command specified with 
arguments must be executed.  
2. -E "<unix-command with arguments>" [Graduate Students Only] 
The list of files that matches the search criteria must be provided as an argument to the 
UNIX command specified. 
  
  **
Features of search program:**
1. The program  takes the directory name from where to start the file traversal as a 
command-line argument and print the file hierarchy starting with the directory that is 
provided by the command-line argument. 
2. If the program is executed without any arguments, the program should print the file 
hierarchy starting with the current directory where the program is executed. If there are no 
directories in the current directory only files are listed one per line. 
3. If there are other directories in the current directory then the directory name is first 
displayed on a separate line and then the files in that directory are listed one-per-line with 
one-tab indentation. 
4. If a file is a symbolic link then the program should display the symbolic link name and in 
parentheses the file name the link points to. 
5. The program should also support three command-line options: 
1. -S 
This should list all files in the file hierarchy and print the file size next to the filename in 
parenthesis.  
2. -s <file size in bytes> 
This should list all files in the file hierarchy with file size greater than or equal to the 
value specified. 
3. -f <string pattern> 
This should list all files in the file hierarchy whose file name or directory name contains 
the substring specified in the string pattern option. 
6. The program should support not only each of these options separately but also any 
combination of these options. For example: -S, -s 1024, -f jpg, -S -s 1024, -S -f jpg, -s 
1024 -f jpg, -S -s 1024 -f jpg, -S -f jpg -s 1024. 
7. If both -s and -f options are specified then the program should list only those files that 
match both criteria. The order of the options should not matter. 
8. -t d will display the directories
  -t f will display all the files
  
9. In addition to this, 
  
# Getting started
These instructions will give you a copy of the project up and running on your local machine for development and testing purposes.
# prerequisites
Requirements for the software and other tools to build, test and push
1. gcc - GNU Compiler Collection
2. Text editor

# installing
A step by step series of examples that tell you how to get a development environment running
1. open the text editor
2. create a c programming file
3. save the file with .c extension.

# Running the tests

functionality of the program:

It uses switch method to take input from command line arguments
  Depending on the input, it goes to a function name printFileHierarchy
  and prints the required ouput based on the command line arguments.
  
  if flag -e or -E is used followed by a unix command, this unix command will be executed.
  
  if -s 1022 is given, it displays the files with size>0 1022
  if -f 'abc' is given, it displays the files with substring 'abc'
  if -S is given it displays the files and its size.
  
  if -e or -E is used along with other flags(-s -f), the program will filter out the files and then applies unix command on only these).
  
 It uses the method printFileHierarchy2 to take the flags and print the directories or file names accordingly.
 An array is declared such that all the unix commands and file paths are stored.
 This array is given as a parameter to execvp() function. Execvp takes two arguments, one is the unix command and the other is an array containg the arguments.
  
 This program also uses the system calls fork() and wait().
  A child process is created by fork() and if a process is created then execvp() is executed, and it waits till the child process is done executing.
  

In the int main(), these methods are called at the right time. 


In general a c program is executed in this way:
1. To compile the file, type the command 'gcc filename.c'
2. To run the file, type './a.out'

To test our program, follow the below steps

1. gcc homework3.c
2. ./a.out 
    
output: 
```To send a file in input stream, follow the below steps:
 ./a.out -e "ls -l"                 
  **output:**
-rw-r--r--@ 1 rnvsrivastava  staff   6148 Mar 13 08:56 ./.DS_Store
-rw-r--r--@ 1 rnvsrivastava  staff   6151 Mar 13 10:00 ./HW2.c
-rw-r--r--@ 1 rnvsrivastava  staff     59 Mar 13 11:38 ./Makefile
-rwxr-xr-x  1 rnvsrivastava  staff  34386 Mar 13 11:49 ./a.out
-rw-r--r--  1 rnvsrivastava  staff      0 Mar 10 16:24 ./d_name
-rw-r--r--  1 rnvsrivastava  staff  12197 Mar 13 11:33 ./homework3.c
-rw-r--r--  1 rnvsrivastava  staff  52224 Mar 12 18:48 ./jpg.tar
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample 2.c
-rw-r--r--  1 rnvsrivastava  staff   1288 Mar 13 09:43 ./sample.c
-rw-r--r--@ 1 rnvsrivastava  staff  17408 Mar 13 08:55 ./sample.tar
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample/sample 2.c
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample/sample.c
  
  
  
 input: ./a.out -e "ls -l" -S
  
 ** 
 output: ** 
  �� (.DS_Store)size: 6148
�� (sample.tar)size: 17408
�� (jpg.tar)size: 52224
�� (Makefile)size: 59
�� (homework3.c)size: 12197
�� (sample.c)size: 1288
�� (sample 2.c)size: 1341
�� (a.out)size: 34386
�� (d_name)size: 0
� �� (homework3.c)size: 11315
� �� (sample.c)size: 1341
� �� (sample 2.c)size: 1341
�� (HW2.c)size: 6151
-rw-r--r--@ 1 rnvsrivastava  staff   6148 Mar 13 08:56 ./.DS_Store
-rw-r--r--@ 1 rnvsrivastava  staff   6151 Mar 13 10:00 ./HW2.c
-rw-r--r--@ 1 rnvsrivastava  staff     59 Mar 13 11:38 ./Makefile
-rwxr-xr-x  1 rnvsrivastava  staff  34386 Mar 13 11:49 ./a.out
-rw-r--r--  1 rnvsrivastava  staff      0 Mar 10 16:24 ./d_name
-rw-r--r--  1 rnvsrivastava  staff  12197 Mar 13 11:33 ./homework3.c
-rw-r--r--  1 rnvsrivastava  staff  52224 Mar 12 18:48 ./jpg.tar
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample 2.c
-rw-r--r--  1 rnvsrivastava  staff   1288 Mar 13 09:43 ./sample.c
-rw-r--r--@ 1 rnvsrivastava  staff  17408 Mar 13 08:55 ./sample.tar
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample/sample 2.c
-rw-r--r--  1 rnvsrivastava  staff   1341 Mar 12 16:25 ./sample/sample.c
  
  
```
# Author
Sri Vastava RNV

# Acknoledgement

I thank my TA's and Dr. Mahmut Unan for helping me learn everyday. 


