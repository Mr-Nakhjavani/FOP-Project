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
int revert(int argc, char *argv[]);
bool uncommited_change();
int monster_tag(int argc, char *argv[]);
int tag_counter();
void red();
int grerp(int argc, char *argv[]);
void black();
int diff(int argc, char *argv[]);
void filesizecheck(char *address);
void green();
int pre_commit(int argc, char *argv[]);
void todocheck(char *address);
void balancebraces(char *address);
void characterlimit(char *address);

void balancebraces(char *address)
{
    printf("balance-braces......................");
    int start = 0;
    int flag = 0;
    for (int i = strlen(address) - 1; i >= 0; i--)
    {
        if (address[i] == '.')
        {
            start = i + 1;
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        char mode[50];
        for (int i = start; i < strlen(address); i++)
        {
            mode[i - start] = address[i];
        }
        mode[strlen(address) - start] = '\0';
        if (strcmp(mode, "cpp") == 0 || strcmp(mode, "c") == 0 || strcmp(mode, "txt") == 0)
        {
            int sumk1 = 0;
            int sumk2 = 0;
            int sump1 = 0;
            int sump2 = 0;
            int sumb1 = 0;
            int sumb2 = 0;
            FILE *file = fopen(address, "r");
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line) - 1] = '\0';
                if (strstr(line, "{") != NULL)
                {
                    sumk1++;
                }
                if (strstr(line, "}") != NULL)
                {
                    sumk2++;
                }
                if (strstr(line, "(") != NULL)
                {
                    sump1++;
                }
                if (strstr(line, ")") != NULL)
                {
                    sump2++;
                }
                if (strstr(line, "[") != NULL)
                {
                    sumb1++;
                }
                if (strstr(line, "]") != NULL)
                {
                    sumb2++;
                }
            }
            if (sumk1 != sumk2 || sumb1 != sumb2 || sump1 != sump2)
            {
                red();
                printf("FAILED");
                black();
                return;
            }
            else
            {
                green();
                printf("PASSED\n");
                black();
                return;
            }
        }
        else
        {
            printf("SKIPPED\n");
            return;
        }
    }
    printf("SKIPPED\n");
    return;
}

void characterlimit(char *address)
{
    printf("character-limit......................");
    int start = 0;
    int flag = 0;
    for (int i = strlen(address) - 1; i >= 0; i--)
    {
        if (address[i] == '.')
        {
            start = i + 1;
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        char mode[50];
        for (int i = start; i < strlen(address); i++)
        {
            mode[i - start] = address[i];
        }
        mode[strlen(address) - start] = '\0';
        if (strcmp(mode, "cpp") == 0 || strcmp(mode, "c") == 0 || strcmp(mode, "txt") == 0)
        {
            int sum = 0;
            FILE *file = fopen(address, "r");
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line) - 1] = '\0';
                sum += strlen(line);
            }
            if (sum > 20000)
            {
                red();
                printf("FAILED");
                black();
                return;
            }
            else
            {
                green();
                printf("PASSED\n");
                black();
                return;
            }
        }
        else
        {
            printf("SKIPPED\n");
            return;
        }
    }
    printf("SKIPPED\n");
    return;
}

void todocheck(char *address)
{
    printf("todo-check......................");
    int start = 0;
    int flag = 0;
    for (int i = strlen(address) - 1; i >= 0; i--)
    {
        if (address[i] == '.')
        {
            start = i + 1;
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        char mode[50];
        for (int i = start; i < strlen(address); i++)
        {
            mode[i - start] = address[i];
        }
        mode[strlen(address) - start] = '\0';
        if (strcmp(mode, "cpp") == 0 || strcmp(mode, "c") == 0 || strcmp(mode, "txt") == 0)
        {
            FILE *file = fopen(address, "r");
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line) - 1] = '\0';
                if (strcmp(line, "// TODO") == 0 || strstr(line, "TODO") != NULL)
                {
                    red();
                    printf("FAILED\n");
                    black();
                    return;
                }
            }
            green();
            printf("PASSED\n");
            black();
            return;
        }
        else
        {
            printf("SKIPPED\n");
            return;
        }
    }
    printf("SKIPPED\n");
    return;
}

void black()
{
    printf("\033[0m");
}

void red()
{
    printf("\033[1;31m");
}

int tag_counter()
{
    FILE *file = fopen(".monster/taginformation", "r");
    int line = 0;
    char linee[MAX_LINE_LENGTH];
    while (fgets(linee, sizeof(linee), file) != NULL)
    {
        line++;
    }
    line /= 5;
    return line + 1;
}

bool uncommited_change()
{
    DIR *dir = opendir(".monster/commits");
    struct dirent *entry;
    FILE *file = fopen(".monster/staged", "r");
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, ".") != 0)
        {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                line[strlen(line) - 1] = '\0';
                char name[MAX_FILENAME_LENGTH];
                int start = 0;
                for (int i = strlen(line) - 1; i >= 0; i--)
                {
                    if (line[i] == '/')
                    {
                        start = i + 1;
                        break;
                    }
                }
                for (int i = start; i < strlen(line); i++)
                {
                    name[i - start] = line[i];
                }
                name[strlen(line) - start] = '\0';
                if (strcmp(name, entry->d_name) == 0)
                {
                    char filename1[MAX_FILENAME_LENGTH];
                    sprintf(filename1, ".monster/commits/%s", entry->d_name);
                    FILE *file1 = fopen(filename1, "r");
                    FILE *file2 = fopen(line, "r");
                    char line1[MAX_LINE_LENGTH];
                    char line2[MAX_LINE_LENGTH];
                    int cline1 = 0;
                    int cline2 = 0;
                    while (fgets(line1, sizeof(line1), file1) != NULL)
                    {
                        cline1++;
                    }
                    rewind(file1);
                    while (fgets(line2, sizeof(line2), file2) != NULL)
                    {
                        cline2++;
                    }
                    rewind(file2);
                    if (cline1 != cline2)
                    {
                        return true;
                    }
                    while (fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL)
                    {
                        if (strcmp(line1, line2) != 0)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool HEAD_flag()
{
    FILE *file = fopen(".monster/myid", "r");
    char number[100];
    fgets(number, sizeof(number), file);
    number[strlen(number)] = '\0';
    int id = atoi(number);
    if (id == commitcounter() - 1)
    {
        return true;
    }
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
        mkdir(".monster/appliedhooks", 0755);
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
        file = fopen(".monster/tagname", "w");
        fclose(file);
        file = fopen(".monster/taginformation", "w");
        fclose(file);
        file = fopen(".monster/hooklist", "w");
        fprintf(file, "todo-check\neof-blank-space\nformat-check\nbalance-braces\nindentation-check\nstatic-error-check\nfile-size-check\ncharacter-limit\ntime-limit\n");
        fclose(file);
        return 0;
    }
    else
    {
        printf("Monster repository has already initialized\n");
        return 1;
    }
}

void green()
{
    printf("\033[0;32m");
}

void filesizecheck(char *address)
{
    struct stat file_status;
    if (stat(address, &file_status) < 0)
    {
        return;
    }
    printf("file-size-check...............................");
    if (file_status.st_size / 1000000 < 5)
    {
        green();
        printf("PASSED\n");
        black();
        return;
    }
    else
    {
        red();
        printf("FAILED\n");
        black();
        return;
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
    if (check_if_file_is_unstaged(path) == 'S')
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
                    FILE *file = fopen(address, "r");
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
    DIR *dir = opendir(".monster/commits");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, ".") != 0)
        {
            char name[MAX_FILENAME_LENGTH];
            int start = 0;
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
                name[i - start] = path[i];
            }
            name[strlen(path) - start] = '\0';
            if (strcmp(name, entry->d_name) == 0)
            {
                char filename1[MAX_FILENAME_LENGTH];

                sprintf(filename1, ".monster/commits/%s", entry->d_name);
                FILE *file1 = fopen(filename1, "r");
                FILE *file2 = fopen(path, "r");
                char line1[MAX_LINE_LENGTH];
                char line2[MAX_LINE_LENGTH];
                int cline1 = 0;
                int cline2 = 0;
                while (fgets(line1, sizeof(line1), file1) != NULL)
                {
                    cline1++;
                }
                rewind(file1);
                while (fgets(line2, sizeof(line2), file2) != NULL)
                {
                    cline2++;
                }
                rewind(file2);
                if (cline1 != cline2)
                {
                    return 'M';
                }
                while (fgets(line1, sizeof(line1), file1) != NULL && fgets(line2, sizeof(line2), file2) != NULL)
                {
                    if (strcmp(line1, line2) != 0)
                    {
                        return 'M';
                    }
                }
                return 'A';
            }
        }
    }
    return 'D';
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
    {
        printf("File %s status: +%c\n", path, status_mode(path));
    }
    else
    {
        printf("File %s status: -%c\n", path, status_mode(path));
    }
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
                    char lineeeee[MAX_LINE_LENGTH];
                    while (fgets(lineeeee, sizeof(lineeeee), file_src) != NULL)
                    {
                        fputs(lineeeee, file_dest);
                        fputs(lineeeee, file_dest_2);
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
                printf("Your commit was succefully done by %sat %swith id:%d\n[%s]", line, asctime(info), id, argv[3]);
                file = fopen(".monster/myid", "w");
                fprintf(file, "%d", id);
                fclose(file);
                DIR *direc = opendir(".monster/commits");
                struct dirent *ent;
                while ((ent = readdir(direc)) != NULL)
                {
                    if (ent->d_name[0] != '.')
                    {
                        char srcname[MAX_FILENAME_LENGTH];
                        char destname[MAX_FILENAME_LENGTH];
                        sprintf(srcname, ".monster/commits/%s", ent->d_name);
                        sprintf(destname, ".monster/commits%d/%s", id, ent->d_name);
                        FILE *src = fopen(srcname, "r");
                        FILE *dest = fopen(destname, "w");
                        char line[MAX_LINE_LENGTH];
                        while (fgets(line, sizeof(line), src) != NULL)
                        {
                            fputs(line, dest);
                        }
                        fclose(src);
                        fclose(dest);
                    }
                }
                closedir(direc);
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
        {
            puts(line);
        }
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
    if ((argv[2][0] < '0' || argv[2][0] > '9') && strcmp(argv[2], "HEAD") != 0)
    {
        if (uncommited_change())
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
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
        if (flag == 0)
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
        if (uncommited_change())
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
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
                    flag = 0;
                    char dirname[MAX_FILENAME_LENGTH];
                    nuller(dirname);
                    sprintf(dirname, ".monster/commits%d/", id);
                    DIR *dir2 = opendir(dirname);
                    struct dirent *entry2;
                    while ((entry2 = readdir(dir2)) != NULL)
                    {
                        FILE *file1 = fopen(".monster/staged", "r");
                        char line[MAX_LINE_LENGTH];
                        while (fgets(line, sizeof(line), file1) != NULL)
                        {
                            line[strlen(line) - 1] = '\0';
                            char NAME[MAX_FILENAME_LENGTH];
                            int start = 0;
                            for (int i = strlen(line) - 1; i >= 0; i--)
                            {
                                if (line[i] == '/')
                                {
                                    start = i + 1;
                                    break;
                                }
                            }
                            for (int i = start; i < strlen(line); i++)
                            {
                                NAME[i - start] = line[i];
                            }
                            NAME[strlen(line) - start] = '\0';
                            if (strcmp(entry2->d_name, NAME) == 0)
                            {
                                char filename[MAX_FILENAME_LENGTH];
                                nuller(filename);
                                sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                                FILE *file_src = fopen(filename, "r");
                                FILE *file_dest = fopen(line, "w");
                                char linedddd[MAX_LINE_LENGTH];
                                while (fgets(linedddd, sizeof(linedddd), file_src) != NULL)
                                {
                                    fputs(linedddd, file_dest);
                                }
                            }
                        }
                    }
                    closedir(dir2);
                }
            }
        }
        if (flag == 0)
        {
            FILE *filez = fopen(".monster/myid", "w");
            fprintf(filez, "%d", id);
            printf("Switched to commit %d", id);
        }
        closedir(dir);
        if (flag)
        {
            printf("Invalid commit id!\n");
            return 1;
        }
        return 0;
    }
    if (strcmp(argv[2], "HEAD") == 0)
    {
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        sprintf(temp, "%d", commitcounter() - 1);
        nuller(argv[2]);
        sprintf(argv[2], "%s", temp);
        return checkout(argc, argv);
    }
}

int revert(int argc, char *argv[])
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
    if (strcmp(argv[2], "-m") == 0 && argv[4][0] >= '0' && argv[4][0] <= '9')
    {
        if (uncommited_change())
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
        char filenamesrc[MAX_FILENAME_LENGTH];
        char filenamedest[MAX_FILENAME_LENGTH];
        sprintf(filenamesrc, ".monster/commits%d/", atoi(argv[4]));
        DIR *dir = opendir(filenamesrc);
        nuller(filenamesrc);
        nuller(filenamedest);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                sprintf(filenamesrc, ".monster/commits%d/%s", atoi(argv[4]), entry->d_name);
                sprintf(filenamedest, ".monster/added/%s", entry->d_name);
                FILE *filesrc = fopen(filenamesrc, "r");
                FILE *filedest = fopen(filenamedest, "w");
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), filesrc) != NULL)
                {
                    fputs(line, filedest);
                }
                fclose(filesrc);
                fclose(filedest);
            }
        }
        int flag = 1;
        int id = atoi(argv[4]);
        DIR *dir3 = opendir(".monster");
        struct dirent *entry3;
        while ((entry3 = readdir(dir3)) != NULL)
        {
            if (strstr(entry3->d_name, "commits") != NULL && strcmp(entry3->d_name, "commits") != 0)
            {
                int id_to_find = 0;
                sscanf(entry3->d_name, "commits%d", &id_to_find);
                if (id == id_to_find)
                {
                    flag = 0;
                    char dirname[MAX_FILENAME_LENGTH];
                    nuller(dirname);
                    sprintf(dirname, ".monster/commits%d/", id);
                    DIR *dir2 = opendir(dirname);
                    struct dirent *entry2;
                    while ((entry2 = readdir(dir2)) != NULL)
                    {
                        FILE *file1 = fopen(".monster/staged", "r");
                        char line[MAX_LINE_LENGTH];
                        while (fgets(line, sizeof(line), file1) != NULL)
                        {
                            line[strlen(line) - 1] = '\0';
                            char NAME[MAX_FILENAME_LENGTH];
                            int start = 0;
                            for (int i = strlen(line) - 1; i >= 0; i--)
                            {
                                if (line[i] == '/')
                                {
                                    start = i + 1;
                                    break;
                                }
                            }
                            for (int i = start; i < strlen(line); i++)
                            {
                                NAME[i - start] = line[i];
                            }
                            NAME[strlen(line) - start] = '\0';
                            if (strcmp(entry2->d_name, NAME) == 0)
                            {
                                char filename[MAX_FILENAME_LENGTH];
                                nuller(filename);
                                sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                                FILE *file_src = fopen(filename, "r");
                                FILE *file_dest = fopen(line, "w");
                                char linedddd[MAX_LINE_LENGTH];
                                while (fgets(linedddd, sizeof(linedddd), file_src) != NULL)
                                {
                                    fputs(linedddd, file_dest);
                                }
                            }
                        }
                    }
                    closedir(dir2);
                }
            }
        }
        if (flag)
        {
            printf("Wrong commit id!\n");
            return 1;
        }
        closedir(dir);
        sprintf(argv[0], "monster");
        sprintf(argv[1], "commit");
        sprintf(argv[2], "-m");
        return commit(4, argv);
    }
    else if (argv[2][0] >= '0' && argv[2][0] <= '9')
    {
        if (uncommited_change())
        {
            printf("There are uncommited changes!\n");
            return 1;
        }
        char filenamesrc[MAX_FILENAME_LENGTH];
        char filenamedest[MAX_FILENAME_LENGTH];
        sprintf(filenamesrc, ".monster/commits%d", atoi(argv[2]));
        DIR *dir = opendir(filenamesrc);
        nuller(filenamesrc);
        nuller(filenamedest);
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                sprintf(filenamesrc, ".monster/commits%d/%s", atoi(argv[2]), entry->d_name);
                sprintf(filenamedest, ".monster/added/%s", entry->d_name);
                FILE *filesrc = fopen(filenamesrc, "r");
                FILE *filedest = fopen(filenamedest, "w");
                char line[MAX_LINE_LENGTH];
                while (fgets(line, sizeof(line), filesrc) != NULL)
                {
                    fputs(line, filedest);
                }
                fclose(filedest);
                fclose(filesrc);
            }
        }
        int flag = 1;
        int id = atoi(argv[2]);
        DIR *dir3 = opendir(".monster");
        struct dirent *entry3;
        while ((entry3 = readdir(dir3)) != NULL)
        {
            if (strstr(entry3->d_name, "commits") != NULL && strcmp(entry3->d_name, "commits") != 0)
            {
                int id_to_find = 0;
                sscanf(entry3->d_name, "commits%d", &id_to_find);
                if (id == id_to_find)
                {
                    flag = 0;
                    char dirname[MAX_FILENAME_LENGTH];
                    nuller(dirname);
                    sprintf(dirname, ".monster/commits%d/", id);
                    DIR *dir2 = opendir(dirname);
                    struct dirent *entry2;
                    while ((entry2 = readdir(dir2)) != NULL)
                    {
                        FILE *file1 = fopen(".monster/staged", "r");
                        char line[MAX_LINE_LENGTH];
                        while (fgets(line, sizeof(line), file1) != NULL)
                        {
                            line[strlen(line) - 1] = '\0';
                            char NAME[MAX_FILENAME_LENGTH];
                            int start = 0;
                            for (int i = strlen(line) - 1; i >= 0; i--)
                            {
                                if (line[i] == '/')
                                {
                                    start = i + 1;
                                    break;
                                }
                            }
                            for (int i = start; i < strlen(line); i++)
                            {
                                NAME[i - start] = line[i];
                            }
                            NAME[strlen(line) - start] = '\0';
                            if (strcmp(entry2->d_name, NAME) == 0)
                            {
                                char filename[MAX_FILENAME_LENGTH];
                                nuller(filename);
                                sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                                FILE *file_src = fopen(filename, "r");
                                FILE *file_dest = fopen(line, "w");
                                char linedddd[MAX_LINE_LENGTH];
                                while (fgets(linedddd, sizeof(linedddd), file_src) != NULL)
                                {
                                    fputs(linedddd, file_dest);
                                }
                            }
                        }
                    }
                    closedir(dir2);
                }
            }
        }
        if (flag)
        {
            printf("Wrong commit id!\n");
            return 1;
        }
        closedir(dir);
        FILE *filee = fopen(".monster/commitsinformation", "r");
        char linee[MAX_LINE_LENGTH];
        for (int i = 0; i < (atoi(argv[2]) - 1000); i++)
        {
            for (int j = 0; j < 8; j++)
            {
                fgets(linee, sizeof(linee), filee);
            }
        }
        for (int i = 0; i < 7; i++)
        {
            fgets(linee, sizeof(linee), filee);
        }
        linee[strlen(linee) - 1] = '\0';
        sprintf(argv[0], "monster");
        sprintf(argv[1], "commit");
        sprintf(argv[2], "-m");
        argv[3] = linee;
        return commit(4, argv);
    }
    else if (strcmp(argv[2], "-n") == 0)
    {
        if (argc == 4)
        {
            int flag = 1;
            int id = atoi(argv[3]);
            DIR *dir3 = opendir(".monster");
            struct dirent *entry3;
            while ((entry3 = readdir(dir3)) != NULL)
            {
                if (strstr(entry3->d_name, "commits") != NULL && strcmp(entry3->d_name, "commits") != 0)
                {
                    int id_to_find = 0;
                    sscanf(entry3->d_name, "commits%d", &id_to_find);
                    if (id == id_to_find)
                    {
                        flag = 0;
                        char dirname[MAX_FILENAME_LENGTH];
                        nuller(dirname);
                        sprintf(dirname, ".monster/commits%d/", id);
                        DIR *dir2 = opendir(dirname);
                        struct dirent *entry2;
                        while ((entry2 = readdir(dir2)) != NULL)
                        {
                            FILE *file1 = fopen(".monster/staged", "r");
                            char line[MAX_LINE_LENGTH];
                            while (fgets(line, sizeof(line), file1) != NULL)
                            {
                                line[strlen(line) - 1] = '\0';
                                char NAME[MAX_FILENAME_LENGTH];
                                int start = 0;
                                for (int i = strlen(line) - 1; i >= 0; i--)
                                {
                                    if (line[i] == '/')
                                    {
                                        start = i + 1;
                                        break;
                                    }
                                }
                                for (int i = start; i < strlen(line); i++)
                                {
                                    NAME[i - start] = line[i];
                                }
                                NAME[strlen(line) - start] = '\0';
                                if (strcmp(entry2->d_name, NAME) == 0)
                                {
                                    char filename[MAX_FILENAME_LENGTH];
                                    nuller(filename);
                                    sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                                    FILE *file_src = fopen(filename, "r");
                                    FILE *file_dest = fopen(line, "w");
                                    char linedddd[MAX_LINE_LENGTH];
                                    while (fgets(linedddd, sizeof(linedddd), file_src) != NULL)
                                    {
                                        fputs(linedddd, file_dest);
                                    }
                                }
                            }
                        }
                        closedir(dir2);
                    }
                }
            }
            if (flag)
            {
                printf("Wrong commit id!\n");
                return 1;
            }
        }
        else if (argc == 3)
        {
            int flag = 1;
            int id = commitcounter() - 1;
            DIR *dir3 = opendir(".monster");
            struct dirent *entry3;
            while ((entry3 = readdir(dir3)) != NULL)
            {
                if (strstr(entry3->d_name, "commits") != NULL && strcmp(entry3->d_name, "commits") != 0)
                {
                    int id_to_find = 0;
                    sscanf(entry3->d_name, "commits%d", &id_to_find);
                    if (id == id_to_find)
                    {
                        flag = 0;
                        char dirname[MAX_FILENAME_LENGTH];
                        nuller(dirname);
                        sprintf(dirname, ".monster/commits%d/", id);
                        DIR *dir2 = opendir(dirname);
                        struct dirent *entry2;
                        while ((entry2 = readdir(dir2)) != NULL)
                        {
                            FILE *file1 = fopen(".monster/staged", "r");
                            char line[MAX_LINE_LENGTH];
                            while (fgets(line, sizeof(line), file1) != NULL)
                            {
                                line[strlen(line) - 1] = '\0';
                                char NAME[MAX_FILENAME_LENGTH];
                                int start = 0;
                                for (int i = strlen(line) - 1; i >= 0; i--)
                                {
                                    if (line[i] == '/')
                                    {
                                        start = i + 1;
                                        break;
                                    }
                                }
                                for (int i = start; i < strlen(line); i++)
                                {
                                    NAME[i - start] = line[i];
                                }
                                NAME[strlen(line) - start] = '\0';
                                if (strcmp(entry2->d_name, NAME) == 0)
                                {
                                    char filename[MAX_FILENAME_LENGTH];
                                    nuller(filename);
                                    sprintf(filename, ".monster/commits%d/%s", id, entry2->d_name);
                                    FILE *file_src = fopen(filename, "r");
                                    FILE *file_dest = fopen(line, "w");
                                    char linedddd[MAX_LINE_LENGTH];
                                    while (fgets(linedddd, sizeof(linedddd), file_src) != NULL)
                                    {
                                        fputs(linedddd, file_dest);
                                    }
                                }
                            }
                        }
                        closedir(dir2);
                    }
                }
            }
            if (flag)
            {
                printf("Wrong commit id!\n");
                return 1;
            }
        }
        else
        {
            printf("Invalid inputs!\n");
            return 1;
        }
    }
    else if (strstr(argv[2], "HEAD") != NULL)
    {
        int number = 0;
        sscanf(argv[2], "HEAD-%d", &number);
        nuller(argv[2]);
        int id = commitcounter() - number - 1;
        sprintf(argv[2], "%d", id);
        return revert(3, argv);
    }
    else if (strcmp(argv[2], "-m") == 0 && strstr(argv[4], "HEAD") != NULL)
    {
        int number = 0;
        sscanf(argv[4], "HEAD-%d", &number);
        nuller(argv[4]);
        int id = commitcounter() - number - 1;
        sprintf(argv[4], "%d", id);
        return revert(5, argv);
    }
    else
    {
        printf("Invalid inputs!\n");
        return 1;
    }
}

int monster_tag(int argc, char *argv[])
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
    if (argc == 2)
    {
        FILE *file = fopen(".monster/tagname", "r");
        char *names[MAX_WORDS_COUNT_IN_A_COMMAND];
        for (int i = 0; i < MAX_WORDS_COUNT_IN_A_COMMAND; i++)
        {
            names[i] = (char *)malloc(1000);
        }
        int counter = 0;
        while (fgets(names[counter], sizeof(names[counter]), file) != NULL)
        {
            names[counter][strlen(names[counter]) - 1] = '\0';
            counter++;
        }
        for (int i = 0; i < counter; i++)
        {
            for (int j = i + 1; j < counter; j++)
            {
                if (names[i][0] > names[j][0])
                {
                    char *temp = names[i];
                    names[i] = names[j];
                    names[j] = temp;
                }
                if (names[i][0] == names[j][0] && names[i][1] > names[j][1])
                {
                    char *temp = names[i];
                    names[i] = names[j];
                    names[j] = temp;
                }
                if (names[i][0] == names[j][0] && names[i][1] == names[j][1] && names[i][2] > names[j][2])
                {
                    char *temp = names[i];
                    names[i] = names[j];
                    names[j] = temp;
                }
            }
        }

        for (int i = 0; i < counter; i++)
        {
            puts(names[i]);
        }
        return 0;
    }
    else if (strcmp(argv[2], "show") == 0)
    {
        FILE *file = fopen(".monster/taginformation", "r");
        char ans[MAX_LINE_LENGTH];
        int n;
        int flag = 0;
        sprintf(ans, "tag %s", argv[3]);
        for (int i = 0; i < tag_counter(); i++)
        {
            for (int j = 0; j < 5; j++)
            {
                char line[MAX_LINE_LENGTH];
                nuller(line);
                fgets(line, sizeof(line), file);
                line[strlen(line) - 1] = '\0';
                if (strcmp(line, ans) == 0)
                {
                    puts(line);
                    for (int i = 1; i < 5; i++)
                    {
                        char line2[MAX_LINE_LENGTH];
                        nuller(line2);
                        fgets(line2, sizeof(line2), file);
                        line2[strlen(line2) - 1] = '\0';
                        puts(line2);
                    }
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                break;
            }
        }
        if (flag == 0)
        {
            printf("Wrong tag name!\n");
            return 1;
        }
        return 0;
    }
    else if (strcmp(argv[2], "-a") == 0)
    {
        if (argc > 4 && strcmp(argv[4], "-m") == 0)
        {
            if (argv > 6 && strcmp(argv[6], "-c") == 0)
            {
                FILE *temp = fopen(".monster/tagname", "r");
                char templine[MAX_LINE_LENGTH];
                while (fgets(templine, sizeof(templine), temp) != NULL)
                {
                    templine[strlen(templine) - 1] = '\0';
                    if (strcmp(templine, argv[3]) == 0)
                    {
                        printf("Tag already exists!\n");
                        return 1;
                    }
                }
                fclose(temp);
                FILE *file = fopen(".monster/tagname", "a");
                fputs(argv[3], file);
                fprintf(file, "\n");
                fclose(file);
                file = fopen(".monster/taginformation", "a");
                fprintf(file, "tag %s\n", argv[3]);
                fprintf(file, "commit %s\n", argv[7]);
                char line[MAX_LINE_LENGTH];
                char line1[MAX_LINE_LENGTH];
                FILE *username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                line[strlen(line) - 1] = '\0';
                fclose(username);
                FILE *email = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
                fgets(line1, sizeof(line1), email);
                if (line1 == NULL)
                {
                    username = fopen(".monster/config_email", "r");
                    fgets(line1, sizeof(line1), email);
                }
                line1[strlen(line1) - 1] = '\0';
                fclose(email);
                fprintf(file, "Author: %s <%s>\n", line, line1);
                time_t rawtime;
                struct tm *info;
                time(&rawtime);
                info = localtime(&rawtime);
                fprintf(file, "Date: %s", asctime(info));
                fprintf(file, "Message: %s\n", argv[5]);
                fclose(file);
                printf("Tag %s is successfully made!\n", argv[3]);
                return 0;
            }
            else
            {
                FILE *tempp = fopen(".monster/tagname", "r");
                char templine[MAX_LINE_LENGTH];
                while (fgets(templine, sizeof(templine), tempp) != NULL)
                {
                    templine[strlen(templine) - 1] = '\0';
                    if (strcmp(templine, argv[3]) == 0)
                    {
                        printf("Tag already exists!\n");
                        return 1;
                    }
                }
                fclose(tempp);
                FILE *file = fopen(".monster/tagname", "a");
                fputs(argv[3], file);
                fprintf(file, "\n");
                fclose(file);
                file = fopen(".monster/taginformation", "a");
                fprintf(file, "tag %s\n", argv[3]);
                FILE *temp = fopen(".monster/myid", "r");
                char l[MAX_LINE_LENGTH];
                fgets(l, sizeof(l), temp);
                l[strlen(l) - 1] = '\0';
                fprintf(file, "commit %d", atoi(l));
                char line[MAX_LINE_LENGTH];
                char line1[MAX_LINE_LENGTH];
                FILE *username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                line[strlen(line) - 1] = '\0';
                fclose(username);
                FILE *email = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
                fgets(line1, sizeof(line1), email);
                if (line1 == NULL)
                {
                    username = fopen(".monster/config_email", "r");
                    fgets(line1, sizeof(line1), email);
                }
                line1[strlen(line1) - 1] = '\0';
                fclose(email);
                fprintf(file, "Author: %s <%s>\n", line, line1);
                time_t rawtime;
                struct tm *info;
                time(&rawtime);
                info = localtime(&rawtime);
                fprintf(file, "Date: %s", asctime(info));
                fprintf(file, "Message: %s\n", argv[5]);
                fclose(file);
                printf("Tag %s is successfully made!\n", argv[3]);
                return 0;
            }
        }
        else
        {
            if (argc > 4 && strcmp(argv[4], "-c") == 0)
            {
                FILE *tempp = fopen(".monster/tagname", "r");
                char templine[MAX_LINE_LENGTH];
                while (fgets(templine, sizeof(templine), tempp) != NULL)
                {
                    templine[strlen(templine) - 1] = '\0';
                    if (strcmp(templine, argv[3]) == 0)
                    {
                        printf("Tag already exists!\n");
                        return 1;
                    }
                }
                fclose(tempp);
                FILE *file = fopen(".monster/tagname", "a");
                fputs(argv[3], file);
                fprintf(file, "\n");
                fclose(file);
                file = fopen(".monster/taginformation", "a");
                fprintf(file, "tag %s\n", argv[3]);
                fprintf(file, "commit %s\n", argv[5]);
                char line[MAX_LINE_LENGTH];
                char line1[MAX_LINE_LENGTH];
                FILE *username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                line[strlen(line) - 1] = '\0';
                fclose(username);
                FILE *email = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
                fgets(line1, sizeof(line1), email);
                if (line1 == NULL)
                {
                    username = fopen(".monster/config_email", "r");
                    fgets(line1, sizeof(line1), email);
                }
                line1[strlen(line1) - 1] = '\0';
                fclose(email);
                fprintf(file, "Author: %s <%s>\n", line, line1);
                time_t rawtime;
                struct tm *info;
                time(&rawtime);
                info = localtime(&rawtime);
                fprintf(file, "Date: %s", asctime(info));
                fprintf(file, "Message: [empty]\n");
                fclose(file);
                printf("Tag %s is successfully made!\n", argv[3]);
                return 0;
            }
            else
            {
                FILE *tempp = fopen(".monster/tagname", "r");
                char templine[MAX_LINE_LENGTH];
                while (fgets(templine, sizeof(templine), tempp) != NULL)
                {
                    templine[strlen(templine) - 1] = '\0';
                    if (strcmp(templine, argv[3]) == 0)
                    {
                        printf("Tag already exists!\n");
                        return 1;
                    }
                }
                fclose(tempp);
                FILE *file = fopen(".monster/tagname", "a");
                fputs(argv[3], file);
                fprintf(file, "\n");
                fclose(file);
                file = fopen(".monster/taginformation", "a");
                fprintf(file, "tag %s\n", argv[3]);
                FILE *temp = fopen(".monster/myid", "r");
                char l[MAX_LINE_LENGTH];
                fgets(l, sizeof(l), temp);
                l[strlen(l)] = '\0';
                fprintf(file, "commit %d\n", atoi(l));
                char line[MAX_LINE_LENGTH];
                char line1[MAX_LINE_LENGTH];
                FILE *username = fopen("/home/mr_nakhjavani/Documents/global_name", "r");
                fgets(line, sizeof(line), username);
                if (line == NULL)
                {
                    username = fopen(".monster/config_username", "r");
                    fgets(line, sizeof(line), username);
                }
                line[strlen(line) - 1] = '\0';
                fclose(username);
                FILE *email = fopen("/home/mr_nakhjavani/Documents/global_email", "r");
                fgets(line1, sizeof(line1), email);
                if (line1 == NULL)
                {
                    username = fopen(".monster/config_email", "r");
                    fgets(line1, sizeof(line1), email);
                }
                line1[strlen(line1) - 1] = '\0';
                fclose(email);
                fprintf(file, "Author: %s <%s>\n", line, line1);
                time_t rawtime;
                struct tm *info;
                time(&rawtime);
                info = localtime(&rawtime);
                fprintf(file, "Date: %s", asctime(info));
                fprintf(file, "Message: [empty]\n");
                fclose(file);
                printf("Tag %s is successfully made!\n", argv[3]);
                return 0;
            }
        }
    }
    else
    {
        printf("Invalid inputs!\n");
        return 1;
    }
}

int grerp(int argc, char *argv[])
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
    if (argc > 6 && (strcmp(argv[6], "-c") == 0))
    {
        if (argc > 8 && (strcmp(argv[8], "-n") == 0))
        {
            char name[MAX_FILENAME_LENGTH];
            int start = 0;
            for (int i = strlen(argv[3]) - 1; i >= 0; i--)
            {
                if (argv[3][i] == '/')
                {
                    start = i + 1;
                    break;
                }
            }
            for (int i = start; i < strlen(argv[3]); i++)
            {
                name[i - start] = argv[3][i];
            }
            name[strlen(argv[3]) - start] = '\0';
            int commit_id = atoi(argv[7]);
            char mama[MAX_FILENAME_LENGTH];
            sprintf(mama, ".monster/commits%d/%s", commit_id, name);
            int lconuter = 0;
            FILE *file = fopen(mama, "r");
            char line[MAX_LINE_LENGTH];
            char *tokens[MAX_WORDS_COUNT_IN_A_COMMAND];
            int flag = 0;
            int color[100];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                for (int i = 0; i < 100; i++)
                {
                    color[i] = 0;
                }
                lconuter++;
                flag = 0;
                line[strlen(line) - 1] = '\0';
                tokens[0] = strtok(line, " ");
                int counter = 0;
                while (tokens[counter] != NULL)
                {
                    counter++;
                    tokens[counter] = strtok(NULL, " ");
                }
                for (int i = 0; i < counter; i++)
                {
                    if (strcmp(tokens[i], argv[5]) == 0)
                    {
                        flag = 1;
                        color[i] = 1;
                    }
                }
                if (flag)
                {
                    for (int i = 0; i < counter; i++)
                    {
                        if (i == 0 && color[i] == 0)
                        {
                            printf("%d %s ", lconuter, tokens[i]);
                        }
                        if (color[i] == 1 && i == 0)
                        {
                            printf("%d ", lconuter);
                            red();
                            printf("%s ", tokens[i]);
                            black();
                        }
                        if (color[i] == 0 && i != 0)
                        {
                            printf("%s ", tokens[i]);
                        }
                        if (color[i] == 1 && i != 0)
                        {
                            red();
                            printf("%s ", tokens[i]);
                            black();
                        }
                    }
                    printf("\n");
                }
            }
            return 0;
        }
        else
        {
            char name[MAX_FILENAME_LENGTH];
            int start = 0;
            for (int i = strlen(argv[3]) - 1; i >= 0; i--)
            {
                if (argv[3][i] == '/')
                {
                    start = i + 1;
                    break;
                }
            }
            for (int i = start; i < strlen(argv[3]); i++)
            {
                name[i - start] = argv[3][i];
            }
            int commit_id = atoi(argv[7]);
            char mama[MAX_FILENAME_LENGTH];
            sprintf(mama, ".monster/commits%d/%s", commit_id, name);
            int lconuter = 0;
            FILE *file = fopen(mama, "r");
            char line[MAX_LINE_LENGTH];
            char *tokens[MAX_WORDS_COUNT_IN_A_COMMAND];
            int flag = 0;
            int color[100];
            while (fgets(line, sizeof(line), file) != NULL)
            {
                for (int i = 0; i < 100; i++)
                {
                    color[i] = 0;
                }
                lconuter++;
                flag = 0;
                line[strlen(line) - 1] = '\0';
                tokens[0] = strtok(line, " ");
                int counter = 0;
                while (tokens[counter] != NULL)
                {
                    counter++;
                    tokens[counter] = strtok(NULL, " ");
                }
                for (int i = 0; i < counter; i++)
                {
                    if (strcmp(tokens[i], argv[5]) == 0)
                    {
                        flag = 1;
                        color[i] = 1;
                    }
                }
                if (flag)
                {
                    for (int i = 0; i < counter; i++)
                    {
                        if (color[i] == 0)
                        {
                            printf("%s ", tokens[i]);
                        }
                        if (color[i] == 1)
                        {
                            red();
                            printf("%s ", tokens[i]);
                            black();
                        }
                    }
                    printf("\n");
                }
            }
            return 0;
        }
    }
    else if (argc > 6 && strcmp(argv[6], "-n") == 0)
    {
        int lconuter = 0;
        FILE *file = fopen(argv[3], "r");
        char line[MAX_LINE_LENGTH];
        char *tokens[MAX_WORDS_COUNT_IN_A_COMMAND];
        int flag = 0;
        int color[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            for (int i = 0; i < 100; i++)
            {
                color[i] = 0;
            }
            lconuter++;
            flag = 0;
            line[strlen(line) - 1] = '\0';
            tokens[0] = strtok(line, " ");
            int counter = 0;
            while (tokens[counter] != NULL)
            {
                counter++;
                tokens[counter] = strtok(NULL, " ");
            }
            for (int i = 0; i < counter; i++)
            {
                if (strcmp(tokens[i], argv[5]) == 0)
                {
                    flag = 1;
                    color[i] = 1;
                }
            }
            if (flag)
            {
                for (int i = 0; i < counter; i++)
                {
                    if (i == 0 && color[i] == 0)
                    {
                        printf("%d %s ", lconuter, tokens[i]);
                    }
                    if (color[i] == 1 && i == 0)
                    {
                        printf("%d ", lconuter);
                        red();
                        printf("%s ", tokens[i]);
                        black();
                    }
                    if (color[i] == 0 && i != 0)
                    {
                        printf("%s ", tokens[i]);
                    }
                    if (color[i] == 1 && i != 0)
                    {
                        red();
                        printf("%s ", tokens[i]);
                        black();
                    }
                }
                printf("\n");
            }
        }
        return 0;
    }
    if (argc == 6)
    {
        FILE *file = fopen(argv[3], "r");
        char line[MAX_LINE_LENGTH];
        char *tokens[MAX_WORDS_COUNT_IN_A_COMMAND];
        int flag = 0;
        int color[100];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            for (int i = 0; i < 100; i++)
            {
                color[i] = 0;
            }
            flag = 0;
            line[strlen(line) - 1] = '\0';
            tokens[0] = strtok(line, " ");
            int counter = 0;
            while (tokens[counter] != NULL)
            {
                counter++;
                tokens[counter] = strtok(NULL, " ");
            }
            for (int i = 0; i < counter; i++)
            {
                if (strcmp(tokens[i], argv[5]) == 0)
                {
                    flag = 1;
                    color[i] = 1;
                }
            }
            if (flag)
            {
                for (int i = 0; i < counter; i++)
                {
                    if (color[i] == 0)
                    {
                        printf("%s ", tokens[i]);
                    }
                    if (color[i] == 1)
                    {
                        red();
                        printf("%s ", tokens[i]);
                        black();
                    }
                }
                printf("\n");
            }
        }
    }
    return 0;
}

int diff(int argc, char *argv[])
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
    
}

int pre_commit(int argc, char *argv[])
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
    if (argc == 4 && strcmp(argv[2], "hooks") == 0 && strcmp(argv[3], "list") == 0)
    {
        FILE *file = fopen(".monster/hooklist", "r");
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            puts(line);
        }
        fclose(file);
    }
    else if (argc == 4 && strcmp(argv[2], "applied") == 0 && strcmp(argv[3], "hooks") == 0)
    {
        DIR *dir = opendir(".monster/appliedhooks");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                puts(entry->d_name);
            }
        }
        closedir(dir);
    }
    else if (argc == 5 && strcmp(argv[2], "add") == 0 && strcmp(argv[3], "hook") == 0)
    {
        FILE *file = fopen(".monster/hooklist", "r");
        char line[MAX_LINE_LENGTH];
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(argv[4], line) == 0)
            {
                flag = 1;
                break;
            }
        }
        fclose(file);
        if (flag)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            chdir(".monster/appliedhooks");
            file = fopen(argv[4], "w");
            fclose(file);
            chdir(cwd);
            printf("Hook %s succefully added!\n", argv[4]);
            return 0;
        }
        printf("Wrong hook-id!\n");
        return 1;
    }
    else if (argc == 5 && strcmp(argv[2], "remove") == 0 && strcmp(argv[3], "hook") == 0)
    {
        FILE *file = fopen(".monster/hooklist", "r");
        char line[MAX_LINE_LENGTH];
        int flag = 0;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (strcmp(argv[4], line) == 0)
            {
                flag = 1;
                break;
            }
        }
        fclose(file);
        if (flag)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            chdir(".monster/appliedhooks");
            remove(argv[4]);
            chdir(cwd);
            printf("Hook %s succefully removed!\n", argv[4]);
            return 0;
        }
        printf("Wrong hook-id!\n");
        return 1;
    }
    else if (argc == 2)
    {
        DIR *dir = opendir(".monster/added");
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                printf("%s\n", entry->d_name);
                char input[MAX_FILENAME_LENGTH];
                sprintf(input, ".monster/added/%s", entry->d_name);
                DIR *dir2 = opendir(".monster/appliedhooks");
                struct dirent *entry2;
                while ((entry2 = readdir(dir2)) != NULL)
                {
                    if (strcmp(entry2->d_name, "file-size-check") == 0)
                        filesizecheck(input);
                    if (strcmp(entry2->d_name, "todo-check") == 0)
                        todocheck(input);
                    if (strcmp(entry2->d_name, "balance-braces") == 0)
                        balancebraces(input);
                    if (strcmp(entry2->d_name, "character-limit") == 0)
                        characterlimit(input);
                }
            }
        }
    }
    else if (argc > 3 && strcmp(argv[2], "-f") == 0)
    {
        for (int i = 3; i < argc; i++)
        {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL)
            {
                printf("File doesn't eists!\n");
                return 1;
            }
            fclose(file);
            if (check_if_file_is_unstaged(argv[i]) != 'S')
            {
                printf("File is not staged!\n");
                return 1;
            }
            printf("%s\n", argv[i]);
            DIR *dir2 = opendir(".monster/appliedhooks");
            struct dirent *entry2;
            while ((entry2 = readdir(dir2)) != NULL)
            {
                if (strcmp(entry2->d_name, "file-size-check") == 0)
                    filesizecheck(argv[i]);
                if (strcmp(entry2->d_name, "todo-check") == 0)
                    todocheck(argv[i]);
                if (strcmp(entry2->d_name, "balance-braces") == 0)
                    balancebraces(argv[i]);
                if (strcmp(entry2->d_name, "character-limit") == 0)
                    characterlimit(argv[i]);
            }
        }
    }
    else
    {
        printf("Invalid inputs!\n");
        return 1;
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
    if (strcmp(argv[1], "revert") == 0)
        return revert(argc, argv);
    if (strcmp(argv[1], "tag") == 0)
        return monster_tag(argc, argv);
    if (strcmp(argv[1], "grep") == 0)
        return grerp(argc, argv);
    if (strcmp(argv[1], "diff") == 0)
        return diff(argc, argv);
    if(strcmp(argv[1],"pre-commit")==0)
        return pre_commit(argc,argv);
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
                if (strcmp(words[1], "revert") == 0)
                    return revert(count_of_words, words);
                if (strcmp(words[1], "tag") == 0)
                    return monster_tag(count_of_words, words);
                if (strcmp(words[1], "grep") == 0)
                    return grerp(count_of_words, words);
                if (strcmp(words[1], "diff") == 0)
                    return diff(count_of_words, words);
                if(strcmp(words[1],"pre-commit")==0)
                    return pre_commit(count_of_words,words);
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
                if (strcmp(words[1], "revert") == 0)
                    return revert(count_of_words, words);
                if (strcmp(words[1], "tag") == 0)
                    return monster_tag(count_of_words, words);
                if (strcmp(words[1], "grep") == 0)
                    return grerp(count_of_words, words);
                if (strcmp(words[1], "diff") == 0)
                    return diff(count_of_words, words);
                if(strcmp(words[1],"pre-commit")==0)
                    return pre_commit(count_of_words,words);
            }
        }
        printf("Invalid command!\n");
        return 1;
    }
    printf("Invalid command\n");
    return 1;
}