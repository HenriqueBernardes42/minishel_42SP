#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	while (1)
	{
		usleep(1000000);
		kill(atoi(argv[1]), SIGQUIT);
	}
}