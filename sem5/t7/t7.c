#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd1[2], fd2[2], result;

   size_t size;
   char  resstring[14];

   if(pipe(fd1) < 0){
     printf("Can\'t open 1 pipe\n");
     exit(-1);
   }
   if(pipe(fd2) < 0){
     printf("Can\'t open 2 pipe\n");
     exit(-1);
   }

   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */

      close(fd1[0]);
      close(fd2[1]);

      if(write(fd1[1], "Hello, world!", 14) != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      if(read(fd2[0], resstring, 13) < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

      close(fd1[1]);
      close(fd2[0]);
      printf("Parent exit, resstring:%s\n", resstring);

   } else {

      /* Child process */
      close(fd1[1]);
      close(fd2[0]);

      if(write(fd2[1], "Hello, MIPT!", 13) != 13){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }

      if(read(fd1[0], resstring, 14) < 0){
         printf("Can\'t read string from pipe\n");
         exit(-1);
      }

      printf("Child exit, resstring:%s\n", resstring);

      close(fd1[0]);
      close(fd2[1]);
   }

   return 0;
}
