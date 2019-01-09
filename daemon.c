/* daemon.c - implementation of daemon(3) */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

/* Based on Stevens, page 418 */
int
daemon(int nochdir, int noclose)
{
	int in, out, err;
	pid_t pid;

	if ((pid = fork()) < 0)
		return -1;
	else if (pid != 0)
		exit(0);
	setsid();
	if (nochdir == 0)
		chdir("/");
	umask(0);
	if (noclose == 0) {
		in = open("/dev/null", O_RDONLY);
		out = open("/dev/null", O_APPEND);
		err = open("/dev/null", O_APPEND);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		dup2(err, STDERR_FILENO);
	}
	return 0;
}
