#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myheader.h"

int printlist(taskitem_t *listhead) {
    //largest serves to take in the largest priority in the file
    int largest = 0;
    //a temporary taskitem_t is made up
    //in order to store the memory location of listhead
    taskitem_t *temp = (taskitem_t *)malloc(sizeof(taskitem_t));
    temp = listhead;
    //traveres the list and find the largest priority
    //largest priority is set to the variable "largest"
    while (listhead->next != NULL && listhead->taskdesc != NULL) {
        if (listhead->taskprio > largest) {
            largest = listhead->taskprio;
        }
        listhead = listhead->next;
    }
    //listhead is restored
    listhead = temp;
    //if the current taskitem_t's priority is not the largest
    //it is printed first
    while(listhead->next != NULL) {
        if (listhead->taskprio != largest) {
            printf("%d, %s, %d\n",
                listhead->taskprio, listhead->taskdesc, listhead->taskid);
        }
        listhead = listhead->next;
    } 
    //listhead is restored here again for another traversal
    listhead = temp;
    //if the current taskitem_t's priority is the largest
    //print it, since the smaller ones are printed already
    while (listhead->next != NULL) {
        if (listhead->taskprio == largest) {
            printf("%d, %s, %d\n",
                listhead->taskprio, listhead->taskdesc, listhead->taskid);
        }
        listhead = listhead->next;
    }
    return 1;
}
