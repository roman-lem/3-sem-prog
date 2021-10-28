#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
   char    *array;
   int     shmid;
   char    pathname[] = "t2a.c";
   key_t   key;

   if((key = ftok(pathname,0)) < 0){
     printf("Can\'t generate key\n");
     exit(-1);
   }

   FILE* srcFile =0;
   if((srcFile = fopen("t2a.c", "r")) < 0){
      printf("Can\'t open file\n");
      exit(-1);
   }

   if((shmid = shmget(key, 10000*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0){

      if(errno != EEXIST){
         printf("Can\'t create shared memory\n");
         exit(-1);
      } 
   }
   //printf("%d\n", shmid);

   if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
      printf("Can't attach shared memory\n");
      exit(-1);
   }

   int i;
   char getC;
   for(i = 0; getC != EOF; i++){
      getC = fgetc(srcFile);
      array[i] = getC;
   }

   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   if(fclose(srcFile) < 0){
      printf("Can't close file\n");
      exit(-1);
   }

   return 0;
}
