#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#ifndef FUSE_USE_VERSION
#define FUSE_USE_VERSION 30
#endif
#include <fuse.h>


const char *getFileName();

const char* getFileNamePath();

int fun_getattr(const char *path, struct stat *stateBuff);

int fun_readdir(const char *path, void *buff, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);

int fun_read(const char *path, char *buff, size_t size, off_t offset, struct fuse_file_info *fi);

int fun_write(const char *path, const char *buff, size_t size, off_t offset, struct fuse_file_info *fi);

int fun_release(const char *path, struct fuse_file_info *fi);

int fun_flush(const char *path, struct fuse_file_info *fi);

int fun_open(const char *path, struct fuse_file_info *fi);

int fun_truncate(const char *path, off_t size);
