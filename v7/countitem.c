#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countitem(FILE *fp) {
    //create a buffer of 30
    char str[30];
    //count is to be returned at the end of the file
    int count = 0;
    //reads every line and increments count everytime the program does such
    while (fgets(str, 30, fp) != NULL) {
        count++;
    }
    //divide count by 3 because there are 3 items in each list on the file
    count = count / 3;
    
    //closes file pointer passed by addtask()
    fclose(fp);
    fp = NULL;
    //return the amount of items found in the file
    return count;
}
