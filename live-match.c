#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ball
{
    int over;
    int ball;
    int runs;
    int wicket;
    char event[30];

    struct Ball *next;
};

struct Ball* createBall();
void recordBall(struct Ball **head);
void displayBalls(struct Ball *head);
void undoLastBall(struct Ball **head);
void displayScore(struct Ball *head);
void freeBalls(struct Ball **head);


struct Ball* createBall()
{
    struct Ball *newBall;

    newBall=(struct Ball*)malloc(sizeof(struct Ball));

    if(newBall==NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newBall->next=NULL;

    return newBall;
}


void recordBall(struct Ball **head)
{
    struct Ball *newBall;
    struct Ball *temp;

    newBall=createBall();

    if(newBall==NULL)
        return;

    if(*head==NULL)
    {
        newBall->over=1;
        newBall->ball=1;
    }
    else
    {
        temp=*head;

        while(temp->next!=NULL)
            temp=temp->next;

        if(temp->ball==6)
        {
            newBall->over=temp->over+1;
            newBall->ball=1;
        }
        else
        {
            newBall->over=temp->over;
            newBall->ball=temp->ball+1;
        }
    }

    printf("\nEnter runs (0/1/2/3/4/6): ");
    scanf("%d",&newBall->runs);

    while(newBall->runs!=0 &&
          newBall->runs!=1 &&
          newBall->runs!=2 &&
          newBall->runs!=3 &&
          newBall->runs!=4 &&
          newBall->runs!=6)
    {
        printf("Invalid runs! Enter again: ");
        scanf("%d",&newBall->runs);
    }

    printf("Is wicket? (1-Yes / 0-No): ");
    scanf("%d",&newBall->wicket);

    if(newBall->wicket==1)
        strcpy(newBall->event,"WICKET");
    else if(newBall->runs==0)
        strcpy(newBall->event,"DOT BALL");
    else if(newBall->runs==4)
        strcpy(newBall->event,"FOUR");
    else if(newBall->runs==6)
        strcpy(newBall->event,"SIX");
    else
        strcpy(newBall->event,"RUN");

    newBall->next=NULL;

    if(*head==NULL)
        *head=newBall;
    else
    {
        temp=*head;

        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newBall;
    }

    printf("Ball recorded successfully!\n");
}


void displayBalls(struct Ball *head)
{
    struct Ball *temp;

    if(head==NULL)
    {
        printf("\nNo balls recorded.\n");
        return;
    }

    temp=head;

    printf("\n----- BALL-BY-BALL HISTORY -----\n");

    while(temp!=NULL)
    {
        printf("Over %d.%d : %d run - %s\n",
        temp->over,temp->ball,temp->runs,temp->event);

        temp=temp->next;
    }
}


void undoLastBall(struct Ball **head)
{
    struct Ball *temp;
    struct Ball *previous;

    if(*head==NULL)
    {
        printf("\nNo ball to undo.\n");
        return;
    }

    if((*head)->next==NULL)
    {
        free(*head);
        *head=NULL;

        printf("\nLast ball removed.\n");
        return;
    }

    temp=*head;

    while(temp->next!=NULL)
    {
        previous=temp;
        temp=temp->next;
    }

    previous->next=NULL;

    free(temp);

    printf("\nLast ball removed.\n");
}


void displayScore(struct Ball *head)
{
    struct Ball *temp;

    int runs=0;
    int wickets=0;
    int balls=0;

    temp=head;

    while(temp!=NULL)
    {
        runs=runs+temp->runs;

        if(temp->wicket==1)
            wickets++;

        balls++;

        temp=temp->next;
    }

    printf("\n----- SCOREBOARD -----\n");

    printf("Score : %d/%d\n",runs,wickets);
    printf("Balls : %d\n",balls);
    printf("Overs : %d.%d\n",balls/6,balls%6);

    if(balls>0)
        printf("Run Rate : %.2f\n",
        (float)runs/(balls/6.0));
    else
        printf("Run Rate : 0.00\n");
}


void freeBalls(struct Ball **head)
{
    struct Ball *temp;

    while(*head!=NULL)
    {
        temp=*head;
        *head=(*head)->next;
        free(temp);
    }
}


int main()
{
    struct Ball *head=NULL;
    int choice;

    do
    {
        printf("\n================================\n");
        printf("     LIVE BALL-BY-BALL ENGINE\n");
        printf("================================\n");
        printf("1. Record Ball\n");
        printf("2. Display Ball History\n");
        printf("3. Undo Last Ball\n");
        printf("4. Display Score\n");
        printf("5. Exit\n");
        printf("================================\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                recordBall(&head);
                break;

            case 2:
                displayBalls(head);
                break;

            case 3:
                undoLastBall(&head);
                break;

            case 4:
                displayScore(head);
                break;

            case 5:
                freeBalls(&head);
                printf("\nProgram ended.\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    }while(choice!=5);

    return 0;
}