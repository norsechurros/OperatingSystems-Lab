#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

pid_t pid;

pid = fork();

if (pid < 0){printf("error"); return 1;}

else if( pid ==0)
{printf ("child proces: %d %d" , getpid(), getppid());}

else {printf("parent process: %d %d", getpid(), getppid());}

return 0;
}
