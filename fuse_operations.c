#include "fuse_operations.h"
#include "alert_text.h"


const char *fileNamePath = "/alertMe";
const char *fileName = "alertMe";

const char *getFileName() {
    return fileName;
}

const char* getFileNamePath() {
    return fileNamePath;
}

void log_call(const char* funName) {
    printf("[+] %s is called\n", funName);
}

/**
 * Will be called when the system asks for attributes of a file that was stored in the mount point
 */
int fun_getattr(const char *path, struct stat *stateBuff) {
    log_call("fun_getattr");

    stateBuff->st_uid = getuid();
    stateBuff->st_gid = getgid();
    stateBuff->st_atime = stateBuff->st_mtime = stateBuff->st_ctime = time(NULL);

    /** Info For The mount point */
    if (strcmp(path, "/") == 0) {
        stateBuff->st_mode  = S_IFDIR | 0755;
        stateBuff->st_nlink = 2;
    }

    /** Info for a specific file */
    else if (strcmp(path, getFileNamePath()) == 0)  {
        stateBuff->st_mode  = S_IFREG | 0644;
        stateBuff->st_nlink = 1;
        stateBuff->st_size  = getLengthOfAlertText();
    }

    /** Return Error No Entry */
    else {
        return -ENOENT;
    }

    return 0;
}


/**
 * Will be called when the system asks for a list of files that were stored in the mount point
 */
int fun_readdir(const char *path, void *buff, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    log_call("fun_readdir");

    filler(buff, ".", NULL, 0);
    filler(buff, "..", NULL, 0);

    // Get the files/directories which exist in the mount point
    if (strcmp(path, "/") == 0) {
        struct stat* stateBuff = malloc(sizeof(struct stat));

        memset(stateBuff, 0x00, sizeof(struct stat));
        stateBuff->st_uid = getuid();
        stateBuff->st_gid = getgid();
        stateBuff->st_atime = stateBuff->st_mtime = stateBuff->st_ctime = time(NULL);
        stateBuff->st_mode  = S_IFREG | 0644;
        stateBuff->st_nlink = 1;
        stateBuff->st_size  = getLengthOfAlertText();

        filler(buff, getFileName(), stateBuff, 0);
    }
    else
        return -ENOENT;

    return 0;
}


/**
 * Will be executed when the system is trying to read one of the files that were stored in the mount point
 */
int fun_read(const char *path, char *buff, size_t size, off_t offset, struct fuse_file_info *fi) {
    log_call("fun_read");

    char *selectedText = NULL;
    int len = getLengthOfAlertText();

    if (offset >= len || len == 0)
        return 0;
    else if (strcmp(path, getFileNamePath()) == 0)
        selectedText = getAlertText();
    else
        return -ENOENT;

    if (size > len - offset)
        size = len - offset;

    memcpy(buff, selectedText + offset, size);
    return size;
}

/**
 * Will be called when the system is trying to write on one of the files that were stored in the mount point
 */
int fun_write(const char *path, const char *buff, size_t size, off_t offset, struct fuse_file_info *fi) {
    log_call("fun_write");

    if (strcmp(path, getFileNamePath()) == 0)
        setTheAlertText(buff, size);
    else
        return -ENOENT;

    return size;
}

/**
 * Some file is released
 */
int fun_release(const char *path, struct fuse_file_info *fi) {
    log_call("fun_release");
    return 0;
}

/**
 * Some file is flushed
 */
int fun_flush(const char *path, struct fuse_file_info *fi) {
    log_call("fun_flush");
    return 0;
}

/**
 * Some file should be opened
 */
int fun_open(const char *path, struct fuse_file_info *fi) {
    log_call("fun_open");

    if (strcmp(path, getFileNamePath()) == 0)
        printf("File has been opened successfully\n");
    else
        return -ENOENT;

    return 0;
}

/**
* Must be exist for write function to succeed
*/
int fun_truncate(const char *path, off_t size)
{
    log_call("fun_truncate");
    return 0;
}