                                    
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
printf("parent process");

fork();
printf ("child process");

return 0;
}
