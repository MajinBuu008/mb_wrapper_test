
#include <linux/init.h>
#include <linux/module.h>

#include <linux/rcupdate.h>

#include "wrapper_misc.h"

void mb_call_rcu(struct rcu_head *head, rcu_callback_t func)
{
    call_rcu(head, func);
}
EXPORT_SYMBOL(mb_call_rcu);


void mb_rcu_read_lock(void)
{
    rcu_read_lock();
}
EXPORT_SYMBOL(mb_rcu_read_lock);


void mb_rcu_read_unlock(void)
{
    rcu_read_unlock();
}
EXPORT_SYMBOL(mb_rcu_read_unlock);


int mb_get_task_uid(struct task_struct *task)
{
    if ( NULL != task )
    {
        return from_kuid(&init_user_ns, task_uid(task));
    }
    return (-1); /* can't find kuid */
}
EXPORT_SYMBOL(mb_get_task_uid);