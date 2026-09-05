#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Wicket
{
    int wicketNo;
    char batsman[30];
    char bowler[30];
    char fielder[30];
    char wicketType[20];
    int over;
    int ball;
    int score;
    struct Wicket *next;
};
struct StackNode
{
    char batsman[30];
    struct StackNode *next;
};
struct Wicket *head = NULL;
struct Wicket *tail = NULL;
struct StackNode *top = NULL;
void addWicketToList(
    int wicketNo,
    char batsman[],
    char bowler[],
    char fielder[],
    char wicketType[],
    int over,
    int ball,
    int score)
{
    struct Wicket *newNode;
    newNode = (struct Wicket *)malloc(sizeof(struct Wicket));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->wicketNo = wicketNo;
    strcpy(newNode->batsman, batsman);
    strcpy(newNode->bowler, bowler);
    strcpy(newNode->fielder, fielder);
    strcpy(newNode->wicketType, wicketType);
    newNode->over = over;
    newNode->ball = ball;
    newNode->score = score;
    newNode->next = NULL;
    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}
void displayWickets()
{
    struct Wicket *temp = head;
    if (head == NULL)
    {
        printf("\nNo wickets recorded.\n");
        return;
    }
    printf("\n------------ WICKETS ------------\n");
    while (temp != NULL)
    {
        printf("\nWicket %d", temp->wicketNo);

        printf("\nBatsman     : %s", temp->batsman);
        printf("\nWicket Type : %s", temp->wicketType);
        printf("\nBowler      : %s", temp->bowler);

        if (strlen(temp->fielder) > 0)
        {
            printf("\nFielder     : %s", temp->fielder);
        }

        printf("\nOver        : %d.%d",
               temp->over,
               temp->ball);

        printf("\nScore       : %d", temp->score);

        printf("\n-----------------------------\n");

        temp = temp->next;
    }
}


void push(char batsman[])
{
    struct StackNode *newNode;

    newNode = (struct StackNode *)
              malloc(sizeof(struct StackNode));

    if (newNode == NULL)
    {
        printf("Stack memory allocation failed!\n");
        return;
    }

    strcpy(newNode->batsman, batsman);

    newNode->next = top;
    top = newNode;
}
void pop()
{
    struct StackNode *temp;

    if (top == NULL)
    {
        printf("\nStack is empty.\n");
        return;
    }

    temp = top;

    printf("\nMost recently dismissed batsman: %s\n",
           temp->batsman);

    top = top->next;

    free(temp);
}

void displayStack()
{
    struct StackNode *temp = top;

    if (top == NULL)
    {
        printf("\nNo dismissed batsmen.\n");
        return;
    }

    printf("\n-------------- DISMISSED BATSMEN STACK -------------\n");

    while (temp != NULL)
    {
        printf("%s\n", temp->batsman);

        temp = temp->next;
    }

    printf("-----------------------------------------------\n");
}
void recordWicket()
{
    char batsman[30];
    char bowler[30];
    char fielder[30];
    char wicketType[20];

    int over;
    int ball;
    int score;
    int wicketNo;
    wicketNo = 0;

    struct Wicket *temp = head;

    while (temp != NULL)
    {
        wicketNo++;
        temp = temp->next;
    }

    wicketNo++;

    printf("\nEnter batsman name: ");
    scanf("%s", batsman);

    printf("Enter bowler name: ");
    scanf("%s", bowler);

    printf("Enter wicket type: ");
    scanf("%s", wicketType);

    printf("Enter fielder name (enter - if not required): ");
    scanf("%s", fielder);

    if (strcmp(fielder, "-") == 0)
    {
        strcpy(fielder, "");
    }

    printf("Enter over number: ");
    scanf("%d", &over);

    printf("Enter ball number: ");
    scanf("%d", &ball);

    printf("Enter team score at wicket: ");
    scanf("%d", &score);
    addWicketToList(
        wicketNo,
        batsman,
        bowler,
        fielder,
        wicketType,
        over,
        ball,
        score
    );
    push(batsman);

    printf("\n*** WICKET RECORDED SUCCESSFULLY ***\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n------------------ WICKET SYSTEM -----------------\n");

        printf("1. ENTER Wicket\n");
        printf("2. Display All Wickets\n");
        printf("3. Display Dismissed Batsmen Stack\n");
        printf("4. Pop Most Recent Wicket\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                recordWicket();
                break;

            case 2:
                displayWickets();
                break;

            case 3:
                displayStack();
                break;

            case 4:
                pop();
                break;

            case 5:
                printf("\nExiting Wicket System...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}