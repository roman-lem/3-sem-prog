#include <stdio.h>

int main(int argc, char *argv[], char *envp[]){

	int i;
	for (i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	i = 0;
	while (envp[i] != NULL) {
		printf("%s\n", envp[i]);
		i++;
	}

	return 0;
}