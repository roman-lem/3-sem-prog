#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2], cid;
   char  resstring[28];

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }

   cid = fork();

   if(cid < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (cid > 0) {

     /* Parent process */
    int fileD;
    char string[] = "Hello, World! Hello, Roman!";

     if((fileD = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0){
       printf("Can\'t open file\n");
       exit(-1);
     }

     if(write(fileD, string, 28) != 28){
       printf("Can\'t write all string\n");
       exit(-1);
     }

     if(close(fileD) < 0){
       printf("Can\'t close file\n");
     }

      close(fd[0]);

      if(write(fd[1], "myfile", 7) != 7){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      close(fd[1]);
      printf("Parent exit\n");

   } else {

      /* Child process */
      char filename[7];

      close(fd[1]);

      if(read(fd[0], filename, 7) < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

      int fileD;

     if((fileD = open(filename, O_RDONLY)) < 0){
       printf("Can\'t open file\n");
       exit(-1);
     }

     char string[28];
     if(read(fileD, string, 28) != 28){
      printf("Can\'t read all string\n");
      exit(-1);
     }

     if(close(fileD) < 0){
       printf("Can\'t close file\n");
     }

      printf("Child exit, resstring:%s\n", string);

      close(fd[0]);
   }

   return 0;
}
