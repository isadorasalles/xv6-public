#include "types.h"
#include "stat.h"
#include "user.h"
 
int
main(void)
{
set_prio(1);
set_prio(2);
set_prio(0);
exit();
}
