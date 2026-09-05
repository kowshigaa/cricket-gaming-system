#include <stdio.h>
#include <string.h>
struct Match
{
    int id;
    char team1[30];
    char team2[30];
    char date[20];
    int priority;
};
struct Queue
{
    struct Match m[50];
    int front;
    int rear;
};
void initialize(struct Queue *q)
{
    q->front = 0;
    q->rear = -1;
}
void scheduleMatch(struct Queue *q)
{
    if (q->rear == 49)
    {
        printf("Queue is full.\n");
        return;
    }
    q->rear++;
    printf("Enter Match ID: ");
    scanf("%d", &q->m[q->rear].id);
    printf("Enter Team 1: ");
   scanf("%s", q->m[q->rear].team1);
    printf("Enter Team 2: ");
    scanf("%s", q->m[q->rear].team2);
    printf("Enter Date: ");
    scanf("%s", q->m[q->rear].date);
    printf("Enter Priority:\n");
    printf("1. Final\n");
    printf("2. Semi Final\n");
    printf("3. League Match\n");
    printf("Enter choice: ");
    scanf("%d", &q->m[q->rear].priority);

    printf("Match scheduled successfully.\n");
}
void displayMatches(struct Queue *q)
{
    int i;

    if (q->front > q->rear)
    {
        printf("No upcoming matches.\n");
        return;
    }
    printf("\n------ UPCOMING MATCHES ------\n");
    for (i = q->front; i <= q->rear; i++)
    {
        printf("\nMatch ID : %d", q->m[i].id);
        printf("\nTeams    : %s vs %s", q->m[i].team1, q->m[i].team2);
        printf("\nDate     : %s", q->m[i].date);

        if (q->m[i].priority == 1)
            printf("\nType     : Final\n");
        else if (q->m[i].priority == 2)
            printf("\nType     : Semi Final\n");
        else
            printf("\nType     : League Match\n");
    }
}

void startNextMatch(struct Queue *q)
{
    if (q->front > q->rear)
    {
        printf("No matches available.\n");
        return;
    }

    printf("\n------ MATCH STARTED ------\n");
    printf("Match ID : %d\n", q->m[q->front].id);
    printf("%s vs %s\n",
           q->m[q->front].team1,
           q->m[q->front].team2);
    printf("Date : %s\n", q->m[q->front].date);

    q->front++;

    printf("Match removed from the schedule.\n");
}
void cancelMatch(struct Queue *q)
{
    int id, i, found = 0;
    if (q->front > q->rear)
    {
        printf("No matches available.\n");
        return;
    }
    printf("Enter Match ID to cancel: ");
    scanf("%d", &id);
    for (i = q->front; i <= q->rear; i++)
    {
        if (q->m[i].id == id)
        {
            found = 1;
            while (i < q->rear)
            {
                q->m[i] = q->m[i + 1];
                i++;
            }
            q->rear--;
            printf("Match cancelled successfully.\n");
            break;
        }
    }
    if (found == 0)
        printf("Match not found.\n");
}
void postponeMatch(struct Queue *q)
{
    int id, i, found = 0;
    if (q->front > q->rear)
    {
        printf("No matches available.\n");
        return;
    }
    printf("Enter Match ID to postpone: ");
    scanf("%d", &id);
    for (i = q->front; i <= q->rear; i++)
    {
        if (q->m[i].id == id)
        {
            found = 1;

            printf("Enter new date: ");
            scanf("%s", q->m[i].date);

            printf("Match postponed successfully.\n");
            break;
        }
    }
    if (found == 0)
        printf("Match not found.\n");
}
int main()
{
    struct Queue q;
    int choice;
    initialize(&q);
    while (1)
    {
        printf("\n===============================\n");
        printf("       MATCH SCHEDULING\n");
        printf("===============================\n");
        printf("1. Schedule Match\n");
        printf("2. Display Upcoming Matches\n");
        printf("3. Start Next Match\n");
        printf("4. Cancel Match\n");
        printf("5. Postpone Match\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                scheduleMatch(&q);
               break;
            case 2:
                displayMatches(&q);
                break;
            case 3:
                startNextMatch(&q);
                break;
            case 4:
                cancelMatch(&q);
                break;
            case 5:
                postponeMatch(&q);
                break;
            case 6:
                printf("Exiting Match Scheduling.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}