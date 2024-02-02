#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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
int init(int argc,char* argv[]);
int config(int argc,char* argv[]);
int alias(int argc,char* argv[]);
int add(int argc,char* argv[]);
int add_file(char* path);
void add_file_or_folder(char *input);
int reset(int argc,char* argv[]);
void reset_file_or_directory(char input[]);
void reset_file(char* path);
bool check_if_file_is_unstaged(char* addres);
char status_mode(char* path);
void status_file_or_directory(char input[]);
void status_file(char* path);
int status(int argc,char* argv[]);
int commit(int argc,char* argv[]);

void nuller(char input[]){
    for(int i=0;i<strlen(input);i++){
        input[i]='\0';
    }
}

bool check_if_file_is_unstaged(char* addres){
    char file_name[MAX_FILENAME_LENGTH];
    char line[MAX_LINE_LENGTH];
    int start=0;
    for(int i=strlen(addres)-1;i>=0;i--){
        if(addres[i]=='/'){
            start=i+1;
            break;
        }
    }
    for(int i=start;i<strlen(addres);i++){
        file_name[i-start]=addres[i];
    }
    file_name[strlen(addres)-start]='\0';
    DIR* dir=opendir(".monster/unstaged/");
    struct dirent* entry;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,file_name)==0){
            return true;
        }
    }
    return false;
}

int isDirectory(const char *path){
   struct stat statbuf;
   if (stat(path, &statbuf) != 0) return 0;
   return S_ISDIR(statbuf.st_mode);
}

bool config_flag(){
    FILE* config_username=fopen(".monster/config_username","r");
    FILE* config_email=fopen(".monster/config_email","r");
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
        if(mkdir(".monster/commits", 0755) != 0) return 1;
        if(mkdir(".monster/added", 0755) != 0) return 1;
        if(mkdir(".monster/alias", 0755) != 0) return 1;
        if(mkdir(".monster/branches", 0755) != 0) return 1;
        if(mkdir(".monster/unstaged", 0755) != 0) return 1;
        mkdir("/home/mr_nakhjavani/Documents/alias_global", 0755);
        FILE* file=fopen(".monster/commitsinformation","w");
        fclose(file);
        file=fopen(".monster/shortcuts","w");
        fclose(file);
        file=fopen(".monster/staged","w");
        return 0;
    }else {
        printf("Monster repository has already initialized\n");
        return 1;
    }
}

int config(int argc,char* argv[]){
    if(strcmp(argv[2],"-global")==0){
        if(strstr(argv[3],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[3],"user.name")==0){
                FILE* file=fopen("/home/mr_nakhjavani/Documents/global_name","w");
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
                            FILE* temp=fopen(".monster/config_username","w");
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
                FILE* file=fopen("/home/mr_nakhjavani/Documents/global_email","w");
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
                            FILE* temp=fopen(".monster/config_email","w");
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
        if(!init_flag()){
           printf("First you have to create a repository\n");
            return 1;
        }
        if(strstr(argv[2],"alias.")!=NULL){
            return alias(argc,argv);
        }
        else{
            if(strcmp(argv[2],"user.name")==0){
                FILE* config_username=fopen(".monster/config_username","w");
                fprintf(config_username,"USERNAME: %s\n",argv[3]);
                fclose(config_username);
                printf("Your name is regesterd succesfully!\n");
            }
            else if(strcmp(argv[2],"user.email")==0){
                FILE* config_email=fopen(".monster/config_email","w");
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
}

int alias(int argc,char* argv[]){
    if(strcmp(argv[2],"-global")==0){
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        sscanf(argv[3],"alias.%s", temp);
        sprintf(filename,"/home/mr_nakhjavani/Documents/alias_global/%s",temp);
        FILE* file=fopen(filename,"a");
        fputs(argv[4],file);
        printf("Your link is created succesfully!\n");
        return 0;

    }
    else if(strstr(argv[2],"alias.")!=NULL){
        char filename[MAX_FILENAME_LENGTH];
        char temp[MAX_FILENAME_LENGTH];
        nuller(temp);
        strcpy(filename,".monster/alias/");
        sscanf(argv[2],"alias.%s", temp);
        strcat(filename,temp);
        FILE* file=fopen(filename,"a");
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
    FILE* file = fopen(".monster/staged", "r");
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
    char real_file_name[MAX_FILENAME_LENGTH];
    strcpy(file_name,".monster/added/");
    for(int i=start+15;i<strlen(path)+15;i++){
        file_name[i-start]=*(path+i-15); 
        real_file_name[i-start-15]=path[i-15];
    }
    real_file_name[strlen(path)-start]='\0';
    file_name[15+strlen(path)]='\0';
    char unstaged[MAX_FILENAME_LENGTH];
    sprintf(unstaged,".monster/unstaged/%s",real_file_name);
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strlen(line) - 1] = '\0';
        if(strcmp(path, line) == 0){
            if(!check_if_file_is_unstaged(path)){
                printf("File %s is already added\n",path);
                return 0;
            }
        }
    }
    fclose(file);
    file=fopen(".monster/staged", "a");
    fprintf(file,"%s\n",path);
    fclose(file);
    file=fopen(file_name,"w");
    while (fgets(line,sizeof(line),file_to_add)!=NULL){
        // line[strlen(line) - 1] = '\0';
        fputs(line,file);
    }
    printf("file %s added to stage succesfully!\n",path);
    if(check_if_file_is_unstaged(path)) remove(unstaged);
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
                if(!isDirectory(path))  add_file(path);
            }
        }
    }
}

int add(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/Documents/global_name","r");
        FILE* file2=fopen("/home/mr_nakhjavani//Documents/global_email","r");
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
        for(int i=3;i<argc;i++) add_file_or_folder(argv[i]);
        return 0;
    }
    else if(strcmp(argv[2],"-n")==0){
        int flag=1;
        FILE* file=fopen(".monster/staged","r");
        char address[MAX_FILENAME_LENGTH];
        DIR* dir=opendir(".");
        struct dirent* entry;
            address[strlen(address)-1]='\0';
            while((entry = readdir(dir))!=NULL){
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,".monster")!=0 && isDirectory(entry->d_name)==0){
                printf("%s: ", entry->d_name);
                flag=0;
                while(fgets(address,sizeof(address),file)!=NULL){
                    address[strlen(address)-1]='\0';
                    char filename[MAX_FILENAME_LENGTH];
                    nuller(filename);
                    int start=0;
                    for(int i=strlen(address)-1;i>=0;i--){
                        if(address[i]=='/'){
                            start=i+1;
                            break;
                        }
                    }
                    for(int i=start;i<strlen(address);i++){
                        filename[i-start]=address[i];
                    }
                    filename[strlen(address)-start]='\0';
                    if(strcmp(filename,entry->d_name)==0){
                        if(!check_if_file_is_unstaged(address)) printf("STAGED\n");
                        else printf("NOT STAGED\n");
                    }
                }
                rewind(file);
            }
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,".monster")!=0 && isDirectory(entry->d_name)==1) printf("%s: IS A DIRECTORY!\n", entry->d_name);
        }
        if(flag){
            printf("There is no file or folder in this directory!\n");
            return 1;
        }
        return 0;
    }
    else{
        for(int i=2;i<argc;i++) add_file_or_folder(argv[i]);
        return 0;
    }
}

int reset(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/Documents/global_name","r");
        FILE* file2=fopen("/home/mr_nakhjavani/Documents/global_email","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if (argc < 3) {
        perror("please specify a file");
        return 1;
    }
    if(strcmp(argv[2],"-undo")==0){
        int counter=0;
        FILE* file=fopen(".monster/staged","r");
        char line[MAX_LINE_LENGTH];
        while (fgets(line,sizeof(line),file)){
            counter++;
        }
        for(int i=1;i<counter;i++){
            fgets(line,sizeof(line),file);
        }
        line[strlen(line)-1]='\0';
        reset_file(line);
        fclose(file);
        return 0;
    }
    else if(strcmp(argv[2],"-f")==0){
        for(int i=3;i<argc;i++) reset_file_or_directory(argv[i]);
        return 0;
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
    if(check_if_file_is_unstaged(path)){
        printf("File %s is already unstaged!\n",path);
        return;
    }
    FILE* file=fopen(".monster/staged","r");
    char line[MAX_LINE_LENGTH];
    int flag=0;
    while (fgets(line,sizeof(line),file)){
        line[strlen(line)-1]='\0';
        if(strcmp(line,path)==0){
            flag=1;
            break;
        }
    }
    fclose(file);
    if(flag){
        int start=0;
        char file_name[MAX_FILENAME_LENGTH];
        for(int i=strlen(path)-1;i>=0;i--){
            if(path[i]=='/'){
                start=i+1;
                break;
            }
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
            if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
                if(strcmp(entry->d_name,file_name)==0){
                    file = fopen(address,"r");
                    char file_name[MAX_FILENAME_LENGTH];
                    sprintf(file_name,".monster/unstaged/%s",entry->d_name);
                    FILE* file2=fopen(file_name,"w");
                    char line1[MAX_LINE_LENGTH];
                    nuller(line1);
                    while(fgets(line1,sizeof(line1),file)!=NULL){
                        // line1[strlen(line1)-1]='\0';
                        fputs(line1,file2);
                    }
                    fclose(file2);
                    fclose(file);
                    remove(address);
                    file=fopen(".monster/staged","a");
                    file2=fopen(".monster/ustaged","a");
                    while(fgets(line1,sizeof(line1),file)!=NULL){
                        line1[strlen(line1)-1]='\0';
                        if(strcmp(line1,entry->d_name)==0){
                            fputs(line1,file2);
                        }
                    }
                }
            }
        }
        printf("File %s is succefully unstaged!\n",path);
        return;
    }
    printf("File %s is not added to staging area!\n",path);
    return;
}

char status_mode(char* path){
    FILE* file1=fopen(path,"r");
    if(file1==NULL) return 'D';
    FILE* file2;
    char file_name[MAX_FILENAME_LENGTH];
    char line1[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    int start = 0;
    for(int i=strlen(path)-1;i>=0;i--){
        if(path[i]=='/'){
            start=i+1;
            break;
        }
    }
    strcpy(file_name,".monster/added/");
    for(int i=start;i<strlen(path);i++){
        file_name[i-start+15]=path[i];
    }
    file2=fopen(file_name,"r");
    int counter_line1=0;
    int counter_line2=0;
    while(fgets(line1,sizeof(line1),file1)!=NULL){
        counter_line1++;
    }
    rewind(file1);
    while(fgets(line2,sizeof(line2),file2)!=NULL){
        counter_line2++;
    }
    rewind(file2);
    if(counter_line1!=counter_line2) return 'M';
    while(fgets(line1,sizeof(line1),file1)!=NULL && fgets(line2,sizeof(line2),file2)!=NULL){
        if(strcmp(line1,line2)!=0) return 'M';
    }
    return 'A';
}

void status_file_or_directory(char input[]){
    if(!isDirectory(input)){
        status_file(input);
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
                    status_file_or_directory(input);
                    input=temp;
                }
                if(!isDirectory(path)){
                    status_file(path);
                }
            }
        }
    }
}

void status_file(char* path){
    if(!check_if_file_is_unstaged(path)){
            printf("File %s status: +%c\n", path, status_mode(path));
    }
    else printf("File %s status: -\n", path);
}

int status(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/Documents/global_name","r");
        FILE* file2=fopen("/home/mr_nakhjavani/Documents/global_email","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    DIR* dir=opendir(".");
    struct dirent* entry;
    while((entry = readdir(dir)) != NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0 &&strcmp(entry->d_name,".monster")!=0)   status_file_or_directory(entry->d_name);
    }
}

int commit(int argc,char* argv[]){
    if(!config_flag()){
        FILE* file1=fopen("/home/mr_nakhjavani/Documents/global_name","r");
        FILE* file2=fopen("/home/mr_nakhjavani/Documents/global_email","r");
        if(file1 == NULL || file2==NULL){
            printf("First you have to register your name and email!\n");
            return 1;
        }
    }
    if(argc>4){
        printf("If your message has space you should write it between double qoutes!\n");
        return 1;
    }
    if(argc<4){
        printf("Your commit must have a message!\n");
        return 1;
    }
    if(strlen(argv[3]) > 72){
        printf("Your commit message length shouldn't be more than 72 character!\n");
        return 1;
    }
    DIR* dir=opendir(".monster/added/");
    if(readdir(dir)==NULL){
        printf("No file to commit!\n");
        return 1;
    }
    struct dirent* entry;
    char file_name_dest[MAX_FILENAME_LENGTH];
    char file_name_src[MAX_FILENAME_LENGTH];
    while((entry=readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")!=0 && strcmp(entry->d_name,"..")!=0){
            sprintf(file_name_src,".monster/added/%s",entry->d_name);
            sprintf(file_name_dest,".monster/commits/%s",entry->d_name);
            FILE* file_dest=fopen(file_name_dest,"w");
            FILE* file_src=fopen(file_name_src,"r");
            char line[MAX_LINE_LENGTH];
            while(fgets(line,sizeof(line),file_src)!=NULL){
                // line[strlen(line)-1]='\0';
                fputs(line,file_dest);
            }
            fclose(file_dest);
            fclose(file_src);
            remove(file_name_src);
        }
    }
    // FILE* file=fopen(".monster/commitsinformation","a");

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
    if(strcmp(argv[1],"commit")==0 && strcmp(argv[2],"-m")==0) return commit(argc,argv);
    if(init_flag()){
        char cwd[1024];
        getcwd(cwd,sizeof(cwd));
        chdir(".monster/alias");
        struct dirent *entry;
        DIR *dir = opendir(".");
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
                if(strcmp(argv[1],"commit")==0 && strcmp(argv[2],"-m")==0) return commit(count_of_words,words);
            }
        }
        closedir(dir);
        chdir("/home/mr_nakhjavani/Documents/alias_global");
        dir = opendir(".");
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
                if(strcmp(argv[1],"commit")==0 && strcmp(argv[2],"-m")==0) return commit(count_of_words,words);
            }
        }
        printf("Invalid command!\n");
        return 1;
    }
    printf("Invalid command\n");
    return 1;
}