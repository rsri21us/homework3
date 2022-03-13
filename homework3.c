#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <errno.h>
// used my previous code that implments all the flags with function pointer and combination of flags

/* 
Name: Sri Vastava Rangaraju Naga Venkata
BlazerId: rsri21us
Project #: Homework3
To compile: gcc homework3.c 
To run: /<name of executable> <commands and arguments> <directory>
 Ex: ./executable -f txt -S -s 100 -t f ./projects/
*/ 

char *filetype(unsigned char type) {  // This code returns the file type (a String)
    char *str;
    switch(type) {
    case DT_BLK: str = "block device"; break;
    case DT_CHR: str = "character device"; break;
    case DT_DIR: str = "directory"; break;
    case DT_FIFO: str = "named pipe (FIFO)"; break;
    case DT_LNK: str = "symbolic link"; break;
    case DT_REG: str = "regular file"; break;
    case DT_SOCK: str = "UNIX domain socket"; break;
    case DT_UNKNOWN: str = "unknown file type"; break;
    default: str = "UNKNOWN";
    }
    return str;
  }
typedef void MYFUNC();

int getFileSize(char *filename){
    
    struct stat sb;

    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    return(sb.st_size);
}    

void getUnixCommand(int argc, char *argv[]){  // use of function pointer to return the linux command given after flag -e or -E
    char *command = malloc(100);
    for(int i=1;i<argc;i++)
    {
        if(strcmp(argv[i], "-e")==0)
        strcpy(command,argv[i+1]);
        else if(strcmp(argv[i], "-E")==0)
        strcpy(command,argv[i+1]);
    }
    printf("command is%s ", command);
}

void printFileHierarchy2(char *path, int root, int flagS, int flags, int filesize, int flagf, char *substring, int flagt, int flagd, int flagr, int flage, char **paths, int index, MYFUNC *f)
{
    int count=1;
    
    struct dirent *dirent;  
    DIR *parentDir;
    parentDir = opendir (path); 
    char *dir_path;

    if (parentDir == NULL) { 
      printf("Cannot open the Directory");
      return;  
    } 
    
   
    while((dirent = readdir(parentDir)) != NULL)
    { 
      if(strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
      { 
          for (int i=0; i<root; i++) 
            {
                if (i%2 == 0 || i == 0)
                    printf("%c", 179);
                else
                    printf(" ");
            }
            
        char *tmp = malloc(sizeof(path)+sizeof("/")+sizeof(dirent->d_name)); 
        strcpy(tmp, path);
        strcat(tmp,"/");
        strcat(tmp, dirent->d_name);
       
  
        if( strcmp(filetype(dirent->d_type), "directory") == 0)             
        {       
            if(flagr!=1 && flage!=1){
                
            if(flagS ==1 && flags==1 && flagf==1) 
            {
                if(getFileSize(tmp)>=filesize && strstr(dirent->d_name, substring))
                printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,getFileSize(tmp));
            }   
            else if(flagS == 1 && flags==1){ 
                if(getFileSize(tmp)>=filesize)
                printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp)); 
            }       
            else if(flagS == 1 && flagf==1) 
            {      
                 if(strstr(dirent->d_name, substring))
                  printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,getFileSize(tmp));   
            }  
            else if(flagf==1 && flags==1)
            {
                if(strstr(dirent->d_name, substring) && getFileSize(tmp)>=filesize)
                  printf ("%c%c (%s)\n", 195, 196, dirent->d_name);   
            }
            else if(flags == 1){
                if(getFileSize(tmp)>=filesize)
                printf ("%c%c (%s)\n", 195, 196, dirent->d_name);   
            }
            else if(flagf == 1){
                if(strstr(dirent->d_name, substring)) 
                printf ("%c%c (%s)\n", 195, 196, dirent->d_name);   
            }
            else if(flagS==1)
            {
                printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp));
            }   
            else 
            printf ("%c%c (%s)\n", 195, 196, dirent->d_name);
            }              
              dir_path = malloc(sizeof(path)+sizeof("/")+sizeof(dirent->d_name)); 
              strcpy(dir_path, path); 
              strcat(dir_path,"/");
              strcat(dir_path, dirent->d_name);
            
              printFileHierarchy2(dir_path, root+2, flagS, flags, filesize, flagf, substring,flagt, flagd, flagr, flage, paths, index, getUnixCommand);
        }  
        else
        {    
            if(flagd!=1){

            if(flagS ==1 && flags==1 && flagf==1)
            {
                
                if(getFileSize(tmp)>=filesize && strstr(dirent->d_name, substring)){
                    if(flage==1 ){  
                        printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp));
                       paths[index] = tmp;   
                       index++;
                    }
                    else 
                    printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp));
                }
            }

            else if(flagS == 1 && flags==1){
                if(getFileSize(tmp)>=filesize){
                    if(flage==1 ){
                        printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp)); 
                       paths[index] = tmp;   
                       index++;
                    }
                    else 
                    printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp)); 
                }
                
            }
            else if(flagS == 1 && flagf==1)
            {
                if(strstr(dirent->d_name, substring)){
                    if(flage==1 ){
                         printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name, getFileSize(tmp)); 
                       paths[index] = tmp;   
                       index++;
                    }
                    printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name, getFileSize(tmp));   
                }
            }  
            else if(flagf==1 && flags==1)
            {
                if(strstr(dirent->d_name, substring) && getFileSize(tmp)>=filesize){
                    if(flage==1 ){
                       paths[index] = tmp;   
                       index++;
                    }
                    else 
                    printf ("%c%c (%s)\n", 195, 196, dirent->d_name); 
                }
                    
            }
            else if(flags == 1){
                if(getFileSize(tmp)>=filesize){
                    if(flage==1 ){
                       paths[index] = tmp;   
                       index++;
                    }
                    else 
                    printf ("%c%c (%s)\n", 195, 196, dirent->d_name);  
                }
                 
            }
            else if(flagf == 1){
                
                if(strstr(dirent->d_name, substring)) {
                    if(flage==1 ){
                       paths[index] = tmp;   
                       index++;
                    }
                    else 
                    printf ("%c%c (%s)\n", 195, 196, dirent->d_name);  
                }
                  
            } 
            else if(flagS==1)
            {
                printf ("%c%c (%s)size: %d\n", 195, 196, dirent->d_name,  getFileSize(tmp));
                if(flage==1){
                       paths[index] = tmp;   
                       index++;
                    }  
                    
            }   
            else {
                if(flage==1){
                       paths[index] = tmp;   
                       index++;
                    }
                else
                 printf ("%c%c (%s)\n", 195, 196, dirent->d_name); 
            }
              
            } 
        }      
        count++;
      }
    }
}

int main(int argc, char *argv[])
{ 
    
    int flagS=0, flags=0, flagf=0, flagt=0, flagD=0, flagr=0, flage=0, flagE=0;
    
        int option;
        char **paths = malloc(1000);

        while(( option = getopt(argc, argv, "s:t:f:e:E:S")) != -1 )
        { 
            switch (option){ 
                case 'S':   
                    flagS =1;
                    break;
                case 's':
                    flags =1;
                    break;
                case 'f': 
                    flagf=1;
                    break;
                case 't':
                    flagt=1;
                    break;
                case 'e':
                    flage=1;
                    break;
                case 'E':
                    flagE=1;
                    break;
            }  
        }  

      
        
        for(int i=1;i<argc;i++){
            if(strcmp(argv[i], "-S")==0)
            {
                if(flagS == 0)
                 flagS++;
            }
            if(strcmp(argv[i], "-s")==0)
            {
                if(flags ==0)
                flags++;
            }  
            if(strcmp(argv[i], "-f")==0)
            {
                if(flagf ==0)
                flagf++;
            } 
        } 
        for(int i=0;i<argc;i++)
        {
            if(strcmp(argv[i], "-t")==0)
                flagt=1;
            else 
                flagt=0;
        }
         for(int i=0;i<argc;i++)
        {
            if(strcmp(argv[i], "-t")==0)
                flagt=1;
        }
        
    
        for(int i=0;i<argc;i++)
        {
            if(strcmp(argv[i], "-t")==0)
            {
                if(strcmp(argv[i+1], "f")==0){
                    flagr=1;
                    flagD=0;
                    break;
                }
                if(strcmp(argv[i+1], "d")==0){
                    flagr=0;
                    flagD=1;
                    break;
                }
            }
        }
         
        int filesize;
        char *fz = malloc(1000);
        char *substring = malloc(1000);
        char *command = malloc(1000);

        int i;
        for(i=0;i<argc-1; i++)
        {           
            if(strcmp(argv[i],"-s")==0){
            fz = argv[i+1];
            filesize = atoi(argv[i+1]); 
            }
            if(strcmp(argv[i],"-f")==0)   
            substring = argv[i+1];
        }
         int j;
        char *dirPath=malloc(10000);
        dirPath = ".";
        for(j=1;j<argc;j++){
            if(strcmp(argv[j], "-e")==0 || strcmp(argv[j], "-E")==0)
            {
                command = argv[j+1]; 
            }
        }

        for(j=1;j<argc;j++){
            if( strcmp(argv[j], "-S")!=0 && strcmp(argv[j], "-s")!=0 && strcmp(argv[j], fz)!=0 && strcmp(argv[j], "-f")!=0 && strcmp(argv[j], substring)!=0 && strcmp(argv[j], "-t")!=0 && strcmp(argv[j], "d")!=0 && strcmp(argv[j], "f")!=0 && strcmp(argv[j], "-e")!=0 && strcmp(argv[j], "-E")!=0 && strcmp(argv[j], command)!=0)
            {
                dirPath = argv[j];
            }
        }
        int index=0;   
        char s[2]=" ";
        char *tmp1= strdup(command);
        char *token = strtok(tmp1, s);   
        
        while( token != NULL ) 
        {
            paths[index] = token; 
            index++;  
            token = strtok(NULL, s);
        }
         
        if(flage == 0)
        printFileHierarchy2(dirPath, 0, flagS, flags, filesize, flagf, substring, flagt, flagD, flagr, flage, paths, index, getUnixCommand);    
        else if(flagE == 1)
        {
            flage=1;
        } 
        if(flage==0)
        flage++;
        
        if(flage == 1)
        {
            printFileHierarchy2(dirPath, 0, flagS, flags, filesize, flagf, substring, flagt, flagD, flagr, flage,paths, index, getUnixCommand);       
                int pid = fork();               // use of fork(), wait() and execvp()
                if(pid == 0){
                    execvp(paths[0],paths);
                }            
                else
                wait(NULL);
        } 
     return 0;
}