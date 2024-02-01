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

void nuller(char input[]);
bool config_flag();
bool init_flag();
int init(int argc,char* argv[]);
int config(int argc,char* argv[]);
int alias(int argc,char* argv[]);
int add(int argc,char* argv[]);
int reset(int argc,char* argv[]);

void nuller(char input[]){
    for(int i=0;i<strlen(input);i++){
        input[i]='\0';
    }
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
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL) return 1;
    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;
    do{
        DIR *dir = opendir(".");
        if (dir == NULL) {
            printf("Error opening current directory\n");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".monster") == 0){
                exists = true;
            }
        }
        closedir(dir);
        if(getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;
        if(strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0){
                return 1;
            }
        }
    }while(strcmp(tmp_cwd, "/") != 0);
    if(chdir(cwd) != 0) return 1;
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
        printf("First you need to create a repository\n");
        return 1;
    }
    FILE* config_username=fopen(".monster/config_username.txt","w");
    FILE* config_email=fopen(".monster/config_email.txt","w");
    if(strcmp(argv[2],"-global")==0){
        if(strstr(argv[3],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[3],"user.name")==0){
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
                chdir(cwd);
            }
            if(strcmp(argv[3],"user.email")==0){
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
                chdir(cwd);
            }
            printf("Invalid command\n");
            return 1;
        }        
    }
    else{
        if(strstr(argv[2],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[2],"user.name")==0){
                fprintf(config_username,"USERNAME: %s\n",argv[3]);
                fclose(config_username);

            }
            if(strcmp(argv[2],"user.email")==0){
                fprintf(config_email,"EMAIL: %s\n",argv[3]);
                fclose(config_email);
            }
            printf("Invalid command\n");
            return 1;
        }
    }
    if(mkdir(".monster/commits", 0755) != 0) return 1;
    if(mkdir(".monster/added", 0755) != 0) return 1;
    FILE* file=fopen(".monster/commits.txt","w");
    fclose(file);
    file=fopen(".monster/shortcuts.txt","w");
    fclose(file);
    return 0;
}

int alias(int argc,char* argv[]){

}

int add(int argc,char* argv[]){

}

int reset(int argc,char* argv[]){

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
    printf("Invalid command\n");
    return 1;
}