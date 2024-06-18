/*youb nader
instagram: unnamed0._
program: progress bar*/

//this program might generate a warning in the usleep function but warinings can be ignored as long as the program works

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //for usleep() function

void progress_bar() {
    printf("[");
    for (int i = 0; i < 40; i++) {
        printf("#"); //character can be changed
        fflush(stdout); //immediately display the character
        usleep(100000); //sleep for 100000 microseconds (0.1 seconds) (this is the best option)
    }
    printf("]\nDone\n");
}
//----------------------------------------------------------------------------------------------------------
int main()
{
    progress_bar();
    return 0;
}