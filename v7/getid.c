#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myheader.h"

int getid(FILE *fp) {
    //initialize id to 99
    unsigned int id = 999;
    //send the file pointer to the end
    //move back however many spaces the taskid int contains
    fseek(fp, -6, SEEK_END);
    //read this unsigned int into id
    //if not set id to 999 so adding 1 will equal 1000
    if (fscanf(fp, "%u", &id) != EOF) {
        id = id;
    } else {
        id = 999;
    }
    //file pointer passed into getid is closed here
    fclose(fp);
    fp = NULL;
    //return the id of the last element of the file
    return id;
}
