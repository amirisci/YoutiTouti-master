#include <stdio.h>
#include <stdlib.h>
#define true 1 
#define zero 0

struct posts
    {
        char* text;
        int Id ;
        int like;
        struct posts* nextpost;
    };
//-------------------------------------------------------//
struct  users
{    char* usernam;
     char* password ;
     int post_number;
    struct posts* post;
    struct users* nextuser;  
};
///---------///
int sizeoff(char *data){
    int size = 0 ;
    for ( int i = 0 ; data[i]; i++){
        size++;
    }
    return size;
}
///----------------------------------------------------///
char* enter_post(char* data){
     data = (char*)realloc(NULL,sizeof(char));
    char temp[1] ={' '};
    int i = 0;
    *(data) = '0';
    while(true){
        i++;
        scanf("%c",temp);
        printf("%c\n" , temp[0]);
        data = (char*)realloc(data , sizeof(char) * i);
        data[i -1] = '\0';
        switch(temp[0]){
            case '\n':
                return data;
                break;
            default:
                data[i-1] = temp[0];
                break;
        }
        
    }
    
}
///-----------------------------------------------------///
int file_account(struct users* head){
    struct users* temp = head;
    FILE* accounts = fopen("accounts.txt" ,"w");
    while(temp!=NULL){
        fputs(temp->usernam , accounts);
        fputs(" " , accounts);
        fputs(temp->password , accounts);
        fputs(" " , accounts);
        fprintf( accounts , "%d" ,temp->post_number);
        fputs("\n" ,accounts);
        temp = temp->nextuser;   
    }
    fclose(accounts);
}
///------------------------------------------------///
int file_post(struct users* head){
    struct users* temp =  head;
    FILE* posts = fopen("posts.txt" ,"w");
    while(temp!= NULL){
        struct posts* post = temp->post;
        while(post!= NULL){
            fputs(temp->usernam , posts);
            fputs(" " ,posts);
            fputs(post->text , posts);
            fputs(" " , posts);
            fprintf(posts , "%d" , post->like);
            fputs("\n" , posts);
            post = post->nextpost;
        }
        temp = temp->nextuser;
    }
    fclose(posts);
}
///-------------------------------------------------//
///this function scans username , password and all the things exept the commnads and posts
char* enter_data_in_link(char* data){
    printf("line 90\n");
     data = (char*)malloc(sizeof(char));
    char* you;
    int i = 0;
    *(data) =0;
    char temp[1] ={' '};
    printf("enter data\n");
    while(true){
        
        scanf("%c",temp);
        printf("%c" , temp[0]);
        i++;
        //printf("%c\n" , temp[0]);
        data = (char*)realloc(data , sizeof(char) * i);
        //printf("after reallocc\n");
        data[i - 1] = '\0';
        switch(temp[0]){
            case '\n':
            //printf("i found \\n\\ \n");
                return data;
                break;
            case '\0':
            // printf("i found 0\n");
                return data;
                break;
            case ' ':
            //printf("i found ' '\n ");
                return data;
                 break;
            default:
                data[i-1] = temp[0];
                break;
        }
        //printf("outside swich\n");
    }
    printf("outside true\n");
    
    
}

//----------------------------------------------------//
///this function will signup a new user, it reciieves usernme and password , it checks if there is no similar username in the app. 
/// return 0 in case of similar usernames , 1 for successful addition
struct users* signup(struct users* head  ){
    char* data2 ;//= (char*)malloc(sizeof(char));
    char* data;//= (char*)malloc(sizeof(char));
    int check = 0 ;
    struct users* failur = NULL;
    struct users* newone = (struct users*)malloc(sizeof(struct users*)); 
    newone->usernam = enter_data_in_link(data);
    newone->password= enter_data_in_link(data2);
    newone->post_number = 0;
    //free(data);
    //free(data2);
    struct users* temp = head;
    while(temp!= NULL){
        int size= sizeoff(newone->usernam)>sizeoff(temp->usernam)?sizeoff(newone->usernam):sizeoff(temp->usernam);
        for ( int i = 0 ; i < size ; i++){
            if( newone->usernam[i]==temp->usernam[i]){
                check ++;
            }
        }
        if ( check == size){
            printf("check = size\n");
            printf("choose another username !\n");
            return NULL;
        }
        check = 0;
        temp = temp->nextuser;
    }

        if(head == NULL){
            head = newone;
            head->nextuser = NULL;
            head->post = NULL;
            return head;
                }
        else{
            newone->nextuser = head->nextuser;
            head->nextuser = newone;
            newone->post = NULL;
            return head;
            }
    
}
//---------------------------------------------------//
struct users* login(struct users* head){
    char* data;  // = (char*)malloc(sizeof(char));
    char* data2; // = (char*)malloc(sizeof(char));
    printf("in the function\n");
    struct users* temp;
    temp =  head;
    char* username ;
    char* password ;
    //printf("username:%s\n" ,username);
    int what=0;
    username = enter_data_in_link(data);
    printf("again username:%s\n",username);
    password = enter_data_in_link(data2);
    //free(data);
    //free(data2);
    
    while (temp != NULL)
    {
        int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){///iT found the username , now check thepassword
            printf("found the user %s\n" ,temp->usernam);
            int size2 = sizeoff(password)> sizeoff(temp->password)?sizeoff(password):sizeoff(temp->password);
            what = 0;
            for ( int i = 0 ; i < size2 ; i++){
                if ( password[i] == temp->password[i]){
                    what ++;
                }
            }
                if( what == size2 ){///the correct password
                printf("found the password\n"); 
                    return temp;
                }
                else{
                    printf("%s , wrong password!\n", username);
                    return NULL;///why this mf is not workign ?
                }
            
        }
        else{
            what = 0 ;
            temp = temp->nextuser;
        }
    
    }
    printf("no simillar username was found!\n");
    return NULL;//anf also this one
    
}



//-------------------------------------------------//
int what_is_the_order(char* order){
int sum =0 ; 
for (int i = 0 ; order[i]; i++){
    sum+= (int)order[i];
}
return  sum ;
}


//------------------------------------------------//
struct posts* post(struct users* head, struct users* current_user ){
    char* data =  (char*)malloc(sizeof(char));
    int check = 0 ;
    struct users* temp = head;
    while(temp!= NULL){
        int size= sizeoff(current_user->usernam)>sizeoff(temp->usernam)?sizeoff(current_user->usernam):sizeoff(temp->usernam);
        for ( int i = 0 ; i < size ; i++){
            if( current_user->usernam[i]==temp->usernam[i]){
                check ++;
            }
        }
        if ( check == size){
            printf("i found the user\n");
            struct posts* newpost = (struct posts*)malloc(sizeof(struct posts));
            if(current_user->post == NULL){
                current_user->post = newpost;
                current_user->post_number ++;
                newpost->nextpost =NULL;
                newpost->text = enter_post(data);
                free(data);
                newpost->Id = 1;
                newpost->like = 0;
                
            }
            else{////post function , when user has already had a post!///es funktionirt nicht
            printf("in the else\n");
                int id= 2 ;
                struct posts* temp ;
                temp = current_user->post;
                current_user->post_number ++;
                for(; temp->nextpost != NULL;){
                    temp = temp->nextpost;
                    id ++;
                }
                printf(" the last post\n");
                temp->nextpost = newpost;
                newpost->nextpost = NULL;
                printf("1\n");
                printf("2\n");
                newpost->text = enter_post(data);
                free(data);
                printf("3\n");
                newpost->Id = id;
                printf("4\n");
                newpost->like = 0;
                newpost->nextpost = NULL;
            }
            return newpost; 
            printf("%s" ,current_user->post->text );
        }
        check = 0 ;
        temp = temp->nextuser;
    }
    printf(" no user\n");
    return 0;
}
///--------------------------------//try this body :)
int deletee(struct users* current_user){
    char* data = (char*)malloc(sizeof(char));
    char* id = enter_data_in_link(data);
    free(data);
    struct posts* temp;
    temp = current_user->post;
    if( id[0] - 48 == 1){
        current_user->post = temp->nextpost;
        current_user->post_number--;
        free(temp);
        return 1; 
    }
    else{
    while(temp != NULL){
        if( temp->Id == (id[0] - 48)){
            struct posts* pre = current_user->post;
            while (pre != NULL)
            {
             if(pre->nextpost = temp){
                pre->nextpost = temp->nextpost;
                printf("%s\n",pre->text);
                printf("%s\n", temp->text);
                current_user->post_number--;
                free(temp);
                printf("post deleted\n");
                return 1;
             }
             pre = pre->nextpost;
            }
        }
        temp = temp->nextpost;
    }}
    printf("invalid post ID\n");
    return 1;
}
////----------------------------//
int like(struct users* haed ){
    int what =0;
    char* data = (char*)malloc(sizeof(char));
    char* data2 = (char*)malloc(sizeof(char));
    char* username = enter_data_in_link(data);
    printf("after username\n");
    char* id = enter_data_in_link(data2);
    printf("%d\n"  , id[0]);
    free(data);
    free(data2);
    printf("after id\n");
    struct users* temp = haed;

while( true){///first  it wants to find the user
printf("int the while true");
    int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){//it  found the user
        printf("i found th euser\n");
            struct posts* temp1;
            temp1 = temp->post;
            for(; temp1!= NULL;){
                printf("in th efor loop\n");
                printf("%d" ,(int)(id[0])-48);
                if(temp1->Id ==(int)(id[0])-48){
                    printf("i found th epost\n");
                    temp1->like++;
                    printf("the postc was:%s\n" , temp1->text);
                    printf("liked post is now :%d\n",temp1->like);
                    printf("liked the post\n");
                    return 1;
                }
                temp1 = temp1->nextpost;
            }
            printf("invalid post ID\n");
            return 1;
        }
        what = 0;
        temp = temp->nextuser;
}
printf("invalid username\n");
return 1 ;

}
////-----------------------------------///
int info(struct users* head, struct users* current_user ){
    struct users* temp = head;
    int what =0 ;
    while( true){///first  it wants to find the user
    int size = sizeoff(current_user->usernam)> sizeoff(temp->usernam) ?sizeoff(current_user->usernam):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == current_user->usernam[i]){
                what++;
            }
        }
        if( what == size){//when it finds the user
             printf("ussename:%s\n" ,temp->usernam);
             struct posts* temp1 = temp->post;
             while(temp1 != NULL){
                printf("post ID:%d\n" , temp1->Id);
                printf("likes:%d\n"  ,temp1->like);
                printf("%s\n\n" , temp1->text);
                temp1= temp1->nextpost;
             }
             return 1;
            

        }
        what = 0 ;
        temp = temp->nextuser;
    
    }
    printf("error!\n");
    return 1;
}
////-----------------------------------------//
int search(struct users* head ){
    printf("in the function\n");
    char* username;
    char* data = (char*)malloc(sizeof(char));
    username = enter_data_in_link(data);
    free(data);
    printf("after callig enter data\n");
    struct users* temp = head;
    int what =0 ;
    while( true){///first  it wants to find the user
    printf("in whil true\n");
    int size = sizeoff(username)> sizeoff(temp->usernam) ?sizeoff(username):sizeoff(temp->usernam);
        for(int i = 0 ; i < size ; i++){
            if( temp->usernam[i] == username[i]){
                what++;
            }
        }
        if( what == size){///when i found the user name 
            printf("i found th eusername\n");
            printf("username: %s\n" ,temp->usernam);
            struct posts* temp1;
            temp1 = temp->post;
            while(temp1 != NULL){
                printf("finding posts!\n");
                printf("postID:%d\n" , temp1->Id);
                printf("likes:%d\n" , temp1->like);
                printf("%s\n\n" , temp1->text);
                temp1 = temp1->nextpost;
            }
            return 1;
        }
        what = 0 ;
        temp = temp->nextuser;
    }
    printf("no user was found!\n");
    return 1;
}

int main(){ 
    struct posts* postt=NULL;
    const int constt = 1;
    struct users* currnet_user = NULL;
    struct users* head = NULL;
    char jerk[1];
    
    char*useranme = (char*)malloc(sizeof(char*)* 30);
    //system("cls");
    printf("no!");
    printf("welocome to YoutiTouti!\n");
    printf("already a user? log in .....\n");
    printf("NO account yet ?sign up.....\n ");
    while(1){
    while(currnet_user == NULL ){
        char* order = (char*)malloc(sizeof(char*)* 50);
        printf("still null");
        scanf("%s" , order);
        //system("cls");
        scanf("%c", jerk);
        switch(what_is_the_order(order)){
            case 662 ://signup
                head = signup(head);
                printf("after signup \n");
                file_account(head);
                //system("cls");
                free(order);
                if ( head!= NULL){
                    printf("you signed up successfully :)!\n"); } 
            break;

            case 537://login function
                //system("cls");
                //system("cls");
                free(order);
                currnet_user = login(head);
                printf("welcome %s\n",currnet_user->usernam );
                break;

            default: printf("sorry , invalid order !\ntry again [login \\ signup]\n");
            free(order);
            break; 
            }    
        }
    while(currnet_user!= NULL){//now user can start other orders
    char* order = (char*)malloc(sizeof(char*)* 50);
    printf("no longer null\n");
    printf("*--------------------------------------------------*\n");
    printf("YoutiTouti            %s         \n", currnet_user->usernam);
    printf("*--------------------------------------------------*\n");
        scanf("%s",order);
        scanf("%c",jerk);
        //system("cls");
        switch(what_is_the_order(order)){
            case 666:
                currnet_user = NULL;
                free(order);
                printf("Hope see u soon!\n");
                break;
            case 454://post
                printf("post\n");
                free(order);
                postt =post(head , currnet_user);
                file_account(head);
                file_post(head);
                printf("username:%s\n" ,currnet_user->usernam);
                printf("likes:%d\n",postt->like);
                printf("post ID:%d\n" , postt->Id);
                printf("%s\n" ,postt->text );
                break;
            case 421:///like
             printf("bevore die funktion\n");
             like(head);
             free(order);
             file_post(head);
                break;
            case 428:
                 info(head , currnet_user);
                 free(order);
                 break;
            default:
               printf("invalid order!\n");
               free(order);
               break;

            case 630:
            printf("in  the search\n");
                search(head);
                printf("user was found!\n");
                free(order);
                break;
            case 627:
             deletee(currnet_user);
             file_post(head);
             free(order);
             break;
        }

    }    
    }
}