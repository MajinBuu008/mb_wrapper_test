#ifndef __WRAPPER_MISC_H__
#define __WRAPPER_MISC_H__


void mb_call_rcu(struct rcu_head *head, rcu_callback_t func);
void mb_rcu_read_lock(void);
void mb_rcu_read_unlock(void);

int mb_get_task_uid(struct task_struct *task);

#endif //__WRAPPER_MISC_H__