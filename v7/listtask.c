#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myheader.h"

int listtask(int *filesize, taskitem_t *listhead) {
    //file pointer to be used in this function
    FILE *fp = 0;
    //create the needed stuff to take inputs from the file
    int priority = 0;
    char str[30];
    int id = 0;
    //open the file
    fp = fopen("mytasks.dat", "r");
    if (fp == NULL) {
        printf("Could not open file.\n");
        exit(1);
    }
    //set the first listhead to the taskitem_t nextitem
    taskitem_t *nextitem = listhead;

    listhead->next = NULL;
    //loop through however many elements there are in the file
    for (int i = 0; i < *filesize; i++) {
        //read the file and store the content into appropriate variables
        fscanf(fp, "%d\n%30[^\n]\n%d", &priority, str, &id);
        nextitem->taskprio = priority;
        nextitem->taskdesc = malloc(strlen(str) + 1);
        strcpy(nextitem->taskdesc, str);
        nextitem->taskid = id;
        //allocate memory for the next item in the list
        nextitem->next = (taskitem_t *)malloc(sizeof(taskitem_t));
        //traverses to the next item on the list
        nextitem = nextitem->next;
    }
    //makes the last item of the list null
    nextitem->next = NULL;

    //closes file opened in the beginning
    fclose(fp);
    fp = NULL;
    return 1;
}
