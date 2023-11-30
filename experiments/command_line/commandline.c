
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (void) {
	FILE *pipeStdOutput = NULL;
	char *pipeOutput = (char *) malloc(2048 * sizeof(char));

	pipeStdOutput = popen("/bin/echo ", "r");

	while (fgets(pipeOutput, sizeof(pipeOutput), pipeStdOutput) != NULL) {
		printf("%d\n", strlen(pipeOutput));
	}

	pclose(pipeStdOutput);

	return 0;
}
