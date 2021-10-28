#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  int     fd[2], result;
  int   semid;
  char pathname[]="t2a.c";
  key_t key;

   size_t size;
   char  resstring[15];


   key = ftok(pathname, 0);
    
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }

   if(pipe(fd) < 0){
     printf("Can\'t open pipe\n");
     exit(-1);
   }
   long long N = 0, i = 0;

   scanf("%lld", &N);



   result = fork();

   if(result < 0) {
      printf("Can\'t fork child\n");
      exit(-1);
   } else if (result > 0) {

     /* Parent process */
    struct sembuf mybuf;
    mybuf.sem_num = 0;
    mybuf.sem_flg = 0;
    mybuf.sem_op  = 0;

      mybuf.sem_op  = 1;
      if(semop(semid, &mybuf, 1) < 0){
        printf("Can\'t add 1 to semaphore\n");
        exit(-1);
      }
      size = write(fd[1], "Hello, child!", 14);
      if(size != 14){
        printf("Can\'t write all string to pipe\n");
        exit(-1);
      }
      mybuf.sem_op  = 1;
      if(semop(semid, &mybuf, 1) < 0){
        printf("Can\'t add 1 to semaphore\n");
        exit(-1);
      }
      for(i = 0; i < N; i++){
        mybuf.sem_op  = -1;
        if(semop(semid, &mybuf, 1) < 0){
          printf("Can\'t wait for condition\n");
          exit(-1);
        } 
        printf("Sem op = %d\n", mybuf.sem_op);
        size = read(fd[0], resstring, 15);
        if(size < 0){
           printf("Can\'t read string from pipe\n");
           exit(-1);
        }
        printf("Parent proccess, i = %lld, resstring:%s\n", i, resstring);

        size = write(fd[1], "Hello, child!", 14);
        if(size != 14){
          printf("Can\'t write all string to pipe\n");
          exit(-1);
        }   

        mybuf.sem_op  = 2;
        if(semop(semid, &mybuf, 1) < 0){
          printf("Can\'t add 1 to semaphore\n");
          exit(-1);
        }   
        printf("Sem op = %d\n", mybuf.sem_op); 
      }

      close(fd[0]);
      close(fd[1]);
      printf("Parent exit\n");

   } else {

      /* Child process */
    struct sembuf mybuf;
    mybuf.sem_num = 0;
    mybuf.sem_flg = 0;
    mybuf.sem_op  = 0;

      for(i = 0; i < N; i++){
        mybuf.sem_op  = -2;
        if(semop(semid, &mybuf, 1) < 0){
          printf("Can\'t wait for condition\n");
          exit(-1);
        } 
        printf("Sem op = %d\n", mybuf.sem_op);
        size = read(fd[0], resstring, 14);
        if(size < 0){
           printf("Can\'t read string from pipe\n");
           exit(-1);
        }
        printf("Child proccess, i = %lld, resstring:%s\n", i, resstring);

        size = write(fd[1], "Hello, parent!", 15);
        if(size != 15){
          printf("Can\'t write all string to pipe\n");
          exit(-1);
        }    

        mybuf.sem_op  = 1;
        if(semop(semid, &mybuf, 1) < 0){
          printf("Can\'t add 1 to semaphore\n");
          exit(-1);
        }    
        printf("Sem op = %d\n", mybuf.sem_op);
      }

      close(fd[1]);
      close(fd[0]);
      printf("Child exit\n");
      mybuf.sem_op  = -2;
      if(semop(semid, &mybuf, 1) < 0){
        printf("Can\'t wait for condition\n");
        exit(-1);
      } 
      printf("Delete semaphore\n");
      semctl(semid, 0, IPC_RMID, 0);
   }

   return 0;
}
