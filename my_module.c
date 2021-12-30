#include <linux/init.h>
#include <linux/module.h>
#include <linux/ktime.h>
#include<linux/slab.h>


MODULE_AUTHOR("Shchuryk Yevhenii");
MODULE_DESCRIPTION("Lab 5 module.");
MODULE_LICENSE("GPL");


uint message_count = 1;
module_param(message_count, uint, 0660);
MODULE_PARM_DESC(message_count, "Quantity of 'hello world' messages to output");


struct hello_data {
	struct list_head tlist;
	ktime_t time;
};

LIST_HEAD(head_node);


static int __init hello_init(void)
{
	int i;
	
	printk(KERN_INFO "Loading my_module...\n");

	if (message_count == 0) {
		printk(KERN_WARNING "Warning: message_count is zero\n");
	} else if (message_count >= 5 && message_count <= 10) {
		printk(KERN_WARNING "Warning: message_count is between 5 and 10\n");
    	} else if (message_count > 10) {
    		printk(KERN_ERR "message_count bigger than 10!\n");
    		return -EINVAL;
		/*BUG();*/
		
    	}
	
	
	for (i = 0; i < message_count; i++) {
		struct hello_data *new_node = NULL;
		
		new_node = kmalloc(sizeof(struct hello_data), GFP_KERNEL);
		/*
		if(i == 3){
			new_node = NULL;
		}
		*/
		
        if (new_node == NULL) {
            printk(KERN_ERR "0(zero) returned by kmalloc");
        }
		new_node->time = ktime_get();

		INIT_LIST_HEAD(&new_node->tlist);
		list_add_tail(&new_node->tlist, &head_node);

		printk(KERN_INFO "Hello, world!\n");
	}
	return 0;
}


static void __exit hello_exit(void)
{
	int count = 0;
	struct hello_data *c, *temp_node;

	list_for_each_entry_safe(c, temp_node, &head_node, tlist) {
		printk(KERN_INFO "Node %d ktime = %lld\n", count++,
				ktime_to_ns(c->time));
		list_del(&c->tlist);
		kfree(c);
	}
	printk(KERN_INFO "Module removed\n");
}


module_init(hello_init);
module_exit(hello_exit);
