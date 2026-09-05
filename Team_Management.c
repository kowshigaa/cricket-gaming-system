#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Team
{
    int teamId;
    char teamName[50];
    char captain[50];
    char coach[50];
    int totalPlayers;
};
struct Node
{
    struct Team team;
    struct Node *next;
};
struct Node *head = NULL;
struct Node* createTeam()
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    printf("\nEnter Team ID: ");
    scanf("%d", &newNode->team.teamId);
    printf("Enter Team Name: ");
    scanf(" %[^\n]", newNode->team.teamName);
    printf("Enter Captain Name: ");
    scanf(" %[^\n]", newNode->team.captain);
    printf("Enter Coach Name: ");
    scanf(" %[^\n]", newNode->team.coach);
    printf("Enter Total Players: ");
    scanf("%d", &newNode->team.totalPlayers);
    newNode->next = NULL;
    return newNode;
}
void addTeam()
{
    struct Node *newNode, *temp;
    newNode = createTeam();
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("\nTeam added successfully!\n");
}
void displayTeams()
{
    struct Node *temp;
    if (head == NULL)
    {
        printf("\nNo teams available.\n");
        return;
    }
    temp = head;
    printf("\n========== TEAM LIST ==========\n");
    while (temp != NULL)
    {
        printf("\nTeam ID       : %d", temp->team.teamId);
        printf("\nTeam Name     : %s", temp->team.teamName);
        printf("\nCaptain       : %s", temp->team.captain);
        printf("\nCoach         : %s", temp->team.coach);
        printf("\nTotal Players : %d", temp->team.totalPlayers);
        printf("\n-------------------------------");

        temp = temp->next;
    }
}
void findTeam()
{
    struct Node *temp;
    int id;
    int found = 0;
    if (head == NULL)
    {
        printf("\nNo teams available.\n");
        return;
    }
    printf("\nEnter Team ID to search: ");
    scanf("%d", &id);
    temp = head;
    while (temp != NULL)
    {
        if (temp->team.teamId == id)
        {
            printf("\nTeam Found!\n");
            printf("\nTeam ID       : %d", temp->team.teamId);
            printf("\nTeam Name     : %s", temp->team.teamName);
            printf("\nCaptain       : %s", temp->team.captain);
            printf("\nCoach         : %s", temp->team.coach);
            printf("\nTotal Players : %d\n", temp->team.totalPlayers);
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (found == 0)
    {
        printf("\nTeam not found.\n");
    }
}
void deleteTeam()
{
    struct Node *temp, *prev;
    int id;
    if (head == NULL)
    {
        printf("\nNo teams available.\n");
        return;
    }
    printf("\nEnter Team ID to delete: ");
    scanf("%d", &id);
    temp = head;
    prev = NULL;
    if (temp != NULL && temp->team.teamId == id)
    {
        head = temp->next;
        free(temp);
        printf("\nTeam deleted successfully!\n");
        return;
    }
    while (temp != NULL && temp->team.teamId != id)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\nTeam not found.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("\nTeam deleted successfully!\n");
}
void updateTeam()
{
    struct Node *temp;
    int id;
    if (head == NULL)
    {
        printf("\nNo teams available.\n");
        return;
    }
    printf("\nEnter Team ID to update: ");
    scanf("%d", &id);
    temp = head;
    while (temp != NULL)
    {
        if (temp->team.teamId == id)
        {
            printf("\nEnter New Team Name: ");
            scanf(" %[^\n]", temp->team.teamName);
            printf("Enter New Captain Name: ");
            scanf(" %[^\n]", temp->team.captain);
            printf("Enter New Coach Name: ");
            scanf(" %[^\n]", temp->team.coach);
            printf("Enter New Total Players: ");
            scanf("%d", &temp->team.totalPlayers);
            printf("\nTeam updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nTeam not found.\n");
}
int main()
{
    int choice;

    while (1)
    {
        printf("\n-----CRICKET TEAM MANAGEMENT-----");
        printf("\n1. Create Team");
        printf("\n2. Add Team");
        printf("\n3. Delete Team");
        printf("\n4. Display Teams");
        printf("\n5. Update Team");
        printf("\n6. Find Team");
        printf("\n7. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createTeam();
                break;

            case 2:
                addTeam();
                break;

            case 3:
                deleteTeam();
                break;

            case 4:
                displayTeams();
                break;

            case 5:
                updateTeam();
                break;

            case 6:
                findTeam();
                break;

            case 7:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
