#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myheader.h"

int addtask(int *filesize, int taskprio, char *task) {
    //open file to read mytasks.dat
    FILE *fp = 0;
    //initialize id here
    int id = 0;

    //attempts to open file here
    fp = fopen("mytasks.dat", "r");
    if (fp == NULL) {
        printf("could not open file\n");
        exit(1);
    }
    //count the amount of items existing in mytasks.dat
    //if there's 10 already, return error
    //file is closed inside countitem()
    *filesize = countitem(fp);
    if (*filesize >= 10) {
        printf("Task could not be added: too many tasks\n");
        fclose(fp);
        fp = NULL;
        exit(1);
    } 

    //open mytasks.dat for reading again
    //this time to get the last id in the list
    fp = fopen("mytasks.dat", "r");
    if (fp == NULL) {
        printf("could not open file\n");
        exit(1);
    }
    //calls getid() to get the last taskid on the file
    //file is closed at getid
    id = getid(fp);

    //open mytasks.dat for append
    fp = fopen("mytasks.dat", "a");
    if (fp == NULL) {
        printf("Could not open file\n");
        exit(1);
    }
    //create a temp taskitem_t to copy the info into it
    //append temp to the file
    taskitem_t *temp = (taskitem_t *) malloc(sizeof(taskitem_t));
    temp->taskprio = taskprio;
    //memory allocated for description here
    temp->taskdesc = malloc(strlen(task)+1);
    strcpy(temp->taskdesc, task);
    temp->taskid = 1 + id;
    
    //fprint on mytasks.dat
    fprintf(fp, "%d\n%s\n%u\n", taskprio, task, temp->taskid);

    //appending file is closed
    fclose(fp);
    fp = NULL;
    
    return 1;
}
