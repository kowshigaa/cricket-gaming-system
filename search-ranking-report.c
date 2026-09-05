#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS 50
#define MAX_TEAMS 20
#define MAX_MATCHES 50

struct Team
{
    int teamId;
    char name[50];
};

struct Player
{
    int playerId;
    char name[50];
    int teamId;
    char role[30];
    int runs;
    int wickets;
    float strikeRate;
    float average;
};

struct Match
{
    int matchId;
    int team1;
    int team2;
    int score1;
    int score2;
};

struct Node
{
    int playerId;
    struct Node *left;
    struct Node *right;
};

struct Team teams[MAX_TEAMS];
struct Player players[MAX_PLAYERS];
struct Match matches[MAX_MATCHES];

int teamCount, playerCount, matchCount;

void showPlayer(struct Player p)
{
    printf("ID: %d\n", p.playerId);
    printf("Name: %s\n", p.name);
    printf("Team ID: %d\n", p.teamId);
    printf("Role: %s\n", p.role);
    printf("Runs: %d\n", p.runs);
    printf("Wickets: %d\n", p.wickets);
    printf("Strike Rate: %.2f\n", p.strikeRate);
    printf("Average: %.2f\n", p.average);
}

void inputData()
{
    int i;

    printf("Enter number of teams: ");
    scanf("%d", &teamCount);

    for(i = 0; i < teamCount; i++)
    {
        printf("Enter Team ID: ");
        scanf("%d", &teams[i].teamId);

        printf("Enter Team Name: ");
        scanf(" %[^\n]", teams[i].name);
    }

    printf("Enter number of players: ");
    scanf("%d", &playerCount);

    for(i = 0; i < playerCount; i++)
    {
        printf("Enter Player ID: ");
        scanf("%d", &players[i].playerId);

        printf("Enter Player Name: ");
        scanf(" %[^\n]", players[i].name);

        printf("Enter Team ID: ");
        scanf("%d", &players[i].teamId);

        printf("Enter Role: ");
        scanf(" %[^\n]", players[i].role);

        printf("Enter Runs: ");
        scanf("%d", &players[i].runs);

        printf("Enter Wickets: ");
        scanf("%d", &players[i].wickets);

        printf("Enter Strike Rate: ");
        scanf("%f", &players[i].strikeRate);

        printf("Enter Average: ");
        scanf("%f", &players[i].average);
    }

    printf("Enter number of matches: ");
    scanf("%d", &matchCount);

    for(i = 0; i < matchCount; i++)
    {
        printf("Enter Match ID: ");
        scanf("%d", &matches[i].matchId);

        printf("Enter Team 1 ID: ");
        scanf("%d", &matches[i].team1);

        printf("Enter Team 2 ID: ");
        scanf("%d", &matches[i].team2);

        printf("Enter Team 1 Score: ");
        scanf("%d", &matches[i].score1);

        printf("Enter Team 2 Score: ");
        scanf("%d", &matches[i].score2);
    }
}

void searchPlayer()
{
    int id, i;

    printf("Enter Player ID: ");
    scanf("%d", &id);

    for(i = 0; i < playerCount; i++)
    {
        if(players[i].playerId == id)
        {
            showPlayer(players[i]);
            return;
        }
    }

    printf("Player not found\n");
}

void searchTeam()
{
    int id, i;

    printf("Enter Team ID: ");
    scanf("%d", &id);

    for(i = 0; i < teamCount; i++)
    {
        if(teams[i].teamId == id)
        {
            printf("Team ID: %d\n", teams[i].teamId);
            printf("Team Name: %s\n", teams[i].name);
            return;
        }
    }

    printf("Team not found\n");
}

void searchMatch()
{
    int id, i;

    printf("Enter Match ID: ");
    scanf("%d", &id);

    for(i = 0; i < matchCount; i++)
    {
        if(matches[i].matchId == id)
        {
            printf("Match ID: %d\n", matches[i].matchId);
            printf("Team 1: %d\n", matches[i].team1);
            printf("Team 2: %d\n", matches[i].team2);
            printf("Score 1: %d\n", matches[i].score1);
            printf("Score 2: %d\n", matches[i].score2);
            return;
        }
    }

    printf("Match not found\n");
}

void rankPlayers()
{
    int i, j;
    struct Player temp;

    for(i = 0; i < playerCount - 1; i++)
    {
        for(j = 0; j < playerCount - i - 1; j++)
        {
            if(players[j].runs < players[j + 1].runs)
            {
                temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("Player Ranking by Runs\n");

    for(i = 0; i < playerCount; i++)
    {
        printf("%d. %s - %d runs\n",
               i + 1,
               players[i].name,
               players[i].runs);
    }
}

struct Node* createNode(int id)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->playerId = id;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node *root, int id)
{
    if(root == NULL)
        return createNode(id);

    if(id < root->playerId)
        root->left = insert(root->left, id);
    else if(id > root->playerId)
        root->right = insert(root->right, id);

    return root;
}

struct Node* search(struct Node *root, int id)
{
    if(root == NULL || root->playerId == id)
        return root;

    if(id < root->playerId)
        return search(root->left, id);

    return search(root->right, id);
}

void display(struct Node *root)
{
    if(root != NULL)
    {
        display(root->left);
        printf("%d ", root->playerId);
        display(root->right);
    }
}

int main()
{
    int choice, id;
    struct Node *root = NULL;
    struct Node *result;
    int i;

    inputData();

    for(i = 0; i < playerCount; i++)
        root = insert(root, players[i].playerId);

    while(1)
    {
        printf("\n1. Search Player");
        printf("\n2. Search Team");
        printf("\n3. Search Match");
        printf("\n4. Rank Players");
        printf("\n5. Search Player ID using BST");
        printf("\n6. Display BST");
        printf("\n7. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                searchPlayer();
                break;

            case 2:
                searchTeam();
                break;

            case 3:
                searchMatch();
                break;

            case 4:
                rankPlayers();
                break;

            case 5:
                printf("Enter Player ID: ");
                scanf("%d", &id);

                result = search(root, id);

                if(result != NULL)
                    printf("Player ID found\n");
                else
                    printf("Player ID not found\n");
                break;

            case 6:
                printf("BST: ");
                display(root);
                printf("\n");
                break;

            case 7:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}