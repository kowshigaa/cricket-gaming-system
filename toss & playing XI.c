#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Team
{
    char name[30];
    char players[15][30];
};

void displayPlayers(struct Team *team)
{
    int i;

    printf("\n%s Players:\n", team->name);

    for(i = 0; i < 15; i++)
    {
        printf("%d. %s\n", i + 1, team->players[i]);
    }
}

void toss(struct Team *team1, struct Team *team2)
{
    int result;
    char choice[10];

    srand(time(NULL));

    result = rand() % 2;

    printf("\n========== TOSS ==========\n");

    if(result == 0)
    {
        printf("Toss Winner: %s\n", team1->name);

        printf("Choose Bat or Bowl: ");
        scanf("%s", choice);

        while(strcmp(choice, "Bat") != 0 &&
              strcmp(choice, "bat") != 0 &&
              strcmp(choice, "Bowl") != 0 &&
              strcmp(choice, "bowl") != 0)
        {
            printf("Invalid choice! Enter Bat or Bowl: ");
            scanf("%s", choice);
        }

        printf("%s chose to %s\n", team1->name, choice);
    }
    else
    {
        printf("Toss Winner: %s\n", team2->name);

        printf("Choose Bat or Bowl: ");
        scanf("%s", choice);

        while(strcmp(choice, "Bat") != 0 &&
              strcmp(choice, "bat") != 0 &&
              strcmp(choice, "Bowl") != 0 &&
              strcmp(choice, "bowl") != 0)
        {
            printf("Invalid choice! Enter Bat or Bowl: ");
            scanf("%s", choice);
        }

        printf("%s chose to %s\n", team2->name, choice);
    }
}

void selectPlayingXI(struct Team *team, char playingXI[11][30])
{
    int selected[15] = {0};
    int choice;
    int count = 0;

    displayPlayers(team);

    printf("\nSelect 11 players for %s\n", team->name);

    while(count < 11)
    {
        printf("Enter player number: ");
        scanf("%d", &choice);

        if(choice < 1 || choice > 15)
        {
            printf("Invalid player number!\n");
        }
        else if(selected[choice - 1] == 1)
        {
            printf("Player already selected!\n");
        }
        else
        {
            selected[choice - 1] = 1;

            strcpy(playingXI[count], team->players[choice - 1]);

            printf("%s selected.\n",
                   team->players[choice - 1]);

            count++;
        }
    }
}

void displayPlayingXI(char teamName[30], char playingXI[11][30])
{
    int i;

    printf("\n========== %s PLAYING XI ==========\n",
           teamName);

    for(i = 0; i < 11; i++)
    {
        printf("%d. %s\n", i + 1, playingXI[i]);
    }
}

int main()
{
    struct Team team1 =
    {
        "INDIA",
        {
            "Rohit Sharma",
            "Shubman Gill",
            "Virat Kohli",
            "KL Rahul",
            "Rishabh Pant",
            "Hardik Pandya",
            "Ravindra Jadeja",
            "Kuldeep Yadav",
            "Jasprit Bumrah",
            "Mohammed Siraj",
            "Arshdeep Singh",
            "Axar Patel",
            "Washington Sundar",
            "Yashasvi Jaiswal",
            "Sanju Samson"
        }
    };

    struct Team team2 =
    {
        "AUSTRALIA",
        {
            "David Warner",
            "Travis Head",
            "Steve Smith",
            "Marnus Labuschagne",
            "Glenn Maxwell",
            "Josh Inglis",
            "Mitchell Marsh",
            "Pat Cummins",
            "Mitchell Starc",
            "Adam Zampa",
            "Josh Hazlewood",
            "Nathan Lyon",
            "Alex Carey",
            "Cameron Green",
            "Marcus Stoinis"
        }
    };

    char indiaXI[11][30];
    char australiaXI[11][30];

    printf("========================================\n");
    printf("       CRICKET GAMING APPLICATION\n");
    printf("========================================\n");

    printf("\nTeams:\n");
    printf("1. %s\n", team1.name);
    printf("2. %s\n", team2.name);

    /* Toss */
    toss(&team1, &team2);

    /* Playing XI Selection */
    printf("\n========================================\n");
    printf("          PLAYING XI SELECTION\n");
    printf("========================================\n");

    selectPlayingXI(&team1, indiaXI);

    selectPlayingXI(&team2, australiaXI);

    /* Display Playing XI */
    displayPlayingXI(team1.name, indiaXI);

    displayPlayingXI(team2.name, australiaXI);

    printf("\n========================================\n");
    printf("             MATCH READY!\n");
    printf("========================================\n");

    return 0;
}