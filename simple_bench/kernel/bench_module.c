#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include "lockbench.h"

static int threads = 4;
module_param(threads, int, 0660);

static int tests = 1;
module_param(tests, int, 0660);

static char *ltype = "mutex";
module_param(ltype, charp, 0660);

typedef struct file_offset_info{
    char *name;
    unsigned long offset;
    unsigned long size;
}file_offset_info;

static file_offset_info info[100];

void set_info(const char* name, unsigned long offset, unsigned long size, int i){
    file_offset_info tmp;
    int k;

    info[i].name = name;
    info[i].offset = offset;
    info[i].size = size;

    for(k = 0; k<i; ++k){
        if(info[k].offset>info[i].offset){
            tmp = info[i];
            info[i] = info[k];
            info[k] = tmp;
        }
    }
}

static int mod_init(void)
{
    pr_info("Installing...");

    // if (strcmp(ltype, "mutex") == 0) {
    //     bench_multiple(LOCKTYPE_MUTEX, threads, tests);
    // } else if (strcmp(ltype, "spinlock") == 0) {
    //     bench_multiple(LOCKTYPE_SPINLOCK, threads, tests);
    // } else {
    //     pr_info("Not supported lock type: %s\n", ltype);
    // }
    
    int total = 0;
    int i;  
    struct file f;
    pr_info("file struct size: %ld\n", sizeof(struct file));
    set_info("f_lock", __builtin_offsetof(struct file, f_lock), sizeof(f.f_lock),total++);
    set_info("f_pos_lock", __builtin_offsetof(struct file, f_pos_lock), sizeof(f.f_pos_lock),total++);
    set_info("f_count", __builtin_offsetof(struct file, f_count), sizeof(f.f_count),total++);
    set_info("f_write_hint", __builtin_offsetof(struct file, f_write_hint), sizeof(f.f_write_hint),total++);
    set_info("f_u", __builtin_offsetof(struct file, f_u), sizeof(f.f_u),total++);
    set_info("f_path", __builtin_offsetof(struct file, f_path), sizeof(f.f_path),total++);
    set_info("f_inode", __builtin_offsetof(struct file, f_inode), sizeof(f.f_inode),total++);
    set_info("f_op", __builtin_offsetof(struct file, f_op), sizeof(f.f_op),total++);
    set_info("f_flags", __builtin_offsetof(struct file, f_flags), sizeof(f.f_flags),total++);
    set_info("f_mode", __builtin_offsetof(struct file, f_mode), sizeof(f.f_mode),total++);
    set_info("f_pos", __builtin_offsetof(struct file, f_pos), sizeof(f.f_pos),total++);
    set_info("f_owner", __builtin_offsetof(struct file, f_owner), sizeof(f.f_owner),total++);
    set_info("f_cred", __builtin_offsetof(struct file, f_cred), sizeof(f.f_cred),total++);
    set_info("f_ra", __builtin_offsetof(struct file, f_ra), sizeof(f.f_ra),total++);
    set_info("f_version", __builtin_offsetof(struct file, f_version), sizeof(f.f_version),total++);
    set_info("f_security", __builtin_offsetof(struct file, f_security), sizeof(f.f_security),total++);
    set_info("private_data", __builtin_offsetof(struct file, private_data), sizeof(f.private_data),total++);
    set_info("f_ep_links", __builtin_offsetof(struct file, f_ep_links), sizeof(f.f_ep_links),total++);
    set_info("f_tfile_llink", __builtin_offsetof(struct file, f_tfile_llink), sizeof(f.f_tfile_llink),total++);
    set_info("f_mapping", __builtin_offsetof(struct file, f_mapping), sizeof(f.f_mapping),total++);
    set_info("f_wb_err", __builtin_offsetof(struct file, f_wb_err), sizeof(f.f_wb_err),total++);
    set_info("f_sb_err", __builtin_offsetof(struct file, f_sb_err), sizeof(f.f_sb_err),total++);

    for(i=0; i<total; ++i){
        pr_info("%s offset: %ld, size: %ld\n", info[i].name, info[i].offset, info[i].size);
    }
    pr_info("Done\n");

    return 0;
}

static void mod_exit(void)
{
    pr_info("Uninstalling...\n");
}

MODULE_DESCRIPTION("kernel lock performance");
MODULE_AUTHOR("YW");
MODULE_LICENSE("GPL");

module_init(mod_init);
module_exit(mod_exit);
