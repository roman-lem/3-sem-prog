#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   int fd;

   if((fd = open("myfile", O_RDONLY)) < 0){
     printf("Can\'t open file\n");
     exit(-1);
   }

   char string[100];
   if(read(fd, string, 100) < 0){
    printf("Can\'t read all string\n");
    exit(-1);
   }

   printf("%s", string);

   if(close(fd) < 0){
     printf("Can\'t close file\n");
   }

   return 0;
}
