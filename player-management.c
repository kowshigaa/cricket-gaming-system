#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Player
{
    int playerId;
    char name[50];
    int age;
    char role[30];
    char battingStyle[30];
    char bowlingStyle[30];

    int teamId;

    int matches;
    int runs;
    int wickets;

    struct Player *next;
};
struct Player *head = NULL;

void addPlayer();
void displayPlayers();
void searchPlayer();
void updatePlayer();
void deletePlayer();
void displayTeamPlayers();
void sortPlayers();
void displayPlayerDetails(struct Player *p);
void playerManagementMenu();

void addPlayer()
{
    struct Player *newPlayer;
    struct Player *temp;

    newPlayer = (struct Player *)malloc(sizeof(struct Player));

    if (newPlayer == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    printf("\n========== ADD PLAYER ==========\n");

    printf("Enter Player ID: ");
    scanf("%d", &newPlayer->playerId);

    /* Check duplicate ID */
    temp = head;

    while (temp != NULL)
    {
        if (temp->playerId == newPlayer->playerId)
        {
            printf("\nPlayer ID already exists!\n");
            free(newPlayer);
            return;
        }

        temp = temp->next;
    }

    printf("Enter Player Name: ");
    scanf(" %[^\n]", newPlayer->name);

    printf("Enter Age: ");
    scanf("%d", &newPlayer->age);

    printf("Enter Role: ");
    scanf(" %[^\n]", newPlayer->role);

    printf("Enter Batting Style: ");
    scanf(" %[^\n]", newPlayer->battingStyle);

    printf("Enter Bowling Style: ");
    scanf(" %[^\n]", newPlayer->bowlingStyle);

    printf("Enter Team ID: ");
    scanf("%d", &newPlayer->teamId);

    
    newPlayer->matches = 0;
    newPlayer->runs = 0;
    newPlayer->wickets = 0;

    newPlayer->next = NULL;
    if (head == NULL)
    {
        head = newPlayer;
    }
    else
    {
        temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newPlayer;
    }

    printf("\nPlayer added successfully!\n");
}

void displayPlayers()
{
    struct Player *temp = head;

    if (head == NULL)
    {
        printf("\nNo players available.\n");
        return;
    }

    printf("\n================ ALL PLAYERS ================\n");

    printf("%-8s %-20s %-6s %-15s %-10s %-8s\n",
           "ID", "NAME", "AGE", "ROLE", "TEAM ID", "RUNS");

    printf("------------------------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-8d %-20s %-6d %-15s %-10d %-8d\n",
               temp->playerId,
               temp->name,
               temp->age,
               temp->role,
               temp->teamId,
               temp->runs);

        temp = temp->next;
    }
}

void displayPlayerDetails(struct Player *p)
{
    printf("\n========================================\n");
    printf("          PLAYER DETAILS\n");
    printf("========================================\n");

    printf("Player ID       : %d\n", p->playerId);
    printf("Name            : %s\n", p->name);
    printf("Age             : %d\n", p->age);
    printf("Role            : %s\n", p->role);
    printf("Batting Style   : %s\n", p->battingStyle);
    printf("Bowling Style   : %s\n", p->bowlingStyle);
    printf("Team ID         : %d\n", p->teamId);

    printf("\n----- Statistics -----\n");

    printf("Matches         : %d\n", p->matches);
    printf("Runs            : %d\n", p->runs);
    printf("Wickets         : %d\n", p->wickets);

    printf("========================================\n");
}

void searchPlayer()
{
    struct Player *temp;
    int choice;
    int id;
    char name[50];
    int found = 0;

    if (head == NULL)
    {
        printf("\nNo players available.\n");
        return;
    }

    printf("\n========== SEARCH PLAYER ==========\n");
    printf("1. Search by Player ID\n");
    printf("2. Search by Player Name\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    temp = head;

    if (choice == 1)
    {
        printf("Enter Player ID: ");
        scanf("%d", &id);

        while (temp != NULL)
        {
            if (temp->playerId == id)
            {
                displayPlayerDetails(temp);
                found = 1;
                break;
            }

            temp = temp->next;
        }
    }
    else if (choice == 2)
    {
        printf("Enter Player Name: ");
        scanf(" %[^\n]", name);

        while (temp != NULL)
        {
            if (strcmp(temp->name, name) == 0)
            {
                displayPlayerDetails(temp);
                found = 1;
                break;
            }

            temp = temp->next;
        }
    }
    else
    {
        printf("\nInvalid choice!\n");
        return;
    }

    if (!found)
    {
        printf("\nPlayer not found.\n");
    }
}

void updatePlayer()
{
    struct Player *temp;
    int id;
    int choice;

    if (head == NULL)
    {
        printf("\nNo players available.\n");
        return;
    }

    printf("\n========== UPDATE PLAYER ==========\n");

    printf("Enter Player ID: ");
    scanf("%d", &id);

    temp = head;

    while (temp != NULL)
    {
        if (temp->playerId == id)
        {
            printf("\nPlayer found: %s\n", temp->name);

            printf("\n1. Update Name\n");
            printf("2. Update Age\n");
            printf("3. Update Role\n");
            printf("4. Update Batting Style\n");
            printf("5. Update Bowling Style\n");
            printf("6. Transfer to Another Team\n");
            printf("Enter choice: ");

            scanf("%d", &choice);

            switch (choice)
            {
                case 1:
                    printf("Enter new name: ");
                    scanf(" %[^\n]", temp->name);
                    break;

                case 2:
                    printf("Enter new age: ");
                    scanf("%d", &temp->age);
                    break;

                case 3:
                    printf("Enter new role: ");
                    scanf(" %[^\n]", temp->role);
                    break;

                case 4:
                    printf("Enter new batting style: ");
                    scanf(" %[^\n]", temp->battingStyle);
                    break;

                case 5:
                    printf("Enter new bowling style: ");
                    scanf(" %[^\n]", temp->bowlingStyle);
                    break;

                case 6:
                    printf("Enter new Team ID: ");
                    scanf("%d", &temp->teamId);
                    break;

                default:
                    printf("\nInvalid choice!\n");
                    return;
            }

            printf("\nPlayer updated successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nPlayer not found.\n");
}

void deletePlayer()
{
    struct Player *temp;
    struct Player *prev;

    int id;

    if (head == NULL)
    {
        printf("\nNo players available.\n");
        return;
    }

    printf("\n========== DELETE PLAYER ==========\n");

    printf("Enter Player ID: ");
    scanf("%d", &id);

    temp = head;
    prev = NULL;
    while (temp != NULL)
    {
        if (temp->playerId == id)
        {
            break;
        }

        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("\nPlayer not found.\n");
        return;
    }

    
    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    printf("\nPlayer '%s' deleted successfully!\n", temp->name);

    free(temp);
}



void displayTeamPlayers()
{
    struct Player *temp;
    int teamId;
    int found = 0;

    if (head == NULL)
    {
        printf("\nNo players available.\n");
        return;
    }

    printf("\n========== TEAM PLAYERS ==========\n");

    printf("Enter Team ID: ");
    scanf("%d", &teamId);

    temp = head;

    printf("\nPlayers belonging to Team %d:\n", teamId);
    printf("----------------------------------------\n");

    while (temp != NULL)
    {
        if (temp->teamId == teamId)
        {
            printf("ID: %d | Name: %s | Role: %s\n",
                   temp->playerId,
                   temp->name,
                   temp->role);

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("No players found for this team.\n");
    }
}



void sortPlayers()
{
    struct Player *i;
    struct Player *j;

    int choice;

    if (head == NULL || head->next == NULL)
    {
        printf("\nNot enough players to sort.\n");
        return;
    }

    printf("\n========== SORT PLAYERS ==========\n");

    printf("1. Sort by Player ID\n");
    printf("2. Sort by Name\n");
    printf("3. Sort by Runs\n");
    printf("4. Sort by Wickets\n");

    printf("Enter choice: ");
    scanf("%d", &choice);


    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            int swap = 0;

            if (choice == 1)
            {
                if (i->playerId > j->playerId)
                    swap = 1;
            }
            else if (choice == 2)
            {
                if (strcmp(i->name, j->name) > 0)
                    swap = 1;
            }
            else if (choice == 3)
            {
                if (i->runs < j->runs)
                    swap = 1;
            }
            else if (choice == 4)
            {
                if (i->wickets < j->wickets)
                    swap = 1;
            }
            else
            {
                printf("\nInvalid choice!\n");
                return;
            }

            if (swap)
            {
                struct Player temp;

                struct Player *next1 = i->next;
                struct Player *next2 = j->next;

                temp = *i;
                *i = *j;
                *j = temp;

                i->next = next1;
                j->next = next2;
            }
        }
    }

    printf("\nPlayers sorted successfully!\n");
}

void playerManagementMenu()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("          PLAYER MANAGEMENT SYSTEM\n");
        printf("============================================\n");

        printf("1. Add Player\n");
        printf("2. Display All Players\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Delete Player\n");
        printf("6. Display Players of a Team\n");
        printf("7. Sort Players\n");
        printf("0. Exit Player Management\n");

        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPlayer();
                break;

            case 2:
                displayPlayers();
                break;

            case 3:
                searchPlayer();
                break;

            case 4:
                updatePlayer();
                break;

            case 5:
                deletePlayer();
                break;

            case 6:
                displayTeamPlayers();
                break;

            case 7:
                sortPlayers();
                break;

            case 0:
                printf("\nReturning to main application...\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);
}


void freePlayers()
{
    struct Player *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp);
    }
}


int main()
{
    playerManagementMenu();

    
    freePlayers();

    printf("\nProgram terminated successfully.\n");

    return 0;
}