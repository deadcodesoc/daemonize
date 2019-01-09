/* daemonize.c - daemonize a program */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	int             nochdir = 0;
	int             noclose = 0;

	const char     *ProgName = argv[0];
	argv++;
	argc--;
	if (*argv && !strcmp(*argv, "-version")) {
		printf("%s version 0.0\n", ProgName);
		return 0;
	}
	if (*argv && !strcmp(*argv, "-help")) {
		printf("Usage: %s [-help|-version|-nochdir|-noclose] program ...\n",
		       ProgName);
		printf("Run program in daemon mode\n");
		return 0;
	}
	if (*argv && !strcmp(*argv, "-nochdir")) {
		nochdir = 1;
		argv++;
		argc--;
	}
	if (*argv && !strcmp(*argv, "-noclose")) {
		noclose = 1;
		argv++;
		argc--;
	}
	syslog(LOG_DEBUG, "argc = %d", argc);
	syslog(LOG_DEBUG, "argv[0] = %s", argv[0]);

	if (daemon(nochdir, noclose) < 0) {
		syslog(LOG_ERR, "Cannot daemonize");
		return 1;
	}
	if (argc > 0 && execv(argv[0], argv) < 0) {
		syslog(LOG_ERR, "Cannot execv: %s", argv[0]);
		return 1;
	}

	return 0;
}
