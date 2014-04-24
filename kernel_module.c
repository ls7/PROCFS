#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>       




#define PROCFS_MAX_SIZE         1024
#define PROCFS_NAME             "my_proc_file"

#define DEBUG(msg) printk(KERN_ALERT "my_proc: %s\n", msg)


MODULE_LICENSE("GPL");

static struct proc_dir_entry* rw_file;



//The buffer used to store characters for this module
 
static char procfs_buffer[PROCFS_MAX_SIZE];


//The size of the buffer

static unsigned long procfs_buffer_size = 0;




//This function is called when the /proc file is written

int procfile_write(struct file *file, const char *input, unsigned long input_len,
                   void *data)
{
    DEBUG("in procfs_write");
       printk("%s\n", input);
       /* get buffer size */
        if ((procfs_buffer_size + input_len) > PROCFS_MAX_SIZE ) {
                input_len = PROCFS_MAX_SIZE - procfs_buffer_size;
        }
        
        /* write data to the buffer */
        if ( copy_from_user(&procfs_buffer[procfs_buffer_size], input, input_len) ) {
                return -EFAULT;
        }

	procfs_buffer_size = procfs_buffer_size + input_len;
        return input_len;
}



static int 
 rw_show(struct seq_file *m, void *v)
 {
    DEBUG("in rw_show");
    if(procfs_buffer_size > 0){
         DEBUG("in rw_show procfsbuffersize>0");
     seq_printf(m, "%s",
         procfs_buffer);
}
     procfs_buffer_size = 0;
 int i = 0;
 while(procfs_buffer[i] != '\0'){
      procfs_buffer[i] = '\0';
      i++;
 }     return 0;
 }

 static int
 rw_open(struct inode *inode, struct file *file)
 {
	DEBUG("in rw_open");     
	return single_open(file, rw_show, NULL);
 }


//Proc File operations structure

 static const struct file_operations rw_fops = {
     .owner	= THIS_MODULE,
     .open	= rw_open,
     .read	= seq_read,
     .llseek	= seq_lseek,
     .release	= single_release,
     .write     = procfile_write,
 };


//Linux kernel module init and exit methods


static int __init init_procfs(void)
{

	DEBUG("In init");

	rw_file = proc_create(PROCFS_NAME, 0666, NULL, &rw_fops);
	if (!rw_file) {
	DEBUG("proc create failed");
         return -ENOMEM;
     }
	

	return 0;
}

static void __exit exit_procfs(void)
{
	DEBUG("In Exit");
	remove_proc_entry(PROCFS_NAME, NULL);
}

module_init(init_procfs);
module_exit(exit_procfs);
