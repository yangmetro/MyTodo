#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "myheader.h"

int main() {
    pid_t k;
    int status;
    //inital buffer with 50 spaces
    char input[50];
    //inital taskdesc with 30 spaces
    char task[30];
    //action can be either add, list, or delete
    char action[6];
    //count keeps track of how many spaces there are in an inputted command
    int count = 0;
    //the following three is the offical variables
    //to be written into file
    int taskprio = 0;
    char *taskdesc;
    unsigned int taskid;
    //file pointer is created here
    FILE *fp = 0;
    //allocate memory to store the amount of items in mytasks.dat
    int *filesize = malloc(sizeof(int));
    //create a list head
    taskitem_t *listhead = (taskitem_t *) malloc(sizeof(taskitem_t));


    while(1) {
        int truthstate = 0;
        count = 0;
        //takes in input from stdin and gets rid of the trailing newline
        fgets(input, 50, stdin);
        int len = strlen(input);
        input[len - 1] = '\0';

        //open a file just for names
        fp = fopen("inputname.txt", "w");

        if (fp == NULL) {
            printf("Unable to open file.\n");
            exit(1);
        }

        //outputs the name onto the file
        //and closes the file
        fputs(input, fp);

        fclose(fp);
        fp = NULL;

        //open mytasks.dat file to read
        fp = fopen("mytasks.dat", "r");
        //filesize first counts how many items there are in the file already
        *filesize = countitem(fp);
        fclose(fp);
        fp = NULL;

        //opens inputname.txt again
        //but this time to read
        fp = fopen("inputname.txt", "r");
        if (fp == NULL) {
            printf("Unable to open file.\n");
            exit(1);
        }
        //counts how many spaces there are in input
        for (int i = 0; i < strlen(input); i++) {
            if (input[i] == 32) {
                count++;
            }
        }
        fclose(fp);
        fp = NULL;

        //open inputname one last time for reading
        fp = fopen("inputname.txt", "r");

        if (fp == NULL) {
            printf("Unable to open file.\n");
            exit(1);
        }
        //automatically assumes any commands
        //without anyspaces is wrong
        if (count == 0) {
            truthstate = 1;
        }

        //if there is only 1 space, that means the command must be mytodo list
        if (count == 1) {
            //action follows "mytodo " and is read into action
            fscanf(fp, "mytodo %s", action);
            //compares to see if it is "list"
            //if it is, continue 
            //if not, nothing happens and truthstate is flipped to 1
            if (strncmp(action, LIST, 4) == 0) {
                listtask(filesize, listhead);
                printlist(listhead);
            } else {
                truthstate = 1;
            }
        }
        //if there is only 2 spaces
        //that means the command must be mytodo delete ----
        if (count == 2) {
            fscanf(fp, "mytodo %s", action);
            if (strncmp(action, DELETE, 6) == 0) {
                fscanf(fp, " %u", &taskid);
                deletetask(filesize, taskid, listhead);
            } else {
                truthstate = 1;
            }
        }
        //if there are 3 spaces
        //that menas the command must be mytodo add ---- __________
        if (count >= 3) {
            fscanf(fp, "mytodo %s", action);
            //either "add" or "a" works 
            int x = strncmp(action, ADD, 3);
            int y = strncmp(action, A, 1);
            if (x == 0 || y == 0) {
                fscanf(fp, " %d %30[^\n]", &taskprio, task);
                addtask(filesize, taskprio, task);
            } else {
                truthstate = 1;
            }
        }
        fclose(fp);
        fp = NULL;

        k = fork();
        if (k == 0) {
            //if truthstate is 1, it means user entered the command incorrectly
            if (truthstate == 1) {
                fprintf(stderr, "Incorrect command line format\n");
                exit(1);
            }
        }
        else if ( k > 0) {
            waitpid(k, &status, 0);
        }
        else {
            fprintf(stderr, "Fork failed\n");
        }
    }
}
