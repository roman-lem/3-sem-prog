#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void* thread1(void *dummy){

   pthread_t mythid;
   
   mythid = pthread_self();

   a = a+1;

   printf("Thread %lu, Calculation result: a = %d\n", mythid, a);

   return NULL;
}
void* thread2(void *dummy){

   pthread_t mythid;
   
   mythid = pthread_self();

   a = a+10;

   printf("Thread %lu, Calculation result: a = %d\n", mythid, a);

   return NULL;
}

int main()
{
   pthread_t thid1, thid2, mythid; 
   int       result;

   result = pthread_create( &thid1, (pthread_attr_t *)0, thread1, 0);
   
   if(result != 0){
      printf ("Error on thread 1 create, return value = %d\n", result);
      exit(-1);
   }  
   printf("Thread 1 created, thid = %lu\n", thid1);

   result = pthread_create( &thid2, (pthread_attr_t *)0, thread2, 0);
   
   if(result != 0){
      printf ("Error on thread 2 create, return value = %d\n", result);
      exit(-1);
   }   
   
   printf("Thread 2 created, thid = %lu\n", thid2);

   pthread_join(thid1, (void **)0);
   pthread_join(thid2, (void **)0);

   mythid = pthread_self();
   
   a = a+100;
   
   printf("Thread %lu, Calculation result a = %d\n", mythid, a);

   return 0;
}
