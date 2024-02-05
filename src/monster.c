#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 2000
#define MAX_COMMIT_MESSAGE_LENGTH 2000
#define MAX_LINE_LENGTH 2000
#define MAX_MESSAGE_LENGTH 1000
#define MAX_USERNAME_EMAIL_LENGTH 500
#define MAX_WORDS_COUNT_IN_A_COMMAND 10

int isDirectory(const char *path);
void nuller(char input[]);
bool config_flag();
bool init_flag();
int commitcounter();
int init(int argc, char *argv[]);
int config(int argc, char *argv[]);
int alias(int argc, char *argv[]);
int add(int argc, char *argv[]);
int add_file(char *path);
void add_file_or_folder(char *input);
int reset(int argc, char *argv[]);
void reset_file_or_directory(char input[]);
void reset_file(char *path);
char check_if_file_is_unstaged(char *addres);
char status_mode(char *path);
void status_file_or_directory(char input[]);
void status_file(char *path);
int status(int argc, char *argv[]);
int commit(int argc, char *argv[]);
int set(int argc, char *argv[]);
int removeshortcut(int argc, char *argv[]);
void show_log(int counter, int number);
int log_git(int argc, char *argv[]);
void show_some_log(int counter, char *argv[]);
void show_some_log_plus(int counter, char *word);
int branch(int argc, char *argv[]);
bool HEAD_flag();
int checkout(int argc, char *argv[]);

bool HEAD_flag()
{
    FILE *myid = fopen(".monster/myid", "r");
    char myidd[100];
    nuller(myidd);
    fgets(myidd, sizeof(myidd), myid);
    myidd[strlen(myidd)] = '\0';
    if (atoi(myidd) == commitcounter() - 1)
        return true;
    return false;
}

void nuller(char input[])
{
    for (int i = 0; i < strlen(input); i++)
    {
        input[i] = '\0';
    }
}

char check_if_file_is_unstaged(char *addres)
{
    char file_name[MAX_FILENAME_LENGTH];
    char line[MAX_LINE_LENGTH];
    int start = 0;
    for (int i = strlen(addres) - 1; i >= 0; i--)
    {
        if (addres[i] == '/')
        {
            start = i + 1;
            break;
        }
    }
    for (int i = start; i < strlen(addres); i++)
    {
        file_name[i - start] = addres[i];
    }
    file_name[strlen(addres) - start] = '\0';
    DIR *dir = opendir(".monster/unstaged/");
    DIR *dir2 = opendir(".monster/added/");
    struct dirent *entry;
    struct dirent *entry2;
    int flag = 0;
    int flag1 = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, file_name) == 0)
        {
            flag = 1;
            return 'U';
        }
    }
    while ((entry2 = readdir(dir2)) != NULL)
    {
        if (strcmp(entry2->d_name, file_name) == 0)
        {
            flag1 = 1;
            return 'S';
        }
    }
    return 'N';
}

int commitcounter()
{
    FILE *file = fopen(".monster/commitsinformation", "r");
    int counter_lines = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        counter_lines++;
    }
    counter_lines /= 8;
    return counter_lines + 1000;
}

int isDirectory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

bool config_flag()
{
    FILE *config_username = fopen(".monster/config_username", "r");
    FILE *config_email = fopen(".monster/config_email", "r");
    if (config_username == NULL)
        return false;
    if (config_email == NULL)
        return false;
    char temp[MAX_LINE_LENGTH];
    nuller(temp);
    if (fgets(temp, sizeof(temp), config_username) == NULL)
        return false;
    nuller(temp);
    if (fgets(temp, sizeof(temp), config_email) == NULL)
        return false;
    fclose(config_username);
    fclose(config_email);
    return true;
}

bool init_flag()
{
    struct dirent *entry;
    DIR *dir = opendir(".");
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".monster") == 0)
        {
            return true;
        }
    }
    closedir(dir);
    return false;
}

int init(int argc, char *argv[])
{
    DIR *dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error opening current directory\n");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return 1;
    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;
    do
    {
        DIR *dir = opendir(".");
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".monster") == 0)
            {
                exists = true;
            }
        }
        closedir(dir);
        getcwd(tmp_cwd, sizeof(tmp_cwd));
        if (strcmp(tmp_cwd, "/") != 0)
            chdir("..");
    } while (strcmp(tmp_cwd, "/") != 0);
    chdir(cwd);
    closedir(dir);
    if (!exists)
    {
        if (mkdir(".monster", 0755) != 0)
            return 1;
        printf("Repository created succesfully\n");
        if (mkdir(".monster/commits", 0755) != 0)
            return 1;
        if (mkdir(".monster/added", 0755) != 0)
            return 1;
        if (mkdir(".monster/alias", 0755) != 0)
            return 1;
        if (mkdir(".monster/branches", 0755) != 0)
            return 1;
        if (mkdir(".monster/unstaged", 0755) != 0)
            return 1;
        if (mkdir(".monster/shortcuts", 0755) != 0)
            return 1;
        mkdir("/home/mr_nakhjavani/Documents/alias_global", 0755);
        FILE *file = fopen(".monster/commitsinformation", "w");
        fclose(file);
        file = fopen(".monster/staged", "w");
        fclose(file);
        file = fopen(".monster/mybranch", "w");
        fprintf(file, "master");
        fclose(file);
        file = fopen(".monster/branches/master", "w");
        fclose(file);
        file = fopen(".monster/myid", "w");
        fprintf(file, "999");
        fclose(file);
        HEAD_flag();
        return 0;
    }
    else
    {
        HEAD_flag();
        printf("Monster repository has already initialized\n");
        return 1;
    }
}

int config(int argc, char *argv[])
{
    if (strcmp(argv[2], "-global") == 0)
    {
        if (strstr(argv[3], "alias.") != NULL)
        {
            return alias(argc, argv);
        }
        else
        {
            if (strcmp(argv[3], "user.name") == 0)
            {
                FILE *file = fopen("/home/mr_nakhjavani/Documents/global_name", "w");
                fprintf(file, "USERNAME: %s\n", argv[4]);
                fclose(file);
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                    return 1;
                char tmp_cwd[1024];
                bool exists = false;
                struct dirent *entry;
                do
                {
                    DIR *dir = opendir(".");
                    while ((entry = readdir(dir)) != NULL)
                    {
                        if (strcmp(entry->d_name, ".monster") == 0)
                        {
                            FILE *temp = fopen(".monster/config_username", "w");
                            fprintf(temp, "USERNAME: %s\n", argv[4]);
                            fclose(temp);
                        }
                    }
                    closedir(dir);
                    getcwd(tmp_cwd, sizeof(tmp_cwd));
                    if (strcmp(tmp_cwd, "/") != 0)
                        chdir("..");
                } while (strcmp(tmp_cwd, "/") != 0);
                printf("Your name is regesterd succesfully!\n");
                chdir(cwd);
                return 0;
            }
            else if (strcmp(argv[3], "user.email") == 0)
            {
                FILE *file = fopen("/home/mr_nakhjavani/Documents/global_email", "w");
                fprintf(file, "EMAIL: %s\n", argv[4]);
                fclose(file);
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                    return 1;
                char tmp_cwd[1024];
                bool exists = false;
                struct dirent *entry;
                do
                {
                    DIR *dir = opendir(".");
                    while ((entry = readdir(dir)) != NULL)
                    {
                        if (strcmp(entry->d_name, ".monster") == 0)
                        {
                            FILE *temp = fopen(".monster/config_email", "w");
                            fprintf(temp, "EMAIL: %s\n", argv[4]);
                            fclose(temp);
                        }
                    }
                    closedir(dir);
                    getcwd(tmp_cwd, sizeof(tmp_cwd));
                    if (strcmp(tmp_cwd, "/") != 0)
                        chdir("..");
                } while (strcmp(tmp_cwd, "/") != 0);
                printf("Your email is registerd succesfully!\n");
                chdir(cwd);
                return 0;
            }
            else
            {
                printf("Invalid command\n");
                return 1;
            }
        }
    }
    else
    {
        if (!init_flag())
        {
            printf("First you have to create a repository\n");
            return 1;
        }
        if (strstr(argv[2], "alias.") != NULL)
        {
            return alias(argc, argv);
        }
        else
        {
            if (strcmp(argv[2], "user.name") == 0)
            {
                FILE *config_username = fopen(".monster/config_username", "w");
                fprintf(config_username, "USERNAME: %s\n", argv[3]);
                fclose(config_username);
                printf("Your name is regesterd succesfully!\n");
            }
            else if (strcmp(argv[2], "user.email") == 0)
            {
                FILE *config_email = fopen(".monster/config_email", "w");
                fprintf(config_email, "EMAIL: %s\n", argv[3]);
                fclose(config_email);
                printf("Your email is registerd succesfully!\n");
            }
            else
            {
                printf("Invalid command\n");
                return 1;
            }
        }
    }
}

int alias(int argc, char *argv[])
{
    if (strcmp(argv[2], "-global") == 0)
    {
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        sscanf(argv[3], "alias.%s", temp);
        sprintf(filename, "/home/mr_nakhjavani/Documents/alias_global/%s", temp);
        FILE *file = fopen(filename, "w");
        fputs(argv[4], file);
        printf("Your link is created succesfully!\n");
        return 0;
    }
    else if (strstr(argv[2], "alias.") != NULL)
    {
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        strcpy(filename, ".monster/alias/");
        sscanf(argv[2], "alias.%s", temp);
        strcat(filename, temp);
        FILE *file = fopen(filename, "w");
        fputs(argv[3], file);
        printf("Your link is created succesfully!\n");
        return 0;
    }
    else
    {
        printf("Invalid command\n");
        return 1;
    }
}

int add_file(char *path)
{
    FILE *file_to_add = fopen(path, "r");
    if (file_to_add == NULL)
    {
        printf("File doesn't exists\n");
        return 1;
    }
    int start = 0;
    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (*(path + i) == '/')
        {
            start = i + 1;
            break;
        }
    }
    char file_name[MAX_FILENAME_LENGTH];
    char real_file_name[MAX_FILENAME_LENGTH];
    strcpy(file_name, ".monster/added/");
    for (int i = start + 15; i < strlen(path) + 15; i++)
    {
        file_name[i - start] = *(path + i - 15);
        real_file_name[i - start - 15] = path[i - 15];
    }
    real_file_name[strlen(path) - start] = '\0';
    file_name[15 + strlen(path)] = '\0';
    char unstaged[MAX_FILENAME_LENGTH];
    sprintf(unstaged, ".monster/unstaged/%s", real_file_name);
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(".monster/staged", "a");
    fprintf(file, "%s\n", path);
    fclose(file);
    file = fopen(file_name, "w");
    while (fgets(line, sizeof(line), file_to_add) != NULL)
    {
        fputs(line, file);
    }
    printf("file %s added to stage succesfully!\n", path);
    if (check_if_file_is_unstaged(path) == 'U')
        remove(unstaged);
    fclose(file);
    fclose(file_to_add);
    return 0;
}

void add_file_or_folder(char input[])
{
    if (!isDirectory(input) && strcmp(input, ".") != 0 && strcmp(input, "..") != 0)
    {
        add_file(input);
    }
    else if (isDirectory(input))
    {
        DIR *dir = opendir(input);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char path[MAX_FILENAME_LENGTH];
                sprintf(path, "%s/%s", input, entry->d_name);
                if (isDirectory(path))
                {
                    char *temp = input;
                    input = path;
                    add_file_or_folder(input);
                    input = temp;
                }
                if (!isDirectory(path))
                    add_file(path);
            }
        }
    }
}

int add(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani//Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc < 3)
    {
        printf("Please specify a file\n");
        return 1;
    }
    if (strcmp(argv[2], "-f") == 0)
    {
        for (int i = 3; i < argc; i++)
            add_file_or_folder(argv[i]);
        return 0;
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        int flag = 1;
        DIR *dir = opendir(".");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".monster") != 0 && isDirectory(entry->d_name) == 0)
            {
                printf("%s: ", entry->d_name);
                flag = 0;
                if (check_if_file_is_unstaged(entry->d_name) == 'S')
                    printf("STAGED\n");
                else
                    printf("NOT STAGED\n");
            }
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".monster") != 0 && isDirectory(entry->d_name) == 1)
                printf("%s: IS A DIRECTORY!\n", entry->d_name);
        }
        if (flag)
        {
            printf("There is no file or folder in this directory!\n");
            return 1;
        }
        return 0;
    }
    else
    {
        for (int i = 2; i < argc; i++)
            add_file_or_folder(argv[i]);
        return 0;
    }
}

int reset(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc < 3)
    {
        perror("please specify a file");
        return 1;
    }
    if (strcmp(argv[2], "-undo") == 0)
    {
        int counter = 0;
        FILE *file = fopen(".monster/staged", "r");
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file))
        {
            counter++;
        }
        for (int i = 1; i < counter; i++)
        {
            fgets(line, sizeof(line), file);
        }
        line[strlen(line) - 1] = '\0';
        reset_file(line);
        fclose(file);
        return 0;
    }
    else if (strcmp(argv[2], "-f") == 0)
    {
        for (int i = 3; i < argc; i++)
            reset_file_or_directory(argv[i]);
        return 0;
    }
    else
    {
        for (int i = 2; i < argc; i++)
            reset_file_or_directory(argv[i]);
        return 0;
    }
}

void reset_file_or_directory(char input[])
{
    if (!isDirectory(input))
    {
        reset_file(input);
    }
    else if (isDirectory(input))
    {
        DIR *dir = opendir(input);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char path[MAX_FILENAME_LENGTH];
                sprintf(path, "%s/%s", input, entry->d_name);
                if (isDirectory(path))
                {
                    char *temp = input;
                    input = path;
                    reset_file_or_directory(input);
                    input = temp;
                }
                if (!isDirectory(path))
                {
                    reset_file(path);
                }
            }
        }
    }
}

void reset_file(char *path)
{
    if (check_if_file_is_unstaged(path) == 'U')
    {
        printf("File %s is already unstaged!\n", path);
        return;
    }
    FILE *file = fopen(".monster/staged", "r");
    char line[MAX_LINE_LENGTH];
    int flag = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, path) == 0)
        {
            flag = 1;
            break;
        }
    }
    fclose(file);
    if (flag)
    {
        int start = 0;
        char file_name[MAX_FILENAME_LENGTH];
        for (int i = strlen(path) - 1; i >= 0; i--)
        {
            if (path[i] == '/')
            {
                start = i + 1;
                break;
            }
        }
        for (int i = start; i < strlen(path); i++)
        {
            file_name[i - start] = path[i];
        }
        file_name[strlen(path) - start] = '\0';
        char address[MAX_FILENAME_LENGTH];
        sprintf(address, ".monster/added/%s", file_name);
        DIR *dir = opendir(".monster/added/");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                if (strcmp(entry->d_name, file_name) == 0)
                {
                    file = fopen(address, "r");
                    char file_name[MAX_FILENAME_LENGTH];
                    sprintf(file_name, ".monster/unstaged/%s", entry->d_name);
                    FILE *file2 = fopen(file_name, "w");
                    char line1[MAX_LINE_LENGTH];
                    nuller(line1);
                    while (fgets(line1, sizeof(line1), file) != NULL)
                    {
                        fputs(line1, file2);
                    }
                    fclose(file2);
                    fclose(file);
                    remove(address);
                    file = fopen(".monster/staged", "a");
                    file2 = fopen(".monster/ustaged", "a");
                    while (fgets(line1, sizeof(line1), file) != NULL)
                    {
                        line1[strlen(line1) - 1] = '\0';
                        if (strcmp(line1, entry->d_name) == 0)
                        {
                            fputs(line1, file2);
                        }
                    }
                }
            }
        }
        printf("File %s is succefully unstaged!\n", path);
        return;
    }
    printf("File %s is not added to staging area!\n", path);
    return;
}

char status_mode(char *path)
{
    FILE *file1 = fopen(path, "r");
    if (file1 == NULL)
        return 'D';
    FILE *file2;
    char file_name[MAX_FILENAME_LENGTH];
    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int start = 0;
    for (int i = strlen(path) - 1; i >= 0; i--)
    {
        if (path[i] == '/')
        {
            start = i + 1;
            break;
        }
    }
    strcpy(file_name, ".monster/added/");
    for (int i = start; i < strlen(path); i++)
    {
        file_name[i - start + 15] = path[i];
    }
    file2 = fopen(file_name, "r");
    int counter_line1 = 0;
    int counter_line2 = 0;
    while (fgets(line1, sizeof(line1), file1) != NULL)
    {
        counter_line1++;
    }
    rewind(file1);
    while (fgets(line2, sizeof(line2), file2) != NULL)
    {
        counter_line2++;
    }
    rewind(file2);
    if (counter_line1 != counter_line2)
        return 'M';
    while (fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL)
    {
        if (strcmp(line1, line2) != 0)
            return 'M';
    }
    return 'A';
}

void status_file_or_directory(char input[])
{
    if (!isDirectory(input))
    {
        status_file(input);
    }
    else if (isDirectory(input))
    {
        DIR *dir = opendir(input);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char path[MAX_FILENAME_LENGTH];
                sprintf(path, "%s/%s", input, entry->d_name);
                if (isDirectory(path))
                {
                    char *temp = input;
                    input = path;
                    status_file_or_directory(input);
                    input = temp;
                }
                if (!isDirectory(path))
                {
                    status_file(path);
                }
            }
        }
    }
}

void status_file(char *path)
{
    if (check_if_file_is_unstaged(path) == 'S')
        printf("File %s status: +%c\n", path, status_mode(path));
    else
        printf("File %s status: -\n", path);
    return;
}

int status(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    DIR *dir = opendir(".");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, ".monster") != 0)
            status_file_or_directory(entry->d_name);
    }
}

int commit(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc > 4)
    {
        printf("If your message has space you should write it between double qoutes!\n");
        return 1;
    }
    if (argc < 4)
    {
        printf("Your commit must have a message!\n");
        return 1;
    }
    if (strlen(argv[3]) > 72)
    {
        printf("Your commit message length shouldn't be more than 72 character!\n");
        return 1;
    }
    DIR *dir = opendir(".monster/added/");
    if (strcmp(argv[2], "-m") == 0)
    {
        if (HEAD_flag())
        {
            struct dirent *entry;
            char file_name_dest[MAX_FILENAME_LENGTH];
            char file_name_src[MAX_FILENAME_LENGTH];
            char file_name_dest_2[MAX_FILENAME_LENGTH];
            int flag = 0;
            int counter_commited_files = 0;
            DIR *dwadaw = opendir(".monster/added/");
            struct dirent *kiir;
            if ((kiir = readdir(dwadaw)) == NULL)
            {
                printf("There is no file in staging area!\n");
                return 1;
            }
            DIR *mamad = opendir(".monster/commits/");
            struct dirent *memed;
            while ((memed = readdir(mamad)) != NULL)
            {
                if (strcmp(memed->d_name, ".") != 0 && strcmp(memed->d_name, "..") != 0)
                {
                    char tetete[1000];
                    sprintf(tetete, ".monster/commits/%s", memed->d_name);
                    remove(tetete);
                }
            }
            closedir(mamad);
            while ((entry = readdir(dir)) != NULL)
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    flag = 1;
                    sprintf(file_name_src, ".monster/added/%s", entry->d_name);
                    char commitname[MAX_FILENAME_LENGTH];
                    sprintf(commitname, ".monster/commits%d", commitcounter());
                    mkdir(commitname, 0755);
                    sprintf(file_name_dest, ".monster/commits%d/%s", commitcounter(), entry->d_name);
                    sprintf(file_name_dest_2, ".monster/commits/%s", entry->d_name);
                    FILE *file_dest = fopen(file_name_dest, "w");
                    FILE *file_dest_2 = fopen(file_name_dest_2, "w");
                    FILE *file_src = fopen(file_name_src, "r");
                    char line[MAX_LINE_LENGTH];
                    while (fgets(line, sizeof(line), file_src) != NULL)
                    {
                        fputs(line, file_dest);
                        fputs(line, file_dest_2);
                    }
                    fclose(file_dest);
                    fclose(file_dest_2);
                    fclose(file_src);
                    remove(file_name_src);
                    counter_commited_files++;
                }
            }
            if (flag)
            {
                char line[MAX_LINE_LENGTH];
                FILE *file = fopen(".monster/commitsinformation", "a");
                FILE *username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                time_t rawtime;
                struct tm *info;
                time(&rawtime);
                info = localtime(&rawtime);
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                fputs(line, file);
                fclose(username);
                FILE *email = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
                fgets(line, sizeof(line), email);
                if (line == NULL)
                {
                    username = fopen(".monster/config_email", "r");
                    fgets(line, sizeof(line), email);
                }
                fputs(line, file);
                FILE *branch = fopen(".monster/mybranch", "r");
                fgets(line, sizeof(line), branch);
                fprintf(file, "branch:%s\n", line);
                fprintf(file, "at %d:%d:%d\n", info->tm_hour, info->tm_min, info->tm_sec);
                int id = commitcounter();
                fprintf(file, "commit id:%d\n", id);
                fprintf(file, "%d files commited\n", counter_commited_files);
                fprintf(file, "%s\n", argv[3]);
                fprintf(file, "---\n");
                fclose(file);
                nuller(line);
                username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                fclose(username);
                printf("Your commit was succefully done by %sat %d:%d:%d\nwith id:%d\n[%s]", line, info->tm_hour, info->tm_min, info->tm_sec, id, argv[3]);
                file = fopen(".monster/myid", "w");
                fprintf(file, "%d", id);
                fclose(file);
            }
            else
            {
                printf("There is no file in staging area!\n");
                return 1;
            }
        }
        else
        {
            printf("You can't commit anything now(try runnig monster checkout HEAD)\n");
            return 1;
        }
    }
    else if (strcmp(argv[2], "-s") == 0)
    {
        if (HEAD_flag())
        {
            char filename[MAX_FILENAME_LENGTH];
            sprintf(filename, ".monster/shortcuts/%s", argv[3]);
            FILE *file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("No shortcut exists with given name!\n");
                return 1;
            }
            char line[MAX_LINE_LENGTH];
            fgets(line, sizeof(line), file);
            argv[2][1] = 'm';
            nuller(argv[3]);
            sprintf(argv[3], "%s", line);
            return commit(argc, argv);
        }
        else
        {
            printf("You can't commit anything now(try runnig monster checkout HEAD)\n");
            return 1;
        }
    }
}

int set(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc != 6)
    {
        printf("Invalid inputs!\n");
        return 1;
    }
    char filename[MAX_FILENAME_LENGTH];
    sprintf(filename, ".monster/shortcuts/%s", argv[5]);
    if (strcmp(argv[1], "replace") == 0)
    {
        FILE *temp = fopen(filename, "r");
        if (temp == NULL)
        {
            printf("No shortcut exists with give name!\n");
            return 1;
        }
    }
    FILE *file = fopen(filename, "w");
    fputs(argv[3], file);
    printf("Your link created succefully!\n");
    return 0;
}

int removeshortcut(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc != 4)
    {
        printf("Invalid inputs!\n");
        return 1;
    }
    char filename[MAX_FILENAME_LENGTH];
    sprintf(filename, ".monster/shortcuts/%s", argv[3]);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("No shortcut exists with give name!\n");
        return 1;
    }
    remove(filename);
    printf("Shortcut(%s) is succefully removed!\n", argv[3]);
    return 0;
}

int log_git(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    FILE *file = fopen(".monster/commitsinformation", "r");
    char line[MAX_LINE_LENGTH];
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("No commit to show!\n");
        return 1;
    }
    fclose(file);
    if (argc == 2)
    {
        show_log(999, 0);
        return 0;
    }
    else if (strcmp(argv[2], "-n") == 0 && argc == 4)
    {
        int number = atoi(argv[3]);
        show_log(999, number);
        return 0;
    }
    else if (strcmp(argv[2], "-branch") == 0)
    {
        show_some_log(999, argv);
        return 0;
    }
    else if (strcmp(argv[2], "-author") == 0)
    {
        show_some_log(999, argv);
        return 0;
    }
    else if (strcmp(argv[2], "-since") == 0)
    {
        show_some_log(999, argv);
        return 0;
    }
    else if (strcmp(argv[2], "-before") == 0)
    {
        show_some_log(999, argv);
        return 0;
    }
    else if (strcmp(argv[2], "-search") == 0 && argc == 4)
    {
        show_some_log(999, argv);
        return 0;
    }
    else if (strcmp(argv[2], "-search") == 0 && argc > 4)
    {
        for (int i = 3; i < argc; i++)
            show_some_log_plus(999, argv[i]);
        return 0;
    }
    else
    {
        printf("invalid inputs!\n");
        return 1;
    }
}

void show_log(int counter, int number)
{
    if (counter == commitcounter() - number)
        return;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(".monster/commitsinformation", "r");
    for (int i = counter; i < commitcounter() - 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fgets(line, sizeof(line), file);
        }
    }
    nuller(line);
    for (int i = 0; i < 8; i++)
    {
        fgets(line, sizeof(line), file);
        line[strlen(line) - 1] = '\0';
        if (line[0] != '\0')
            puts(line);
    }
    rewind(file);
    show_log(counter + 1, number);
}

void show_some_log(int counter, char *argv[])
{
    if (counter == commitcounter())
        return;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(".monster/commitsinformation", "r");
    for (int i = counter; i < commitcounter() - 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fgets(line, sizeof(line), file);
        }
    }
    if (strcmp(argv[2], "-branch") == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            fgets(line, sizeof(line), file);
        }
        line[strlen(line) - 1] = '\0';
        char branch_name[100];
        nuller(branch_name);
        sscanf(line, "branch:%s", branch_name);
        rewind(file);
        for (int i = counter; i < commitcounter() - 1; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
            }
        }
        if (strcmp(argv[3], branch_name) == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                puts(line);
            }
        }
        rewind(file);
        show_some_log(counter + 1, argv);
    }
    if (strcmp(argv[2], "-author") == 0)
    {
        fgets(line, sizeof(line), file);
        line[strlen(line) - 1] = '\0';
        char username[100];
        nuller(username);
        sscanf(line, "USERNAME:%s", username);
        rewind(file);
        for (int i = counter; i < commitcounter() - 1; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
            }
        }
        if (strcmp(argv[3], username) == 0)
        {
            for (int i = 0; i < 8; i++)
            {
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                puts(line);
            }
        }
        rewind(file);
        show_some_log(counter + 1, argv);
    }
    if (strcmp(argv[2], "-since") == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            fgets(line, sizeof(line), file);
        }
        line[strlen(line) - 1] = '\0';
        int hour = 0;
        int min = 0;
        int sec = 0;
        sscanf(line, "at %d:%d:%d", &hour, &min, &sec);
        rewind(file);
        for (int i = counter; i < commitcounter() - 1; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
            }
        }
        int m_hour = 0;
        int m_min = 0;
        int m_sec = 0;
        sscanf(argv[3], "%d:%d:%d", &m_hour, &m_min, &m_sec);
        nuller(line);
        if ((m_hour < hour) || (m_hour == hour && m_min < min) || (m_hour == hour && m_min == min && m_sec < sec) || (m_hour == hour && m_min == min && m_sec == sec))
        {
            for (int i = 0; i < 8; i++)
            {
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                if (line[0] != '\0')
                    puts(line);
            }
        }
        rewind(file);
        show_some_log(counter + 1, argv);
    }
    if (strcmp(argv[2], "-before") == 0)
    {
        for (int i = 0; i < 4; i++)
        {
            fgets(line, sizeof(line), file);
        }
        line[strlen(line) - 1] = '\0';
        int hour = 0;
        int min = 0;
        int sec = 0;
        sscanf(line, "at %d:%d:%d", &hour, &min, &sec);
        rewind(file);
        for (int i = counter; i < commitcounter() - 1; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
            }
        }
        int m_hour = 0;
        int m_min = 0;
        int m_sec = 0;
        sscanf(argv[3], "%d:%d:%d", &m_hour, &m_min, &m_sec);
        nuller(line);
        if ((m_hour > hour) || (m_hour == hour && m_min > min) || (m_hour == hour && m_min == min && m_sec > sec) || (m_hour == hour && m_min == min && m_sec == sec))
        {
            for (int i = 0; i < 8; i++)
            {
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                if (line[0] != '\0')
                    puts(line);
            }
        }
        rewind(file);
        show_some_log(counter + 1, argv);
    }
    if (strcmp(argv[2], "-search") == 0)
    {
        for (int i = 0; i < 7; i++)
        {
            fgets(line, sizeof(line), file);
        }
        // line[strlen(line)-1]='\0';
        char message[MAX_COMMIT_MESSAGE_LENGTH];
        nuller(message);
        sscanf(line, "%s", message);
        char *token[MAX_WORDS_COUNT_IN_A_COMMAND];
        token[0] = strtok(message, " ");
        int counter_token = 0;
        while (token[counter_token] != NULL)
        {
            counter_token++;
            token[counter_token] = strtok(NULL, " ");
        }

        rewind(file);
        for (int i = counter; i < commitcounter() - 1; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
            }
        }
        nuller(line);
        for (int i = 0; i < counter_token; i++)
        {
            if (strcmp(argv[3], token[i]) == 0)
            {
                for (int j = 0; j < 8; j++)
                {
                    fgets(line, sizeof(line), file);
                    line[strlen(line) - 1] = '\0';
                    if (line[0] != '\0')
                        puts(line);
                }
            }
        }
        rewind(file);
        show_some_log(counter + 1, argv);
    }
}

void show_some_log_plus(int counter, char *word)
{
    if (counter == commitcounter())
        return;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(".monster/commitsinformation", "r");
    for (int i = counter; i < commitcounter() - 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fgets(line, sizeof(line), file);
        }
    }
    for (int i = 0; i < 7; i++)
    {
        fgets(line, sizeof(line), file);
    }
    line[strlen(line) - 1] = '\0';
    char message[MAX_COMMIT_MESSAGE_LENGTH];
    nuller(message);
    sscanf(line, "%s", message);
    char *token[MAX_WORDS_COUNT_IN_A_COMMAND];
    token[0] = strtok(message, " ");
    int counter_token = 0;
    while (token[counter_token] != NULL)
    {
        counter_token++;
        token[counter_token] = strtok(NULL, " ");
    }

    rewind(file);
    for (int i = counter; i < commitcounter() - 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            fgets(line, sizeof(line), file);
        }
    }
    for (int i = 0; i < counter_token; i++)
    {
        if (strcmp(word, token[i]) == 0)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                if (line[0] != '\0')
                    puts(line);
            }
        }
    }
    rewind(file);
    show_some_log_plus(counter + 1, word);
}

int branch(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc == 3)
    {
        char filename[MAX_FILENAME_LENGTH];
        sprintf(filename, ".monster/branches/%s", argv[2]);
        FILE *file = fopen(filename, "w");
        fclose(file);
        printf("Your branch (%s) was succefully made!\n", argv[2]);
        return 0;
    }
    if (argc == 2)
    {
        FILE *file = fopen(".monster/mybranch", "r");
        char branch[100];
        fgets(branch, sizeof(branch), file);
        DIR *dir = opendir(".monster/branches/");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                if (strcmp(entry->d_name, branch) == 0)
                {
                    printf("*%s*\n", entry->d_name);
                }
                else
                {
                    printf("%s\n", entry->d_name);
                }
            }
        }
        return 0;
    }
    printf("Invalid command!\n");
    return 0;
}

int checkout(int argc, char *argv[])
{
    if (!config_flag())
    {
        FILE *file1 = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
        FILE *file2 = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
        if (file1 == NULL || file2 == NULL)
        {
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argv[2][0] < '0' || argv[2][0] > '9')
    {
        DIR *dir0 = opendir(".monster/added/");
        struct dirent* entryy;
        for(int i=0;i<2;i++){
            readdir(dir0);
        }
        if (((entryy = readdir(dir0)) != NULL))
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
        closedir(dir0);
        int flag = 1;
        DIR *dir = opendir(".monster/branches/");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, argv[2]) == 0)
            {
                flag = 0;
                FILE *file = fopen(".monster/mybranch", "r");
                char temp[MAX_LINE_LENGTH];
                fgets(temp, sizeof(temp), file);
                if (strcmp(argv[2], temp) == 0)
                {
                    printf("You already are in branch %s\n", temp);
                    return 1;
                }
                fclose(file);
                file = fopen(".monster/mybranch", "w");
                fprintf(file, "%s", argv[2]);
                fclose(file);
            }
        }
        if(flag==0)
            printf("Switched to branch %s", argv[2]);
        if (flag)
        {
            printf("Wrong branch name!\n");
            return 1;
        }
        return 0;
    }
    if (argv[2][0] >= '0' && argv[2][0] <= '9')
    {
        DIR *dir0 = opendir(".monster/added/");
        struct dirent* entryy;
        for(int i=0;i<2;i++){
            readdir(dir0);
        }
        if (((entryy = readdir(dir0)) != NULL))
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
        closedir(dir0);
        int flag = 1;
        int id = atoi(argv[2]);
        DIR *dir = opendir(".monster");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strstr(entry->d_name, "commits") != NULL && strcmp(entry->d_name, "commits") != 0)
            {
                int id_to_find = 0;
                sscanf(entry->d_name, "commits%d", &id_to_find);
                if (id == id_to_find)
                {
                    DIR *mamad = opendir(".monster/commits/");
                    struct dirent *memed;
                    while ((memed = readdir(mamad)) != NULL)
                    {
                        if (strcmp(memed->d_name, ".") != 0 && strcmp(memed->d_name, "..") != 0)
                        {
                            char tetete[1000];
                            sprintf(tetete, ".monster/commits/%s", memed->d_name);
                            remove(tetete);
                        }
                    }
                    flag = 0;
                    char dirname[MAX_FILENAME_LENGTH];
                    nuller(dirname);
                    sprintf(dirname, ".monster/commits%d/", id);
                    DIR *dir2 = opendir(dirname);
                    struct dirent *entry2;
                    while ((entry2 = readdir(dir2)) != NULL)
                    {
                        char filename[MAX_FILENAME_LENGTH];
                        char filename_d[MAX_FILENAME_LENGTH];
                        nuller(filename);
                        nuller(filename_d);
                        sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                        sprintf(filename_d, ".monster/commits/%s", entry2->d_name);
                        FILE *file_src = fopen(filename, "r");
                        FILE *file_dest = fopen(filename_d, "w");
                        char line[MAX_LINE_LENGTH];
                        while (fgets(line, sizeof(line), file_src) != NULL)
                        {
                            fputs(line, file_dest);
                        }
                    }
                    closedir(dir2);
                }
            }
        }
        FILE *filedwadwa = fopen(".monster/myid", "w");
        fprintf(filedwadwa, "%d", id);
        printf("Switched to commit %d", id);
        closedir(dir);
        return 0;
        if (flag)
        {
            printf("Invalid commit id!\n");
            return 1;
        }
    }
    if (strcmp(argv[2], "HEAD") == 0)
    {
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        sprintf(temp, "%d", commitcounter());
        nuller(argv[2]);
        sprintf(argv[2], "%s", temp);
        return checkout(argc, argv);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Please enter a valid command\n");
        return 1;
    }
    if (strcmp(argv[1], "config") == 0)
        return config(argc, argv);
    if (strcmp(argv[1], "init") == 0)
        return init(argc, argv);
    if (strcmp(argv[1], "add") == 0)
        return add(argc, argv);
    if (strcmp(argv[1], "reset") == 0)
        return reset(argc, argv);
    if (strcmp(argv[1], "status") == 0)
        return status(argc, argv);
    if (strcmp(argv[1], "commit") == 0)
        return commit(argc, argv);
    if ((strcmp(argv[1], "set") == 0 || strcmp(argv[1], "replace") == 0) && strcmp(argv[2], "-m") == 0 && strcmp(argv[4], "-s") == 0)
        return set(argc, argv);
    if (strcmp(argv[1], "remove") == 0 && strcmp(argv[2], "-s") == 0)
        return removeshortcut(argc, argv);
    if (strcmp(argv[1], "log") == 0)
        return log_git(argc, argv);
    if (strcmp(argv[1], "branch") == 0)
        return branch(argc, argv);
    if (strcmp(argv[1], "checkout") == 0)
        return checkout(argc, argv);
    if (init_flag())
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        chdir(".monster/alias");
        struct dirent *entry;
        DIR *dir = opendir(".");
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, argv[1]) == 0)
            {
                FILE *file = fopen(argv[1], "r");
                char line[MAX_LINE_LENGTH];
                fgets(line, sizeof(line), file);
                line[strlen(line)] = '\0';
                char *words[MAX_WORDS_COUNT_IN_A_COMMAND];
                words[0] = strtok(line, " ");
                int count_of_words = 0;
                while (words[count_of_words] != NULL)
                {
                    count_of_words++;
                    words[count_of_words] = strtok(NULL, " ");
                }
                chdir(cwd);
                if (strcmp(words[1], "config") == 0)
                    return config(count_of_words, words);
                if (strcmp(words[1], "init") == 0)
                    return init(count_of_words, words);
                if (strcmp(words[1], "add") == 0)
                    return add(count_of_words, words);
                if (strcmp(words[1], "reset") == 0)
                    return reset(count_of_words, words);
                if (strcmp(words[1], "status") == 0)
                    return status(count_of_words, words);
                if (strcmp(words[1], "commit") == 0)
                    return commit(count_of_words, words);
                if ((strcmp(words[1], "set") == 0 || strcmp(words[1], "replace") == 0) && strcmp(words[2], "-m") == 0 && strcmp(words[4], "-s") == 0)
                    return set(count_of_words, words);
                if (strcmp(words[1], "remove") == 0 && strcmp(words[2], "-s") == 0)
                    return removeshortcut(count_of_words, words);
                if (strcmp(words[1], "log") == 0)
                    return log_git(count_of_words, words);
                if (strcmp(words[1], "branch") == 0)
                    return branch(count_of_words, words);
                if (strcmp(words[1], "checkout") == 0)
                    return checkout(count_of_words, words);
            }
        }
        closedir(dir);
        chdir("/home/mr_nakhjavani/Documents/alias_global");
        dir = opendir(".");
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, argv[1]) == 0)
            {
                FILE *file = fopen(argv[1], "r");
                char line[MAX_LINE_LENGTH];
                fgets(line, sizeof(line), file);
                line[strlen(line)] = '\0';
                char *words[MAX_WORDS_COUNT_IN_A_COMMAND];
                words[0] = strtok(line, " ");
                int count_of_words = 0;
                while (words[count_of_words] != NULL)
                {
                    count_of_words++;
                    words[count_of_words] = strtok(NULL, " ");
                }
                chdir(cwd);
                if (strcmp(words[1], "config") == 0)
                    return config(count_of_words, words);
                if (strcmp(words[1], "init") == 0)
                    return init(count_of_words, words);
                if (strcmp(words[1], "add") == 0)
                    return add(count_of_words, words);
                if (strcmp(words[1], "reset") == 0)
                    return reset(count_of_words, words);
                if (strcmp(words[1], "status") == 0)
                    return status(count_of_words, words);
                if (strcmp(words[1], "commit") == 0)
                    return commit(count_of_words, words);
                if ((strcmp(words[1], "set") == 0 || strcmp(words[1], "replace") == 0) && strcmp(words[2], "-m") == 0 && strcmp(words[4], "-s") == 0)
                    return set(count_of_words, words);
                if (strcmp(words[1], "remove") == 0 && strcmp(words[2], "-s") == 0)
                    return removeshortcut(count_of_words, words);
                if (strcmp(words[1], "log") == 0)
                    return log_git(count_of_words, words);
                if (strcmp(words[1], "branch") == 0)
                    return branch(count_of_words, words);
                if (strcmp(words[1], "checkout") == 0)
                    return checkout(count_of_words, words);
            }
        }
        printf("Invalid command!\n");
        return 1;
    }
    printf("Invalid command\n");
    return 1;
}