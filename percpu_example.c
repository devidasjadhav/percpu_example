#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_AUTHOR("Devidas Jadhav");
MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Call back PerCPU module");

char temp_buf[4096] = "test123";
struct percpu_struct {
char mybuf[10];
int len;
};
//static DEFINE_PER_CPU(struct percpu_struct *, percpu_var);
struct percpu_struct * __percpu percpu_var;

int my_int_set(const char *val, const struct kernel_param *kp){
	struct percpu_struct * local_var;
	local_var = get_cpu_ptr(percpu_var);
	strncpy(local_var->mybuf,val, strlen(val));
	local_var->len = strlen(local_var->mybuf);
	printk(KERN_INFO "PerCPU variavble set Succaesufully!!!\n[%d]: %s\n",local_var->len,local_var->mybuf);
	put_cpu_ptr(percpu_var);
	return 0;
}
int my_int_get(char *buffer, const struct kernel_param *kp){
	int ret;
	struct percpu_struct * local_var;
	local_var = get_cpu_ptr(percpu_var);
	strncpy(buffer, local_var->mybuf, local_var->len);
	ret = local_var->len;
	printk(KERN_INFO "PerCPU variavble get Succaesufully!!!\n[%d]: %s\n",local_var->len,local_var->mybuf);
	put_cpu_ptr(percpu_var);
	return ret;
}
void my_int_free(void *arg){
	printk(KERN_INFO "Freeing cookie buff\n");
}
struct kernel_param_ops custom_ops =  {
	.set = my_int_set,
	.get = my_int_get,
	.free = my_int_free
};


//module_param(num,int,0600);
module_param_cb(mybuf , &custom_ops , &temp_buf , 0600);



int __init callback_init(void){
	printk(KERN_INFO "Hello World!!!\n");
	percpu_var = alloc_percpu(struct percpu_struct );
	if(!percpu_var)
		return -ENOMEM;
	printk(KERN_INFO "PerCPU variavble allocated Succaesufully!!!\n");
	return 0;
}


void __exit bye_init(void){
	printk(KERN_INFO "Bye World!!!\n");
	free_percpu(percpu_var);
	printk(KERN_INFO "PerCPU variavble freeed Succaesufully!!!\n");
}

module_init(callback_init);

module_exit(bye_init);
