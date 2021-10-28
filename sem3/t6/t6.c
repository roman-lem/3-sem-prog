#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
pid_t pid, ppid;
int a = 0;
pid_t chpid = fork();

if (chpid == -1){
	printf("Error\n");
}
else if (chpid == 0){
	execle("/bin/ls", "/bin/ls", NULL, envp);
	a = a-1;
}
else{
	a = a+1;
}

sleep(1);
pid = getpid();
ppid = getppid();

printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
return 0;
}