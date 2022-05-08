#include "alert_text.h"

char *pathOfBashrc = NULL;
char *userName = NULL;

char *getUsername() {
    if (userName != NULL)
        return userName;

    struct passwd *pw;
    uid_t uid;

    uid = geteuid();
    pw = getpwuid(uid);

    return (userName = pw->pw_name);
}

char* getPathOfBashrcFile() {
    if (pathOfBashrc != NULL)
        return pathOfBashrc;

    pathOfBashrc = malloc(PATH_MAX);
    memset(pathOfBashrc, 0, PATH_MAX);

    strcat(pathOfBashrc, "/home/");
    strcat(pathOfBashrc, getUsername());
    strcat(pathOfBashrc, "/.bashrc");

    return pathOfBashrc;
}

char* getAlertText() {
    char    *line            = malloc(500);
    FILE    *stream         = fopen(getPathOfBashrcFile(), "r");
    size_t  len             = 0;
    ssize_t nread           = 0;
    int     isLineFound     = 0;

    if (!stream)
        return NULL;
    while ((nread = getline(&line, &len, stream)) != -1) {
        if (strncmp("cowsay", line, strlen("cowsay")) == 0) {
            isLineFound = 1;
            break;
        }
    }
    fclose(stream);

    if (isLineFound == 0) {
        return NULL;
    } else {
        int cowCommandLength = strlen("cowsay -e \"o0\" ");
        char *x = malloc(nread - cowCommandLength + 1);
        memcpy(x, line + cowCommandLength, nread - cowCommandLength + 1);
        free(line);
        return x;
    }
}

int getLengthOfAlertText() {
    char *j = getAlertText();
    if (j == NULL)
        return 0;

    int c = strlen(j);
    free(j);

    return c;
}

int getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    int fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return fileSize;
}

void setTheAlertText(const char *newText, size_t size) {
    char    *cowSayCMD      = "cowsay -e \"o0\" ";
    FILE    *file       = fopen(getPathOfBashrcFile(), "r");
    if (file == NULL)
        return;


    int     bashrc_size     = getFileSize(file);
    int     commandLen      = strlen(cowSayCMD) + strlen(newText) + 3;
    char    *cowSayFullCmd  = malloc(commandLen);
    char    *buff           = malloc(bashrc_size + commandLen + 1);
    char    *line           = malloc(bashrc_size);
    size_t  len             = 0;
    ssize_t nread           = 0;


    memset(cowSayFullCmd, 0x00, commandLen);
    memset(buff, 0x00, bashrc_size + commandLen + 1);
    memset(line, 0x00, bashrc_size);
    strcat(cowSayFullCmd, cowSayCMD);
    strcat(cowSayFullCmd, newText);
    strcat(cowSayFullCmd, "\n");


    while ((nread = getline(&line, &len, file)) != -1) {
        if (strncmp("cowsay", line, 6) != 0)
            strcat(buff, line);
    }
    strcat(buff, cowSayFullCmd);


    fclose(file);
    file = fopen(getPathOfBashrcFile(), "w");
    fprintf(file, "%s", buff);
    fclose(file);


    free(line);
    free(buff);
    free(cowSayFullCmd);
}