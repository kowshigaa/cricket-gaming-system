#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 11

struct Player
{
    int id;
    char name[30];
    int runs;
    int balls;
    int fours;
    int sixes;
    int wickets;
    int runsConceded;
    float overs;
};

struct Player players[MAX_PLAYERS];
int playerCount = 0;

float strikeRate(struct Player p)
{
    if (p.balls == 0)
        return 0;

    return ((float)p.runs / p.balls) * 100;
}

float economyRate(struct Player p)
{
    if (p.overs == 0)
        return 0;

    return p.runsConceded / p.overs;
}

void addPlayer()
{
    if (playerCount >= MAX_PLAYERS)
    {
        printf("\nMaximum 11 players can be added!\n");
        return;
    }

    printf("\nEnter Player ID: ");
    scanf("%d", &players[playerCount].id);

    printf("Enter Player Name: ");
    scanf(" %[^\n]", players[playerCount].name);

    players[playerCount].runs = 0;
    players[playerCount].balls = 0;
    players[playerCount].fours = 0;
    players[playerCount].sixes = 0;
    players[playerCount].wickets = 0;
    players[playerCount].runsConceded = 0;
    players[playerCount].overs = 0;

    playerCount++;

    printf("\nPlayer added successfully!\n");
}

void updateBatting()
{
    int id, runs, balls, fours, sixes;
    int i;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            printf("Enter Runs Scored: ");
            scanf("%d", &runs);

            printf("Enter Balls Faced: ");
            scanf("%d", &balls);

            printf("Enter Number of Fours: ");
            scanf("%d", &fours);

            printf("Enter Number of Sixes: ");
            scanf("%d", &sixes);

            players[i].runs += runs;
            players[i].balls += balls;
            players[i].fours += fours;
            players[i].sixes += sixes;

            printf("\nBatting score updated successfully!\n");
            return;
        }
    }

    printf("\nPlayer not found!\n");
}

void updateBowling()
{
    int id, runs, wickets;
    float overs;
    int i;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            printf("Enter Overs Bowled: ");
            scanf("%f", &overs);

            printf("Enter Runs Conceded: ");
            scanf("%d", &runs);

            printf("Enter Wickets Taken: ");
            scanf("%d", &wickets);

            players[i].overs += overs;
            players[i].runsConceded += runs;
            players[i].wickets += wickets;

            printf("\nBowling score updated successfully!\n");
            return;
        }
    }

    printf("\nPlayer not found!\n");
}

void displayTeamScore()
{
    int i;
    int totalRuns = 0;

    for (i = 0; i < playerCount; i++)
    {
        totalRuns += players[i].runs;
    }

    printf("\nCRICKET SCOREBOARD\n");
    printf("Team Runs: %d\n", totalRuns);
}

void displayBattingScoreboard()
{
    int i;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    printf("\nBATTING SCOREBOARD\n");
    printf("ID\tName\t\tRuns\tBalls\t4s\t6s\tStrike Rate\n");

    for (i = 0; i < playerCount; i++)
    {
        printf("%d\t%-15s\t%d\t%d\t%d\t%d\t%.2f\n",
               players[i].id,
               players[i].name,
               players[i].runs,
               players[i].balls,
               players[i].fours,
               players[i].sixes,
               strikeRate(players[i]));
    }
}

void displayBowlingScoreboard()
{
    int i;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    printf("\nBOWLING SCOREBOARD\n");
    printf("ID\tName\t\tOvers\tRuns\tWickets\tEconomy\n");

    for (i = 0; i < playerCount; i++)
    {
        printf("%d\t%-15s\t%.1f\t%d\t%d\t%.2f\n",
               players[i].id,
               players[i].name,
               players[i].overs,
               players[i].runsConceded,
               players[i].wickets,
               economyRate(players[i]));
    }
}

void searchPlayer()
{
    int id;
    int i;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            printf("\nPLAYER SCORECARD\n");
            printf("Player ID     : %d\n", players[i].id);
            printf("Player Name   : %s\n", players[i].name);

            printf("\nBATTING\n");
            printf("Runs          : %d\n", players[i].runs);
            printf("Balls         : %d\n", players[i].balls);
            printf("Fours         : %d\n", players[i].fours);
            printf("Sixes         : %d\n", players[i].sixes);
            printf("Strike Rate   : %.2f\n",
                   strikeRate(players[i]));

            printf("\nBOWLING\n");
            printf("Overs         : %.1f\n", players[i].overs);
            printf("Runs Conceded : %d\n", players[i].runsConceded);
            printf("Wickets       : %d\n", players[i].wickets);
            printf("Economy Rate  : %.2f\n",
                   economyRate(players[i]));

            return;
        }
    }

    printf("\nPlayer not found!\n");
}

int main()
{
    int choice;

    do
    {
        printf("\nCRICKET SCOREBOARD\n");
        printf("1. Add Player\n");
        printf("2. Update Batting Score\n");
        printf("3. Update Bowling Score\n");
        printf("4. Display Team Score\n");
        printf("5. Display Batting Scoreboard\n");
        printf("6. Display Bowling Scoreboard\n");
        printf("7. Search Player\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPlayer();
                break;

            case 2:
                updateBatting();
                break;

            case 3:
                updateBowling();
                break;

            case 4:
                displayTeamScore();
                break;

            case 5:
                displayBattingScoreboard();
                break;

            case 6:
                displayBowlingScoreboard();
                break;

            case 7:
                searchPlayer();
                break;

            case 0:
                printf("\nExiting Cricket Scoreboard...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
