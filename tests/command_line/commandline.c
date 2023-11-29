
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (void) {
	FILE *pipeStdOutput = NULL;
	char *pipeOutput = (char *) malloc(2048 * sizeof(char));

	pipeStdOutput = popen("/bin/ls -la ~", "r");

	while (fgets(pipeOutput, sizeof(pipeOutput), pipeStdOutput) != NULL) {
		fprintf(stdout, "%s", pipeOutput);
	}

	pclose(pipeStdOutput);

	return 0;
}
