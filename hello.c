#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
	struct head_list *item_next;
	ktime_t time;
};

MODULE_AUTHOR("Hana Khalil <hanka100h@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static uint hw_count = 1;
module_param(hw_count, uint, 0444);
MODULE_PARM_DESC(hw_count, "This parameter is counter of hello world");

static int __init hello_init(void)
{
	uint i = 0;

	struct head_list *temp_var, *next_temp_var;

	pr_info("Input %d\n", hw_count);

	if (hw_count == 0) {
		pr_warn("You cannot enter 0");
	} else {
		if (hw_count >= 5 && hw_count <= 10) {
			pr_warn("Number should be less than 5");
		} else {
			if (hw_count > 10) {
				pr_err("The parameter is greater than 10");
				pr_info("");
				return -EINVAL;
			}
		}
	}

	head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);
	temp_var = head;

	for (i = 0; i < hw_count; i++) {
		temp_var->item_next =
			kmalloc(sizeof(struct head_list), GFP_KERNEL);
		temp_var->time = ktime_get();
		pr_info("Hello, world!\n");
		next_temp_var = temp_var;
		temp_var = temp_var->item_next;
	}

	if (hw_count != 0) {
		kfree(next_temp_var->item_next);
		next_temp_var->item_next = NULL;
	}

	pr_info("");
	return 0;
}

static void __exit hello_exit(void)
{
	struct head_list *var;

	while (head != NULL && hw_count != 0) {
		var = head;
		pr_info("Time: %lld", var->time);
		head = var->item_next;
		kfree(var);
	}

	pr_info("");
}

module_init(hello_init);
module_exit(hello_exit);
