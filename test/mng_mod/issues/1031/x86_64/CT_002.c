#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "./test_chk.h"

#define TEST_NAME "CT_002"

int handled_cnt = 0;

void test_handler(int sig)
{
	handled_cnt++;
}

int main(int argc, char** argv)
{
	int rc = 0;
	int pid = 0;
	int status;
	int tmp_flag = 0;
	struct sigaction sa;

	printf("*** %s start *******************************\n", TEST_NAME);

	pid = fork();
	CHKANDJUMP(pid == -1, "fork");

	if (pid == 0) { /* child */
		sa.sa_handler = test_handler;
		sa.sa_flags = 0;

		rc = sigaction(SIGUSR1, &sa, NULL);
		OKNG(rc != 0, "sigaction (no SA_RESETHAND)");

		printf("   send 1st SIGUSR1\n");
		kill(getpid(), SIGUSR1);
		OKNG(handled_cnt != 1, "invoked test_handler");
		printf("   send 2nd SIGUSR1\n");
		kill(getpid(), SIGUSR1);
		OKNG(handled_cnt != 2, "invoked test_handler again");
		_exit(123);
	} else { /* parent */
		rc = waitpid(pid, &status, 0);
		CHKANDJUMP(rc == -1, "waitpid");

		if (!WIFSIGNALED(status) && 
		    WIFEXITED(status)) {
			if (WEXITSTATUS(status) == 123) {
				tmp_flag = 1;
			}
		}
		OKNG(tmp_flag != 1, "child exited normaly");
	}

	printf("*** %s PASSED\n\n", TEST_NAME);

	return 0;

fn_fail:
	printf("*** %s FAILED\n\n", TEST_NAME);

	return -1;
}
