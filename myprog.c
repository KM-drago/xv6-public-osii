#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
printf (1, " start of kernel = %p \n", getkernalstartaddr()) ;
printf (1, "end of kernel = %p \n", getkernalendaddr());
printf (1, "addr of kernel variable = %p \n", getkernalvariaddr()) ;
printf (1, "addr of fork sys call = %p \n", getsystemcalladdr());
exit ();
}
