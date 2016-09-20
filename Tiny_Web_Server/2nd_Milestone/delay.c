#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "csapp.h"

int main(void)
{

  char *buf;
    char arg1[MAXLINE], content[MAXLINE];
    int n1=0;

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
	strcpy(arg1, buf);
	n1 = atoi(arg1);
    }

//  if (argc < 2)
//    {
//      printf("USAGE: %s loop-iterations\n", argv[0]);
//      return 1;
//    }

//  int delay = atoi(argv[1]);

  int delay= n1;

  struct timeval start, end;
  time_t start_time, cur_time;

  gettimeofday(&start, NULL);
  
  time(&start_time);
  do
  {
	time(&cur_time);
  }
  while((cur_time - start_time) < delay);


  gettimeofday(&end, NULL);

  printf("%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));

 /* Make the response body */
    sprintf(content, "Welcome to delay.com\r\n ");
    sprintf(content, "%sDelayed for %d\r\n<p>",content, delay);
    sprintf(content, "%sThanks for visiting!\r\n", content);
  
    /* Generate the HTTP response */
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}
