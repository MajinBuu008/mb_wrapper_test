#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/mm.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "wrapper_misc.h"
#define PROC_ENTRY_NAME "dump_all_tasks"

struct task_struct *mb_find_lock_task_mm(struct task_struct *p);

#define PAGES_TO_KB(__pages) ((__pages) << ( PAGE_SHIFT - 10 ))


static int dump_tasks_show(struct seq_file *m, void *v)
{
    struct task_struct *p = NULL;
    struct task_struct *task = NULL;
    
    seq_printf(m, "name               pid      tgid   uid   total_vm  rss     pgtables_bytes\n");
    mb_rcu_read_lock();
    for_each_process(p)
    {
        for_each_thread(p, task)
        {
            task_lock(task);
            if (likely(task->mm))
            {
                seq_printf(m,
                    "%-15s "
                    "[%7d] %5d %5d "
                    " %8lu"
                    " %8lu"
                    " %8ld \n",
                    task->comm,
                    task->pid, task->tgid, mb_get_task_uid(task),
                    PAGES_TO_KB(task->mm->total_vm),
                    PAGES_TO_KB(get_mm_rss(task->mm)), 
                    PAGES_TO_KB(mm_pgtables_bytes(task->mm)));
            }
            task_unlock(task);
        }
    }
    mb_rcu_read_unlock();
    return 0;
}

static int dump_tasks_open(struct inode *inode, struct file *file)
{
    return single_open(file, dump_tasks_show, NULL);
}

/* File operations for the /proc file (read-only) */
static const struct proc_ops dump_tasks_proc_ops =
{
    .proc_open    = dump_tasks_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

static int __init mb_dump_task_init(void)
{
    if (!proc_create(PROC_ENTRY_NAME, 0444, NULL, &dump_tasks_proc_ops))
    {
        pr_err("Failed to create /proc/%s\n", PROC_ENTRY_NAME);
        return -ENOMEM;
    }
    pr_info("Proprietary module loaded, /proc/%s created\n", PROC_ENTRY_NAME);
    return 0;
}

static void __exit mb_dump_task_exit(void)
{
    remove_proc_entry(PROC_ENTRY_NAME, NULL);
    pr_info("Proprietary module unloaded, /proc/%s removed\n", PROC_ENTRY_NAME);
}

module_init(mb_dump_task_init);
module_exit(mb_dump_task_exit);


MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("MajinBuu");
MODULE_DESCRIPTION("copy dumptasks from kernel");