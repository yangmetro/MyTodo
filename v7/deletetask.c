#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myheader.h"

int deletetask(int *filesize, unsigned int taskid, taskitem_t *leaditem) {
    //first create a linked list by calling listtask 
    listtask(filesize, leaditem);

    //create file pointer
    FILE *fp = 0;
    fp = fopen("mytasks.dat", "w");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        exit(1);
    }
    //count will the the position where the taskitem_t with the 
    //same taskid is
    int count = 0;
    
    //allocate space for three helper taskitem_t
    //current and previous are used for traversing
    //and temp is to store the memory location of the first list
    taskitem_t *current = (taskitem_t *)malloc(sizeof(taskitem_t));
    taskitem_t *previous = (taskitem_t *) malloc(sizeof(taskitem_t));
    taskitem_t *temp = (taskitem_t *) malloc(sizeof(taskitem_t));
    temp = leaditem;
    current = leaditem;

    //increment count until a taskid is found
    while (leaditem->next != NULL) {
        if (leaditem->taskid == taskid) {
            break;
        } else {
            count++;
        }
        leaditem = leaditem->next;
    }
    //if count is equals the amount of items in the file
    //it means it cannot find any taskitem_t with the same id
    //therefore program is terminated
    //write the existing linked list back into the file
    if (count == *filesize) {
        printf("Specified task does not exist.\n");
        leaditem = temp;
        //write the new linked list onto the file
        while (leaditem->next != NULL) {
            fprintf(fp, "%d\n%s\n%u\n",
            leaditem->taskprio, leaditem->taskdesc, leaditem->taskid);
            leaditem = leaditem->next;
        }
        fclose(fp);
        fp = NULL;
        exit(1);
    }
    leaditem = temp;
    //traverse the linked list until reaching the position
    for (int i = 0; i < count; i++) {
        previous = current;
        current = current->next;
    }
    //at the position, skip over current's memory location
    previous->next = current->next;
    free(current);

    leaditem = temp;
    //write the new linked list onto the file
    while (leaditem->next != NULL) {
        fprintf(fp, "%d\n%s\n%u\n",
                leaditem->taskprio, leaditem->taskdesc, leaditem->taskid);
        leaditem = leaditem->next;
    }
    //files are close
    fclose(fp);
    fp = NULL;
    return 0;
}
