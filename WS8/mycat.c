#include "apue.h"

#define	BUFFSIZE	4096

int
main(void)
{
	int		n;
	char	buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");
	
	char fileName[50] = "stdErr";
	FILE *fileOut = fopen(fileName, "a");
	fprintf(fileOut, "%d\n", n);
	fclose(fileOut);
	
	fprintf(stderr, "%s\n", n);

	if (n < 0)
		err_sys("read error");

	exit(0);
}
