#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<json-c/json.h>

struct Profile{
    char Username[20];
    char Password[20];
    int Posts[10000];
    int PCount;
};
struct Profile Users[1000];
char AllPosts[10000][1001];

void MainMenu();
void Post(int i);
void Edit(int i);
void All();
void PassChange(int i);
void init();

int ID, UserCount;
int *tmpPtr;
FILE *fptr;

int main(){
    //Log in/Sign up menu

    char u[100], p[100], test;
    int act;
    init();

    while(1){
        printf("Please enter your username(Maximum of 20 characters and no spaces): ");
        fgets(u, 99, stdin);
        while(strlen(u) > 20 || strchr(u, ' ') != NULL){
            puts("Invalid username!\n");
            printf("Please enter your username(Maximum of 20 characters and no spaces): ");
            fgets(u, 99, stdin);
        }
        printf("Please enter your password(Maximum of 20 characters and no spaces): ");
        fgets(p, 99, stdin);
        while(strlen(p) > 20 || strchr(p, ' ') != NULL){
            puts("Invalid password!\n");
            printf("Please enter your password(Maximum of 20 characters and no spaces): ");
            fgets(p, 99, stdin);
        }
        puts("\n1. Log in\n2. Sign up\n3. Exit");
        printf("Enter number of menu: ");
        act = getchar()-48;
        if ((test = getchar()) != '\n'){
            act = 0;
            while((test = getchar()) != '\n'){}
        }
        if(act == 1){
            int f = 0;
            for(int i=0; i<UserCount; i++){
                if(strcmp(Users[i].Username, u) == 0){
                    f = 1;
                    if(strcmp(Users[i].Password, p) != 0){
                        puts("Wrong password!\n");
                        break;
                    }
                    else{
                        system("cls");
                        int tmp = i;
                        tmpPtr = &tmp;
                        MainMenu();
                        break;
                    }
                }
            }
            if(f == 0)
                puts("Username doesn't exist.");
            continue;
        }
        else if(act == 2){
            int f = 0;
            for(int i=0; i<UserCount; i++){
                if(strcmp(Users[i].Username, u) == 0){
                    f = 1;
                    puts("Username already exists.");
                    break;
                }
            }
            if (f == 1)
                continue;
            strcpy(Users[UserCount].Username, u);
            strcpy(Users[UserCount].Password, p);
            Users[UserCount].PCount = 0;
            system("cls");
            int tmp = UserCount++;
            tmpPtr = &tmp;
            fptr = fopen("Uc.json", "w");
            fprintf(fptr, "{\"Uc\": %d}", UserCount);
            fclose(fptr);
            fptr = fopen("Prf.json", "w");
            for(int i=0; i < UserCount; i++){
                if(i == 0)
                    fprintf(fptr, "[{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                else
                    fprintf(fptr, "{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                for(int j=0; j < Users[i].PCount; j++){
                    if(j == Users[i].PCount - 1){
                        fprintf(fptr, "%d", Users[i].Posts[j]);
                        break;
                    }
                    fprintf(fptr, "%d, ", Users[i].Posts[j]);
                }
                if(i == UserCount - 1){
                        fprintf(fptr, "]}]");
                        break;
                    }
                fprintf(fptr, "]}, ");

            }
            fclose(fptr);
            MainMenu();
        }
        else if(act == 3)
            break;
        else
            puts("Invalid command!");
    }
}

void MainMenu(){
    puts("Main menu:\n1. Send message\n2. Edit message\n3. View all messages\n4. Change password\n5. Exit");
    printf("Enter number of menu: ");
    int choice;
    char test;
    choice = getchar()-48;
    if ((test = getchar()) != '\n'){
        choice = 0;
        while((test = getchar()) != '\n'){}
    }
    while(choice != 5){
        switch(choice){
            case 1:
                system("cls");
                Post(*tmpPtr);
                puts("Main menu:\n1. Send message\n2. Edit message\n3. View all messages\n4. Change password\n5. Exit");
                printf("Enter number of menu: ");
                break;
            case 2:
                system("cls");
                Edit(*tmpPtr);
                puts("Main menu:\n1. Send message\n2. Edit message\n3. View all messages\n4. Change password\n5. Exit");
                printf("Enter number of menu: ");
                break;
            case 3:
                system("cls");
                All();
                puts("Main menu:\n1. Send message\n2. Edit message\n3. View all messages\n4. Change password\n5. Exit");
                printf("Enter number of menu: ");
                break;
            case 4:
                system("cls");
                PassChange(*tmpPtr);
                puts("Main menu:\n1. Send message\n2. Edit message\n3. View all messages\n4. Change password\n5. Exit");
                printf("Enter number of menu: ");
                break;
            default:
                puts("Invalid command!\n");
                printf("Enter number of menu: ");
        }
        choice = getchar()-48;
        if ((test = getchar()) != '\n'){
            choice = 0;
            while((test = getchar()) != '\n'){}
        }
    }
    system("cls");
}

void Post(int i){
    puts("Send message menu:\n1. Write a message\n2. Exit");
    printf("Enter number of menu: ");
    int choice;
    char test;
    choice = getchar()-48;
    if ((test = getchar()) != '\n'){
        choice = 0;
        while((test = getchar()) != '\n'){}
    }
    while(choice != 2){
        switch (choice){
            case 1:
                puts("Please enter your message(Maximum of 1000 characters):");
                Users[i].Posts[Users[i].PCount++] = ID;
                fgets(AllPosts[ID-1], 1000, stdin);
                fptr = fopen("Prf.json", "w");
                for(int i=0; i < UserCount; i++){
                    if(i == 0)
                        fprintf(fptr, "[{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                    else
                        fprintf(fptr, "{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                    for(int j=0; j < Users[i].PCount; j++){
                        if(j == Users[i].PCount - 1){
                            fprintf(fptr, "%d", Users[i].Posts[j]);
                            break;
                        }
                        fprintf(fptr, "%d, ", Users[i].Posts[j]);
                    }
                    if(i == UserCount - 1){
                            fprintf(fptr, "]}]");
                            break;
                        }
                    fprintf(fptr, "]}, ");
                }
                fclose(fptr);
                ID++;
                fptr = fopen("id.json", "w");
                fprintf(fptr, "{\"ID\": %d}", ID);
                fclose(fptr);
                fptr = fopen("Posts.json", "w");
                for (int i=0; i < ID - 1; i++){
                    if(i == 0)
                        fprintf(fptr, "[");
                    fprintf(fptr, "\"%s\"", AllPosts[i]);
                    if (i == ID - 2)
                        fprintf(fptr, "]");
                    else
                        fprintf(fptr, ", ");
                }
                fclose(fptr);
                puts("\nMessage saved successfully!\n");
                printf("Enter number of menu: ");
                break;
            default:
                puts("Invalid command!\n");
                printf("Enter number of menu: ");
        }
        choice = getchar()-48;
        if ((test = getchar()) != '\n'){
            choice = 0;
            while((test = getchar()) != '\n'){}
        }
    }
    system("cls");
}

void Edit(int i){
    puts("Edit message menu:\n1. Edit a message\n2. Exit");
    printf("Enter number of menu: ");
    int choice, e, check = 0;
    char test, n;
    choice = getchar()-48;
    if ((test = getchar()) != '\n'){
        choice = 0;
        while((test = getchar()) != '\n'){}
    }
    while(choice != 2){
        switch (choice){
            case 1:
                printf("Please enter your message ID: ");
                scanf("%d", &e);
                while((n = getchar()) != '\n'){}
                if(e >= ID){
                    puts("Message doesn't exist!\n");
                    continue;
                }
                for(int j=0; j<Users[i].PCount; j++){
                    if(Users[i].Posts[j] == e)
                        check = 1;
                }
                if(check == 0){
                    puts("You can't edit someone else's message!\n");
                    continue;
                }
                printf("Please edit the following message: %s\n -> ", AllPosts[e-1]);
                fgets(AllPosts[e-1], 1000, stdin);
                fptr = fopen("Posts.json", "w");
                for (int i=0; i < ID - 1; i++){
                    if(i == 0)
                        fprintf(fptr, "[");
                    fprintf(fptr, "\"%s\"", AllPosts[i]);
                    if (i == ID - 2)
                        fprintf(fptr, "]");
                    else
                        fprintf(fptr, ", ");
                }
                fclose(fptr);
                puts("\nMessage saved successfully!\n");
                printf("Enter number of menu: ");
                break;
            default:
                puts("Invalid command!\n");
                printf("Enter number of menu: ");
        }
        choice = getchar()-48;
        if ((test = getchar()) != '\n'){
            choice = 0;
            while((test = getchar()) != '\n'){}
        }
    }
    system("cls");
}

void All(){
    puts("1. See all messages\n2. Exit");
    printf("Enter number of menu: ");
    int choice;
    char test;
    choice = getchar()-48;
    if ((test = getchar()) != '\n'){
        choice = 0;
        while((test = getchar()) != '\n'){}
    }
    while(choice != 2){
        switch (choice){
            case 1:
                for(int i=0; i<ID-1; i++)
                    printf("%d: %s\n", i+1, AllPosts[i]);
                printf("Enter number of menu: ");
                break;
            default:
                puts("Invalid command!\n");
                printf("Enter number of menu: ");
        }
        choice = getchar()-48;
        if ((test = getchar()) != '\n'){
            choice = 0;
            while((test = getchar()) != '\n'){}
        }
    }
    system("cls");
}

void PassChange(int i){
    puts("1. Change password\n2. Exit");
    printf("Enter number of menu: ");
    int choice;
    char test, p[100];
    choice = getchar()-48;
    if ((test = getchar()) != '\n'){
        choice = 0;
        while((test = getchar()) != '\n'){}
    }
    while(choice != 2){
        switch (choice){
            case 1:
                printf("Please enter your password(Maximum of 20 characters and no spaces): ");
                fgets(p, 99, stdin);
                while(strlen(p) > 20 || strchr(p, ' ') != NULL){
                    puts("Invalid password!\n");
                    printf("Please enter your password(Maximum of 20 characters and no spaces): ");
                    fgets(p, 99, stdin);
                }
                strcpy(Users[i].Password, p);
                fptr = fopen("Prf.json", "w");
                for(int i=0; i < UserCount; i++){
                    if(i == 0)
                        fprintf(fptr, "[{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                    else
                        fprintf(fptr, "{\"username\": \"%s\", \"password\": \"%s\", \"pcount\": %d, \"posts\": [", Users[i].Username, Users[i].Password, Users[i].PCount);
                    for(int j=0; j < Users[i].PCount; j++){
                        if(j == Users[i].PCount - 1){
                            fprintf(fptr, "%d", Users[i].Posts[j]);
                            break;
                        }
                        fprintf(fptr, "%d, ", Users[i].Posts[j]);
                    }
                    if(i == UserCount - 1){
                            fprintf(fptr, "]}]");
                            break;
                        }
                    fprintf(fptr, "]}, ");

                }
                fclose(fptr);
                puts("\nMessage saved successfully!\n");
                printf("Enter number of menu: ");
                break;
            default:
                puts("Invalid command!\n");
                printf("Enter number of menu: ");
        }
        choice = getchar()-48;
        if ((test = getchar()) != '\n'){
            choice = 0;
            while((test = getchar()) != '\n'){}
        }
    }
    system("cls");
}
void init(){
    FILE *fp;
    char buffer[10240];
    struct json_object *tp;
    struct json_object *t;
    struct json_object *pj;
    struct json_object *prf;
    struct json_object *un;
    struct json_object *pw;
    struct json_object *pc;
    struct json_object *pos;
    struct json_object *po;


    fp = fopen("id.json", "r");
    if(fp == NULL){
        fp = fopen("id.json", "w");
        fprintf(fp, "{\"ID\": 1}");
        fclose(fp);
        fp = fopen("id.json", "r");
    }

    fread(buffer, 10240, 1, fp);
    fclose(fp);
    pj = json_tokener_parse(buffer);
    json_object_object_get_ex(pj, "ID", &tp);
    ID = json_object_get_int(tp);

    fp = fopen("Uc.json", "r");
    if(fp == NULL){
        fp = fopen("Uc.json", "w");
        fprintf(fp, "{\"Uc\": 0}");
        fclose(fp);
        fp = fopen("Uc.json", "r");
    }
    fread(buffer, 10240, 1, fp);
    fclose(fp);
    pj = json_tokener_parse(buffer);
    json_object_object_get_ex(pj, "Uc", &tp);
    UserCount = json_object_get_int(tp);


    fp = fopen("Prf.json", "r");
    if(fp == NULL){
        fp = fopen("Prf.json", "w");
        fprintf(fp, "[]");
        fclose(fp);
        fp = fopen("Prf.json", "r");
    }
    fread(buffer, 10240, 1, fp);
    fclose(fp);
    pj = json_tokener_parse(buffer);
    for(int i=0; i<UserCount; i++){
        t = json_object_array_get_idx(pj, i);
        json_object_object_get_ex(t, "username", &un);
        strcpy(Users[i].Username, json_object_get_string(un));
        json_object_object_get_ex(t, "password", &pw);
        strcpy(Users[i].Password, json_object_get_string(pw));
        json_object_object_get_ex(t, "pcount", &pc);
        Users[i].PCount = json_object_get_int(pc);
        json_object_object_get_ex(t, "posts", &pos);
        for (int j=0; j < Users[i].PCount; j++){
            po = json_object_array_get_idx(pos, j);
            Users[i].Posts[j] = json_object_get_int(po);
        }
    }

    fp = fopen("Posts.json", "r");
    if(fp == NULL){
        fp = fopen("Posts.json", "w");
        fprintf(fp, "[]");
        fclose(fp);
        fp = fopen("Posts.json", "r");
    }
    fread(buffer, 10240, 1, fp);
    fclose(fp);
    pj = json_tokener_parse(buffer);
    for(int i=0; i < ID-1; i++){
        t = json_object_array_get_idx(pj, i);
        strcpy(AllPosts[i], json_object_get_string(t));
    }
}
