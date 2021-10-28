#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
pid_t pid, ppid;

pid_t chpid = fork();

switch (chpid){

	case -1:
		printf("Error\n");
		break;
	case 0:
		execle("/bin/ls", "/bin/ls", NULL, envp);
		a = a-1;
		break;
	default:
}

sleep(1);
pid = getpid();
ppid = getppid();

printf("My pid = %d, my ppid = %d, result = %d\n", (int)pid, (int)ppid, a);
return 0;
}
