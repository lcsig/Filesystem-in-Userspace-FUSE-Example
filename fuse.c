#ifndef FUSE_USE_VERSION
#define FUSE_USE_VERSION 30
#endif
#include <stdio.h>
#include "fuse_operations.h"
#include "alert_text.h"


/**
 * Many operations are available:
 *
 *  .init .destroy .getattr .fgetattr .access .readlink .opendir .readdir .releasedir .mknod .mkdir .setcrtime
 *	.symlink .unlink .rmdir .rename .link .chmod .chown .truncate .ftruncate .utimens .create .open .chflags
 *	.read .read_buf .write .write_buf .statfs .flush .release .fsync .fallocate .setxattr .getxattr .setattr_x
 *	.listxattr .removexattr .lock .flock .setvolname .exchange .getxtimes .setbkuptime .setchgtime .fsetattr_x
 */

static struct fuse_operations operations = {
        .getattr	= fun_getattr,
        .readdir	= fun_readdir,
        .read		= fun_read,
        .write		= fun_write,
        .open		= fun_open,
        .release	= fun_release,
        .flush		= fun_flush,
        .truncate	= fun_truncate
};


int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &operations, NULL);
}
