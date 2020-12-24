#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

void print_process(void){
    struct task_struct *task_list;
    struct list_head *sub;

    for_each_process(task_list) {
        printk("== id[%d] state[%ld] %s\n", task_list->pid, task_list->state, task_list->comm);
        
	list_for_each(sub, &task_list->children){
	    struct task_struct *task;

	    task = list_entry(sub, struct task_struct, sibling);
	    printk("==== id[%d] state[%ld] %s\n", task_list->pid, task_list->state, task_list->comm);

	}

	printk("\n");	
	
    }

}

/* Essa função é chamada quando o módulo é carregado. */
int hello_init(void){

    printk(KERN_INFO "----->Hello!<-----\n");
    print_process();
    return 0;

}

/* Essa função é chamada quando o módulo é removido. */
void hello_exit(void){

    printk(KERN_INFO "----->Tchau!<-----\n");

}

/* Macros para o registro dos pontos de entrada e saída do módulo. */
module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("Sistemas Operecionais");
MODULE_AUTHOR("Belem");
