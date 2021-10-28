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

   if((shmid = shmget(key, 10000*sizeof(char), 0)) < 0){
      printf("Can\'t find shared memory\n");
      exit(-1);
   }

   if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
      printf("Can't attach shared memory\n");
      exit(-1);
   }

   int i;
   char Symb;
   for(i = 0; 1; i++){
      Symb = array[i];
      if(Symb == EOF)
         break;
      if(Symb == '\0')
         printf("\n");
      else
         printf("%c", Symb);
   }

   if(shmdt(array) < 0){
      printf("Can't detach shared memory\n");
      exit(-1);
   }

   if(shmctl(shmid, IPC_RMID, 0) < 0){
      printf("Can't delete shared memory\n");
      exit(-1);
   }

   return 0;
}
