#include "stdio.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <linux/limits.h>


char* getUsername();

char* getPathOfBashrcFile();

char* getAlertText();

int getLengthOfAlertText();

int getFileSize(FILE *file);

void setTheAlertText(const char *x, size_t size);