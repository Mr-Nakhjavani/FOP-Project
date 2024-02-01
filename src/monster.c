#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_FILENAME_LENGTH 1000
#define MAX_COMMIT_MESSAGE_LENGTH 2000
#define MAX_LINE_LENGTH 1000
#define MAX_MESSAGE_LENGTH 1000
#define MAX_USERNAME_EMAIL_LENGTH 500
#define MAX_WORDS_COUNT_IN_A_COMMAND 10

int isDirectory(const char *path);
void nuller(char input[]);
bool config_flag();
bool init_flag();
int init(int argc,char* argv[]);
int config(int argc,char* argv[]);
int alias(int argc,char* argv[]);
int add(int argc,char* argv[]);
int reset(int argc,char* argv[]);
int copy(char* src,char* dest);
int add_file(char* path);
void add_file_or_folder(char *input);
int reset(int argc,char* argv[]);
int status(int argc,char* argv[]);
void reset_file(char* path);
void reset_file_or_directory(char input[]);

void nuller(char input[]){
    for(int i=0;i<strlen(input);i++){
        input[i]='\0';
    }
}

int isDirectory(const char *path){
   struct stat statbuf;
   if (stat(path, &statbuf) != 0) return 0;
   return S_ISDIR(statbuf.st_mode);
}

bool config_flag(){
    FILE* config_username=fopen(".monster/config_username.txt","r");
    FILE* config_email=fopen(".monster/config_email.txt","r");
    if(config_username==NULL) return false;
    if(config_email==NULL) return false;
    char temp[MAX_LINE_LENGTH];
    nuller(temp);
    if(fgets(temp,sizeof(temp),config_username)==NULL) return false;
    nuller(temp);
    if(fgets(temp,sizeof(temp),config_email)==NULL) return false;
    fclose(config_username);
    fclose(config_email);
    return true;
}

bool init_flag(){
    struct dirent *entry;
    DIR *dir = opendir(".");
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".monster") == 0){
            return true;
        }
    }
    closedir(dir);
    return false;
}

int init(int argc,char* argv[]){
    bool exists = false;
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (dir == NULL) {
        printf("Error opening current directory\n");
        return 1;
    }
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;
    do{
        DIR *dir = opendir(".");
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".monster") == 0){
                exists=true;
            }
        }
        closedir(dir);
        getcwd(tmp_cwd, sizeof(tmp_cwd));
        if(strcmp(tmp_cwd, "/") != 0)  chdir(".."); 
    }while(strcmp(tmp_cwd, "/") != 0);
    chdir(cwd);
    closedir(dir);
    if(!exists){
        if (mkdir(".monster", 0755) != 0) return 1;
        printf("Repository created succesfully\n");
        return 0;
    }else {
        printf("Monster repository has already initialized\n");
        return 1;
    }
}

int config(int argc,char* argv[]){
    if(!init_flag()){
        printf("First you have to create a repository\n");
        return 1;
    }
    if(strcmp(argv[2],"-global")==0){
        if(strstr(argv[3],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[3],"user.name")==0){
                FILE* file=fopen("/home/mr_nakhjavani/Desktop/global_name.txt","w");
                fprintf(file,"USERNAME: %s\n",argv[4]);
                fclose(file);
                char cwd[1024];
                if(getcwd(cwd, sizeof(cwd)) == NULL) return 1;
                char tmp_cwd[1024];
                bool exists = false;
                struct dirent *entry;
                do{
                    DIR *dir = opendir(".");
                    while ((entry = readdir(dir)) != NULL) {
                        if (strcmp(entry->d_name, ".monster") == 0){
                            FILE* temp=fopen(".monster/config_username.txt","w");
                            fprintf(temp,"USERNAME: %s\n",argv[4]);
                            fclose(temp);
                        }
                    }
                    closedir(dir);
                    getcwd(tmp_cwd, sizeof(tmp_cwd));
                    if(strcmp(tmp_cwd, "/") != 0)  chdir(".."); 
                }while(strcmp(tmp_cwd, "/") != 0);
                printf("Your name is regesterd succesfully!\n");
                chdir(cwd);
                return 0;
            }
            else if(strcmp(argv[3],"user.email")==0){
                FILE* file=fopen("/home/mr_nakhjavani/Desktop/global_email.txt","w");
                fprintf(file,"USERNAME: %s\n",argv[4]);
                fclose(file);
                char cwd[1024];
                if(getcwd(cwd, sizeof(cwd)) == NULL) return 1;
                char tmp_cwd[1024];
                bool exists = false;
                struct dirent *entry;
                do{
                    DIR *dir = opendir(".");
                    while ((entry = readdir(dir)) != NULL) {
                        if (strcmp(entry->d_name, ".monster") == 0){
                            FILE* temp=fopen(".monster/config_email.txt","w");
                            fprintf(temp,"EMAIL: %s\n",argv[4]);
                            fclose(temp);
                        }
                    }
                    closedir(dir);
                    getcwd(tmp_cwd, sizeof(tmp_cwd));
                    if(strcmp(tmp_cwd, "/") != 0)  chdir(".."); 
                }while(strcmp(tmp_cwd, "/") != 0);
                printf("Your email is registerd succesfully!\n");
                chdir(cwd);
                return 0;
            }
            else{
                printf("Invalid command\n");
                return 1;
            }
        }        
    }
    else{
        if(strstr(argv[2],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[2],"user.name")==0){
                FILE* config_username=fopen(".monster/config_username.txt","w");
                fprintf(config_username,"USERNAME: %s\n",argv[3]);
                fclose(config_username);
                printf("Your name is regesterd succesfully!\n");
            }
            else if(strcmp(argv[2],"user.email")==0){
                FILE* config_email=fopen(".monster/config_email.txt","w");
                fprintf(config_email,"EMAIL: %s\n",argv[3]);
                fclose(config_email);
                printf("Your email is registerd succesfully!\n");
            }
            else{
                printf("Invalid command\n");
                return 1;
            }
        }
    }
    if(mkdir(".monster/commits", 0755) != 0) return 1;
    if(mkdir(".monster/added", 0755) != 0) return 1;
    if(mkdir(".monster/alias", 0755) != 0) return 1;
    if(mkdir(".monster/branches", 0755) != 0) return 1;
    FILE* file=fopen(".monster/commits.txt","w");
    fclose(file);
    file=fopen(".monster/shortcuts.txt","w");
    fclose(file);
    file=fopen(".monster/staged.txt","w");
    return 0;
}

int alias(int argc,char* argv[]){
    if(strcmp(argv[2],"-global")==0){
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        sscanf(argv[3],"alias.%s", temp);
        strcpy(filename,".monster/alias/");
        strcat(filename,temp);
        strcat(filename,".txt");
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) == NULL) return 1;
        char tmp_cwd[1024];
        bool exists = false;
        struct dirent *entry;
        do{
            DIR *dir = opendir(".");
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".monster") == 0){
                    FILE* file=fopen(filename,"w");
                    fputs(argv[3],file);
                    printf("Your link is created succesfully!\n");
                }
            }
            closedir(dir);
            getcwd(tmp_cwd, sizeof(tmp_cwd));
            if(strcmp(tmp_cwd, "/") != 0)  chdir(".."); 
        }while(strcmp(tmp_cwd, "/") != 0);
        chdir(cwd);
        return 0;

    }
    else if(strstr(argv[2],"alias.")!=NULL){
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        strcpy(filename,".monster/alias/");
        sscanf(argv[2],"alias.%s", temp);
        strcat(filename,temp);
        strcat(filename,".txt");
        FILE* file=fopen(filename,"w");
        fputs(argv[3],file);
        printf("Your link is created succesfully!\n");
        return 0;
    }
    else{
        printf("Invalid command\n");
        return 1;
    }
}

int add_file(char* path){
    FILE* file = fopen(".monster/staged.txt", "r");
    if (file == NULL) return 1;
    FILE* file_to_add = fopen(path,"r");
    if(file_to_add==NULL){
        printf("File doesn't exists\n");
        return 1;
    }
    int start = 0;
    for(int i=strlen(path)-1;i>=0;i--){
        if(*(path+i)=='/'){
            start=i+1;
            break;
        }
    }
    char file_name[MAX_FILENAME_LENGTH];
    strcpy(file_name,".monster/added/");
    for(int i=start+15;i<strlen(path)+15;i++){
        file_name[i-start]=*(path+i-15); 
    }
    file_name[15+strlen(path)]='\0';
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(path, line) == 0){
            printf("File is already added\n");
            return 0;
        }
    }
    fclose(file);
    file=fopen(".monster/staged.txt", "a");
    fprintf(file,"%s\n",path);
    fclose(file);
    file=fopen(file_name,"w");
    while (fgets(line,sizeof(line),file_to_add)!=NULL){
        line[strlen(line) - 1] = '\0';
        fputs(line,file);
    }
    printf("file %s added to stage succesfully!\n",path);
    fclose(file);
    fclose(file_to_add);
    return 0;
}

void add_file_or_folder(char input[]){
    if(!isDirectory(input)){
            add_file(input);
    }
    else if(isDirectory(input)){
        DIR* dir=opendir(input);
        struct dirent* entry;
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                char path[MAX_FILENAME_LENGTH];
                sprintf(path,"%s/%s",input,entry->d_name);
                if(isDirectory(path)){
                    char * temp=input;
                    input=path;
                    add_file_or_folder(input);
                    input=temp;
                }
                if(!isDirectory(path)){
                    add_file(path);
                }
            }
        }
    }
}

int add(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/global_name.txt","r");
        FILE* file2=fopen("/home/mr_nakhjavani/global_email.txt","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc < 3) {
        printf("Please specify a file\n");
        return 1;
    }
    if(strcmp(argv[2],"-f")==0){
        for(int i=3;i<argc;i++){
            add_file_or_folder(argv[i]);
        }
        return 0;
    }
    else{
        for(int i=2;i<argc;i++){
            add_file_or_folder(argv[i]);
        }
        return 0;
    }
}

int reset(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/global_name.txt","r");
        FILE* file2=fopen("/home/mr_nakhjavani/global_email.txt","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if(strcmp(argv[2],"-undo")==0){

    }
    else{
        for(int i=2;i<argc;i++) reset_file_or_directory(argv[i]);
        return 0;
    }
}

void reset_file_or_directory(char input[]){
    if(!isDirectory(input)){
        reset_file(input);
    }
    else if(isDirectory(input)){
        DIR* dir=opendir(input);
        struct dirent* entry;
        while((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                char path[MAX_FILENAME_LENGTH];
                sprintf(path,"%s/%s",input,entry->d_name);
                if(isDirectory(path)){
                    char * temp=input;
                    input=path;
                    reset_file_or_directory(input);
                    input=temp;
                }
                if(!isDirectory(path)){
                    reset_file(path);
                }
            }
        }
    }
}

void reset_file(char* path){
    FILE* file=fopen(".monster/staged.txt","r");
    char line[MAX_LINE_LENGTH];
    int flag=0;
    while (fgets(line,sizeof(line),file)){
        if(strcmp(line,path)==0){
            flag=1;
            break;
        }
    }
    if(flag){
        int start=0;
        char file_name[MAX_FILENAME_LENGTH];
        for(int i=strlen(path)-1;i>=0;i--){
            if(path[i]=='/') start=i+1;
        }
        for(int i=start;i<strlen(path);i++){
            file_name[i-start]=path[i];
        }
        file_name[strlen(path)-start]='\0';
        char address[MAX_FILENAME_LENGTH];
        sprintf(address,".monster/added/%s",file_name);
        DIR* dir=opendir(".monster/added/");
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL){
            if(strcmp(entry->d_name,file_name)==0){
                remove(address);
            }
        }
        printf("File %s is succefully unstaged!\n",path);
        return;
    }
    printf("File %s is not added in stage mode!\n",path);
    return;
}
int status(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/global_name.txt","r");
        FILE* file2=fopen("/home/mr_nakhjavani/global_email.txt","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }


}
int main (int argc,char* argv[]){
    if (argc < 2) {
        printf("Please enter a valid command\n");
        return 1;
    }
    if(strcmp(argv[1],"config")==0) return config(argc,argv);
    if(strcmp(argv[1],"init")==0) return init(argc,argv);
    if(strcmp(argv[1],"add")==0) return add(argc,argv);
    if(strcmp(argv[1],"reset")==0) return reset(argc,argv);
    if(strcmp(argv[1],"status")==0) return status(argc,argv);
    if(init_flag()){
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;
        chdir(".monster/alias");
        struct dirent *entry;
        DIR *dir = opendir(".");
        strcat(argv[1],".txt");
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, argv[1]) == 0){
                FILE* file=fopen(argv[1],"r");
                char line[MAX_LINE_LENGTH];
                fgets(line,sizeof(line),file);
                line[strlen(line)]='\0';
                char* words[MAX_WORDS_COUNT_IN_A_COMMAND];
                words[0]=strtok(line," ");
                int count_of_words=0;
                while(words[count_of_words]!=NULL){
                    count_of_words++;
                    words[count_of_words] = strtok(NULL," ");
                }
                chdir(cwd);
                if(strcmp(words[1],"config")==0) return config(count_of_words,words);
                if(strcmp(words[1],"init")==0) return init(count_of_words,words);
                if(strcmp(words[1],"add")==0) return add(count_of_words,words);
                if(strcmp(words[1],"reset")==0) return reset(count_of_words,words);
                if(strcmp(argv[1],"status")==0) return status(count_of_words,words);
                printf("Invalid command\n");
                return 1;
            }
        }
    }
    printf("Invalid command\n");
    return 1;
}

// do{
//     DIR *dir = opendir(".");
//     if (dir == NULL) {
//         printf("Error opening current directory\n");
//         return 1;
//     }
//     while ((entry = readdir(dir)) != NULL) {
//         if (strcmp(entry->d_name, ".monster") == 0){
//             exists = true;
//             printf("%s\n",tmp_cwd);
//         }
//     }
//     closedir(dir);
//     if(getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
//     if(strcmp(tmp_cwd, "/") != 0) {
//         if (chdir("..") != 0){
//             return 1;
//         }
//     }
// }while(strcmp(tmp_cwd, "/") != 0);