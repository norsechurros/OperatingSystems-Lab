/*
 #include <stdio.h>
 #include <sys/types.h>
 #include <unistd.h>
 int main(void){
 printf("Hello \n");
 fork();
 printf("bye\n");
 return 0;
 }

*/

/*


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define BUFLEN 10

int main(void) {
    int i;
    char buffer[BUFLEN + 1];
    pid_t pid1;

    pid1 = fork();
    if (pid1 == 0) {
        strncpy(buffer, "CHILD\n", BUFLEN); /* in the child process */
  /*      buffer[BUFLEN] = '\0';
    } else if (pid1 > 0) { // for parent process
        strncpy(buffer, "PARENT\n", BUFLEN); /* in the parent process */
    /*    buffer[BUFLEN] = '\0';
    } else if (pid1 == -1) {
        printf("ERROR:\n");
        switch (errno) {
            case EAGAIN:
                printf("Cannot fork process: System Process Limit Reached\n");
                break; // You forgot to add break statements here
            case ENOMEM:
                printf("Cannot fork process: Out of memory\n");
                break;
        }
        return 1;
    }
    for (i = 0; i < 5; ++i) { /* both processes do this */
      /*  sleep(1); /* 5 times each */
      /*  write(1, buffer, strlen(buffer));
    }
    return 0;
}

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int status;
    pid_t fork_return;
    
    fork_return = fork();
    if (fork_return == 0) { /* child process */
        printf("\n I'm the child!");
        exit(0);
    } else { /* parent process */
        wait(&status);
        printf("\n I'm the parent!");
        if (WIFEXITED(status))
            printf("\n Child returned: %d\n", WEXITSTATUS(status));
    }

    return 0;
}

