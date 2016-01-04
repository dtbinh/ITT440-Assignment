#include<stdio.h>
#include<signal.h>
#include<unistd.h>

signal(SIGHUP,catcher);
signal(SIGINT, catcher);

void catcher(int sig)
{

  printf ("Caught signal %d\n", sig);
  fflush(stdout);
  switch (sig)
        {
        case SIGINT:

          signal(SIGINT, catcher);
          printf("Control-C not Allowed\n");
          fflush(stdout);
          break;

        case SIGHUP:

          signal(SIGHUP,catcher); /* dont die on sighup */
          printf("SIGHUP Ignored\n");
          fflush(stdout);
          break;


          case SIGTERM:

          signal(SIGTERM, catcher);
          printf("exiting sigterm");
          exit(1);
          fflush(stdout);
          break;

        case SIGKILL:
          printf("sigkilla");
          fflush(stdout);
          signal(SIGKILL, catcher);
          printf("sigkilla");
          exit(1);
          fflush(stdout);
          break;
  }
