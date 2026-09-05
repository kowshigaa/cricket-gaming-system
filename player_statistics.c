#include <stdio.h>
#include <string.h>

#define MAX_PLAYERS 50

// Structure to store player statistics
struct Player
{
    int id;
    char name[30];

    // Batting statistics
    int matches;
    int innings;
    int runs;
    int balls;
    int highestScore;
    int fifties;
    int hundreds;

    // Bowling statistics
    float overs;
    int runsConceded;
    int wickets;
};

// Global array of players
struct Player players[MAX_PLAYERS];

int playerCount = 0;


// --------------------------------------------------
// Calculate Batting Average
// --------------------------------------------------
float battingAverage(struct Player p)
{
    if (p.innings == 0)
        return 0;

    return (float)p.runs / p.innings;
}


// --------------------------------------------------
// Calculate Strike Rate
// --------------------------------------------------
float strikeRate(struct Player p)
{
    if (p.balls == 0)
        return 0;

    return ((float)p.runs / p.balls) * 100;
}


// --------------------------------------------------
// Calculate Bowling Economy
// --------------------------------------------------
float economyRate(struct Player p)
{
    if (p.overs == 0)
        return 0;

    return p.runsConceded / p.overs;
}


// --------------------------------------------------
// Add Player
// --------------------------------------------------
void addPlayer()
{
    if (playerCount >= MAX_PLAYERS)
    {
        printf("\nPlayer limit reached!\n");
        return;
    }

    printf("\nEnter Player ID: ");
    scanf("%d", &players[playerCount].id);

    printf("Enter Player Name: ");
    scanf(" %[^\n]", players[playerCount].name);

    players[playerCount].matches = 0;
    players[playerCount].innings = 0;
    players[playerCount].runs = 0;
    players[playerCount].balls = 0;
    players[playerCount].highestScore = 0;
    players[playerCount].fifties = 0;
    players[playerCount].hundreds = 0;

    players[playerCount].overs = 0;
    players[playerCount].runsConceded = 0;
    players[playerCount].wickets = 0;

    playerCount++;

    printf("\nPlayer added successfully!\n");
}


// --------------------------------------------------
// Display One Player
// --------------------------------------------------
void displayPlayer(struct Player p)
{
    printf("\n-----------------------------------------");
    printf("\nPlayer ID       : %d", p.id);
    printf("\nPlayer Name     : %s", p.name);

    printf("\n\nBATTTING STATISTICS");
    printf("\nMatches         : %d", p.matches);
    printf("\nInnings         : %d", p.innings);
    printf("\nRuns            : %d", p.runs);
    printf("\nBalls           : %d", p.balls);
    printf("\nHighest Score   : %d", p.highestScore);
    printf("\nBatting Average : %.2f", battingAverage(p));
    printf("\nStrike Rate     : %.2f", strikeRate(p));
    printf("\n50s             : %d", p.fifties);
    printf("\n100s            : %d", p.hundreds);

    printf("\n\nBOWLING STATISTICS");
    printf("\nOvers           : %.1f", p.overs);
    printf("\nRuns Conceded   : %d", p.runsConceded);
    printf("\nWickets         : %d", p.wickets);
    printf("\nEconomy Rate    : %.2f", economyRate(p));

    printf("\n-----------------------------------------\n");
}


// --------------------------------------------------
// Display All Players
// --------------------------------------------------
void displayAllPlayers()
{
    int i;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    printf("\n============================================================");
    printf("\n                 ALL PLAYER STATISTICS");
    printf("\n============================================================");

    printf("\n%-5s %-15s %-8s %-8s %-8s %-8s",
           "ID", "NAME", "MATCH", "RUNS", "WICKETS", "AVG");

    printf("\n------------------------------------------------------------");

    for (i = 0; i < playerCount; i++)
    {
        printf("\n%-5d %-15s %-8d %-8d %-8d %-8.2f",
               players[i].id,
               players[i].name,
               players[i].matches,
               players[i].runs,
               players[i].wickets,
               battingAverage(players[i]));
    }

    printf("\n============================================================\n");
}


// --------------------------------------------------
// Search Player By ID
// Linear Search
// --------------------------------------------------
void searchByID()
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            displayPlayer(players[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nPlayer not found!\n");
}


// --------------------------------------------------
// Search Player By Name
// Linear Search
// --------------------------------------------------
void searchByName()
{
    char name[30];
    int i;
    int found = 0;

    printf("\nEnter Player Name: ");
    scanf(" %[^\n]", name);

    for (i = 0; i < playerCount; i++)
    {
        if (strcmp(players[i].name, name) == 0)
        {
            displayPlayer(players[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nPlayer not found!\n");
}


// --------------------------------------------------
// Update Batting Statistics
// --------------------------------------------------
void updateBatting()
{
    int id;
    int i;
    int runs;
    int balls;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            printf("Enter runs scored: ");
            scanf("%d", &runs);

            printf("Enter balls faced: ");
            scanf("%d", &balls);

            players[i].innings++;
            players[i].runs += runs;
            players[i].balls += balls;

            if (runs > players[i].highestScore)
                players[i].highestScore = runs;

            if (runs >= 50 && runs < 100)
                players[i].fifties++;

            if (runs >= 100)
                players[i].hundreds++;

            printf("\nBatting statistics updated successfully!\n");

            return;
        }
    }

    printf("\nPlayer not found!\n");
}


// --------------------------------------------------
// Update Bowling Statistics
// --------------------------------------------------
void updateBowling()
{
    int id;
    float overs;
    int runs;
    int wickets;
    int i;

    printf("\nEnter Player ID: ");
    scanf("%d", &id);

    for (i = 0; i < playerCount; i++)
    {
        if (players[i].id == id)
        {
            printf("Enter overs bowled: ");
            scanf("%f", &overs);

            printf("Enter runs conceded: ");
            scanf("%d", &runs);

            printf("Enter wickets taken: ");
            scanf("%d", &wickets);

            players[i].overs += overs;
            players[i].runsConceded += runs;
            players[i].wickets += wickets;

            printf("\nBowling statistics updated successfully!\n");

            return;
        }
    }

    printf("\nPlayer not found!\n");
}


// --------------------------------------------------
// Swap Players
// --------------------------------------------------
void swap(struct Player *a, struct Player *b)
{
    struct Player temp;

    temp = *a;
    *a = *b;
    *b = temp;
}


// --------------------------------------------------
// Sort By Runs
// Bubble Sort
// --------------------------------------------------
void sortByRuns()
{
    int i, j;

    for (i = 0; i < playerCount - 1; i++)
    {
        for (j = 0; j < playerCount - i - 1; j++)
        {
            if (players[j].runs < players[j + 1].runs)
            {
                swap(&players[j], &players[j + 1]);
            }
        }
    }
}


// --------------------------------------------------
// Display Top Run Scorers
// --------------------------------------------------
void topRunScorers()
{
    int i;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    sortByRuns();

    printf("\n============================================");
    printf("\n              TOP RUN SCORERS");
    printf("\n============================================");

    printf("\n%-5s %-15s %-10s",
           "Rank", "Player", "Runs");

    printf("\n--------------------------------------------");

    for (i = 0; i < playerCount; i++)
    {
        printf("\n%-5d %-15s %-10d",
               i + 1,
               players[i].name,
               players[i].runs);
    }

    printf("\n============================================\n");
}


// --------------------------------------------------
// Sort By Wickets
// Bubble Sort
// --------------------------------------------------
void sortByWickets()
{
    int i, j;

    for (i = 0; i < playerCount - 1; i++)
    {
        for (j = 0; j < playerCount - i - 1; j++)
        {
            if (players[j].wickets < players[j + 1].wickets)
            {
                swap(&players[j], &players[j + 1]);
            }
        }
    }
}


// --------------------------------------------------
// Display Top Wicket Takers
// --------------------------------------------------
void topWicketTakers()
{
    int i;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    sortByWickets();

    printf("\n============================================");
    printf("\n              TOP WICKET TAKERS");
    printf("\n============================================");

    printf("\n%-5s %-15s %-10s",
           "Rank", "Player", "Wickets");

    printf("\n--------------------------------------------");

    for (i = 0; i < playerCount; i++)
    {
        printf("\n%-5d %-15s %-10d",
               i + 1,
               players[i].name,
               players[i].wickets);
    }

    printf("\n============================================\n");
}


// --------------------------------------------------
// Player Ranking
// Ranking based on Runs + Wickets
// --------------------------------------------------
int playerScore(struct Player p)
{
    return p.runs + (p.wickets * 20);
}


void playerRanking()
{
    int i, j;

    if (playerCount == 0)
    {
        printf("\nNo players available!\n");
        return;
    }

    // Sort according to ranking score
    for (i = 0; i < playerCount - 1; i++)
    {
        for (j = 0; j < playerCount - i - 1; j++)
        {
            if (playerScore(players[j]) <
                playerScore(players[j + 1]))
            {
                swap(&players[j], &players[j + 1]);
            }
        }
    }

    printf("\n==================================================");
    printf("\n                 PLAYER RANKING");
    printf("\n==================================================");

    printf("\n%-6s %-15s %-10s %-10s",
           "Rank", "Player", "Runs", "Wickets");

    printf("\n--------------------------------------------------");

    for (i = 0; i < playerCount; i++)
    {
        printf("\n%-6d %-15s %-10d %-10d",
               i + 1,
               players[i].name,
               players[i].runs,
               players[i].wickets);
    }

    printf("\n==================================================\n");
}


// --------------------------------------------------
// Main Menu
// --------------------------------------------------
int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("==============================================\n");
        printf("          PLAYER STATISTICS MODULE\n");
        printf("==============================================\n");

        printf("1. Add Player\n");
        printf("2. Display All Player Statistics\n");
        printf("3. Search Player By ID\n");
        printf("4. Search Player By Name\n");
        printf("5. Update Batting Statistics\n");
        printf("6. Update Bowling Statistics\n");
        printf("7. Top Run Scorers\n");
        printf("8. Top Wicket Takers\n");
        printf("9. Player Ranking\n");
        printf("0. Exit\n");

        printf("==============================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addPlayer();
                break;

            case 2:
                displayAllPlayers();
                break;

            case 3:
                searchByID();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                updateBatting();
                break;

            case 6:
                updateBowling();
                break;

            case 7:
                topRunScorers();
                break;

            case 8:
                topWicketTakers();
                break;

            case 9:
                playerRanking();
                break;

            case 0:
                printf("\nExiting Player Statistics Module...\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 0);

    return 0;
}