#define ADD "add"
#define DELETE "delete"
#define LIST "list"
#define A "a"

typedef struct taskitem{
    int taskprio;
    char *taskdesc;
    unsigned int taskid;
    struct taskitem *next;
} taskitem_t;

int main(void);
int addtask(int *, int, char *);
int deletetask(int *, unsigned int, taskitem_t *);
int listtask(int *, taskitem_t *);
int countitem(FILE *);
int getid(FILE *);
int printlist(taskitem_t *);
