#include <linux/module.h>
 #include <linux/init.h>
 #include <linux/kernel.h>
 #include <linux/fs.h>		 // for basic filesystem
 #include <linux/proc_fs.h>	// for the proc filesystem
 #include <linux/seq_file.h>	// for sequence files
#include <asm/uaccess.h>      // for copy_from_user 

#define PROCFS_MAX_SIZE         1024
#define PROCFS_NAME             "osproject"

 static struct proc_dir_entry* rw_file;

/**
 * The buffer used to store characters for this module
  */
static char procfs_buffer[PROCFS_MAX_SIZE];

/**
 * The size of the buffer 
 */
static unsigned long procfs_buffer_size = 0;

/**
 * This function is called when the /proc file is written
 */
int procfile_write(struct file *file, const char *input, unsigned long input_len,
                   void *data)
{
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
    if(procfs_buffer_size > 0){
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
     return single_open(file, rw_show, NULL);
 }

/**
 *  File operations structure
*/
 static const struct file_operations rw_fops = {
     .owner	= THIS_MODULE,
     .open	= rw_open,
     .read	= seq_read,
     .llseek	= seq_lseek,
     .release	= single_release,
     .write     = procfile_write,
 };

/**
 * Proc creation 
*/
 static int __init 
 rw_init(void)
 {
     rw_file = proc_create(PROCFS_NAME, 0666, NULL, &rw_fops);

     if (!rw_file) {
         return -ENOMEM;
     }
     return 0;
 }

/**
 * Proc entry removal
*/
 static void __exit
 rw_exit(void)
 {
     remove_proc_entry(PROCFS_NAME, NULL);
 }

 module_init(rw_init);
 module_exit(rw_exit);
