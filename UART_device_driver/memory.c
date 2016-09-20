/* A simple character device, "memory", that allows a character to be read */
/* or written from memory */
#define UART_DR(baseaddr) ((unsigned int *)(baseaddr))
#define UART_FR(baseaddr) ((((unsigned int *)(baseaddr))+6))
/* Necessary includes for device drivers */
#include <linux/init.h>
// #include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h> /* printk() */
#include <linux/slab.h> /* kmalloc() */
#include <linux/fs.h> /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/proc_fs.h>
#include <linux/fcntl.h> /* O_ACCMODE */
#include <asm/system.h> /* cli(), *_flags */
#include <asm/uaccess.h> /* copy_from/to_user */
#include <asm/io.h>


MODULE_LICENSE("Dual BSD/GPL");

void *addr = NULL; 
enum {
 UART_FR_RXFE = 0x10,
 UART_FR_TXFF = 0x20,
 UART0_ADD = 0x101f1000,
};

/* Declaration of memory.c functions */
int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void memory_exit(void);
int memory_init(void);

/* Structure that declares the usual file */
/* access functions */
struct file_operations memory_fops = {
  read:  memory_read,
  write:  memory_write,
  open:  memory_open,
  release:  memory_release
};

/* Declaration of the init and exit functions */
module_init(memory_init);
module_exit(memory_exit);

/* Global variables of the driver */
/* Major number */
int memory_major = 60;
/* Buffer to store data */
char *memory_buffer;

/* Memory device initialization function */

int memory_init(void)
{
  int result;
  /* Getting Virtual Addr */
  addr = ioremap(UART0_ADD, 512);
  /* Registering device */
  result = register_chrdev(memory_major, "memory", &memory_fops);
  if (result < 0) {
    printk(KERN_ERR "mem_dev: cannot obtain major number %d\n", memory_major);
    return result;
  }

 /* Allocating memory for the buffer */
  memory_buffer = kmalloc(1, GFP_KERNEL); 
  if (!memory_buffer) { 
    result = -ENOMEM;
    goto fail; 
  } 
  memset(memory_buffer, 0, 1);

  printk(KERN_ERR "Inserting memory module\n"); 
  return 0;

  fail: 
    memory_exit(); 
    return result;
}

/* Memory device exit function */

void memory_exit(void) 
{
  /* Freeing the major number */
  unregister_chrdev(memory_major, "memory");

  /* Freeing buffer memory */
  if (memory_buffer) {
    kfree(memory_buffer);
  }

  printk(KERN_ERR "Removing memory module\n");

}

/* Memory device open function */
int memory_open(struct inode *inode, struct file *filp)
{

  /* Success */
  return 0;
}

/* Memory device release function */
int memory_release(struct inode *inode, struct file *filp)
{
 
  /* Success */
  return 0;
}

/* Memory device read function */
ssize_t memory_read(struct file *filp, char *buf, 
                    size_t count, loff_t *f_pos)
{
 ssize_t retval = 0; 
 int todo;
 char val = 0;
 	if(count == 0)
  		return 0;
 	while(ioread32(UART_FR(addr)) & UART_FR_RXFE);
		val = ioread8(UART_DR(addr));
		if (copy_to_user(buf,&val,1)) {
			retval = -EFAULT;
			goto out;
 		}
		buf++;
 	for(todo = 1; todo < count; todo++) 
	{
  		if(ioread32(UART_FR(addr)) & UART_FR_RXFE) {
   			break;
 		}
 		val = ioread8(UART_DR(addr));
		if (copy_to_user(buf,&val,1)) {
			retval = -EFAULT;
			goto out;
 		}
		buf++;
	}
	retval = todo;

out:
 return retval;
}

/* Memory device write function */
ssize_t memory_write( struct file *filp, char *buf,
                      size_t count, loff_t *f_pos) 
{

  ssize_t retval = 0;

  char val = 0;
  int todo;

 for (todo = 0; todo < count; todo++)
 {
	if (copy_from_user(&val,buf,1)) {
		retval = -EFAULT;
		goto out;
        }
	buf++;
  	iowrite8(val, UART_DR(addr));
	
 }

 retval = todo;

 out:
  return retval;
}



