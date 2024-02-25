#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_STRUCTS 10

struct mystruct {
    int pid;
    uint size;
    char name[16];
};

int main(void) {

    struct mystruct struct_array[NUM_STRUCTS];
    struct mystruct *p;

    int return_val = ps( NUM_STRUCTS*sizeof(struct mystruct*), &struct_array);
    p = &struct_array[0];
    printf(1, "PID \tSIZE \tNAME \n");

    while(p != &struct_array[NUM_STRUCTS]){
        if (p -> pid == 0){
            p++;
            continue;
        }
        printf(1,"%d  \t%d \t%s \n",p->pid,p->size,p->name);
        p++;
    }

    printf(1, "Program %d \n", return_val);
    exit();
}
