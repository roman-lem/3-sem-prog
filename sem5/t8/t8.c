#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int     fd[2];
   ssize_t size;
   char  resstring[14];

   if(pipe2(fd, O_NONBLOCK) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }
   

   int pipeSize =0;
  while ((write(fd[1], "*", 1)) >= 0){
    pipeSize += 1;
  }
  printf("Size = %d\n", pipeSize);

   close(fd[0]);
   close(fd[1]);

   return 0;
}
