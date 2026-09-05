#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define MAX_TEAMS 50
#define TOP_TEAMS 4

typedef struct {
    char name[NAME_SIZE];
    int played;
    int won;
    int lost;
    int tied;
    int noResult;
    int points;
    int runsScored;
    int ballsFaced;
    int runsConceded;
    int ballsBowled;
    float nrr;
} Team;

typedef struct {
    char name[NAME_SIZE];
    int teamCount;
    Team *teams;
    int qualified[TOP_TEAMS];
    int qualifiedCount;
    int semi1Team1, semi1Team2;
    int semi2Team1, semi2Team2;
    int semi1Completed, semi2Completed;
    int finalTeam1, finalTeam2;
    int finalCompleted;
    int winner;
} Tournament;

void clearBuffer(void);
void readLine(char text[], int size);
int readInt(char message[], int min, int max);
int oversToBalls(float overs);
int readOvers(char message[]);
void initializeTeam(Team *team);
int findTeam(Tournament *t, char name[]);
int findTeamBefore(Tournament *t, char name[], int count);
void calculateNRR(Tournament *t);
int betterTeam(Team *a, Team *b);
int *getRanking(Tournament *t);
void displayTeams(Tournament *t);
void recordLeagueMatch(Tournament *t);
void displayPointsTable(Tournament *t);
void determineTop4(Tournament *t);
void displayTop4(Tournament *t);
void createSemiFinals(Tournament *t);
void recordSemiFinal(Tournament *t);
void recordFinal(Tournament *t);
void displayStatus(Tournament *t);
void freeTournament(Tournament *t);
void createTournament(Tournament *t);

void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readLine(char text[], int size)
{
    fgets(text, size, stdin);
    text[strcspn(text, "\n")] = '\0';
}

int readInt(char message[], int min, int max)
{
    int value;
    while (1)
    {
        printf("%s", message);
        if (scanf("%d", &value) == 1 && value >= min && value <= max)
        {
            clearBuffer();
            return value;
        }
        printf("Invalid input. Try again.\n");
        clearBuffer();
    }
}

int oversToBalls(float overs)
{
    int whole, extra;
    whole = (int)overs;
    extra = (int)((overs - whole) * 10 + 0.01);
    if (extra < 0 || extra > 5)
        return -1;
    return whole * 6 + extra;
}

int readOvers(char message[])
{
    float overs;
    int balls;
    while (1)
    {
        printf("%s", message);
        if (scanf("%f", &overs) == 1 && overs >= 0)
        {
            clearBuffer();
            balls = oversToBalls(overs);
            if (balls > 0)
                return balls;
        }
        printf("Invalid overs. Use values like 20, 19.4 or 10.2.\n");
        clearBuffer();
    }
}

void initializeTeam(Team *team)
{
    team->played = 0;
    team->won = 0;
    team->lost = 0;
    team->tied = 0;
    team->noResult = 0;
    team->points = 0;
    team->runsScored = 0;
    team->ballsFaced = 0;
    team->runsConceded = 0;
    team->ballsBowled = 0;
    team->nrr = 0;
}

int findTeam(Tournament *t, char name[])
{
    int i;
    for (i = 0; i < t->teamCount; i++)
    {
        if (strcmp(t->teams[i].name, name) == 0)
            return i;
    }
    return -1;
}

int findTeamBefore(Tournament *t, char name[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        if (strcmp(t->teams[i].name, name) == 0)
            return i;
    }
    return -1;
}

void calculateNRR(Tournament *t)
{
    int i;
    float runRateFor, runRateAgainst;
    for (i = 0; i < t->teamCount; i++)
    {
        if (t->teams[i].ballsFaced > 0 && t->teams[i].ballsBowled > 0)
        {
            runRateFor = (float)t->teams[i].runsScored * 6 /
                         t->teams[i].ballsFaced;
            runRateAgainst = (float)t->teams[i].runsConceded * 6 /
                             t->teams[i].ballsBowled;
            t->teams[i].nrr = runRateFor - runRateAgainst;
        }
        else
        {
            t->teams[i].nrr = 0;
        }
    }
}

int betterTeam(Team *a, Team *b)
{
    if (a->points != b->points)
        return a->points > b->points;
    if (a->nrr != b->nrr)
        return a->nrr > b->nrr;
    if (a->won != b->won)
        return a->won > b->won;
    return strcmp(a->name, b->name) < 0;
}

int *getRanking(Tournament *t)
{
    int *rank;
    int i, j, temp;

    rank = malloc(t->teamCount * sizeof(int));
    if (rank == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for (i = 0; i < t->teamCount; i++)
        rank[i] = i;

    for (i = 0; i < t->teamCount - 1; i++)
    {
        for (j = 0; j < t->teamCount - i - 1; j++)
        {
            if (!betterTeam(&t->teams[rank[j]],
                            &t->teams[rank[j + 1]]))
            {
                temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
        }
    }
    return rank;
}

void displayTeams(Tournament *t)
{
    int i;
    printf("\n========== TEAMS ==========\n");
    for (i = 0; i < t->teamCount; i++)
        printf("%d. %s\n", i + 1, t->teams[i].name);
}

void recordLeagueMatch(Tournament *t)
{
    int team1, team2;
    int runs1, runs2;
    int balls1, balls2;
    int allOut1, allOut2;
    int quotaBalls;

    printf("\n========== LEAGUE MATCH ==========\n");
    displayTeams(t);

    team1 = readInt("Enter Team 1 number: ", 1, t->teamCount) - 1;
    team2 = readInt("Enter Team 2 number: ", 1, t->teamCount) - 1;

    if (team1 == team2)
    {
        printf("A team cannot play against itself.\n");
        return;
    }

    printf("\n%s vs %s\n",
           t->teams[team1].name,
           t->teams[team2].name);

    runs1 = readInt("Enter runs scored by Team 1: ", 0, 1000);
    balls1 = readOvers("Enter overs faced by Team 1: ");
    runs2 = readInt("Enter runs scored by Team 2: ", 0, 1000);
    balls2 = readOvers("Enter overs faced by Team 2: ");

    allOut1 = readInt("Was Team 1 all out? (1=Yes, 0=No): ", 0, 1);
    allOut2 = readInt("Was Team 2 all out? (1=Yes, 0=No): ", 0, 1);

    if (allOut1 == 1 || allOut2 == 1)
    {
        quotaBalls = readOvers("Enter full innings quota in overs: ");
        if (allOut1 == 1)
            balls1 = quotaBalls;
        if (allOut2 == 1)
            balls2 = quotaBalls;
    }

    t->teams[team1].played++;
    t->teams[team2].played++;

    t->teams[team1].runsScored += runs1;
    t->teams[team1].ballsFaced += balls1;
    t->teams[team1].runsConceded += runs2;
    t->teams[team1].ballsBowled += balls2;

    t->teams[team2].runsScored += runs2;
    t->teams[team2].ballsFaced += balls2;
    t->teams[team2].runsConceded += runs1;
    t->teams[team2].ballsBowled += balls1;

    printf("\n========== MATCH RESULT ==========\n");
    printf("%s: %d runs in %.1f overs\n",
           t->teams[team1].name,
           runs1,
           balls1 / 6.0);
    printf("%s: %d runs in %.1f overs\n",
           t->teams[team2].name,
           runs2,
           balls2 / 6.0);

    if (runs1 > runs2)
    {
        t->teams[team1].won++;
        t->teams[team2].lost++;
        t->teams[team1].points += 2;
        printf("Winner: %s\n", t->teams[team1].name);
    }
    else if (runs2 > runs1)
    {
        t->teams[team2].won++;
        t->teams[team1].lost++;
        t->teams[team2].points += 2;
        printf("Winner: %s\n", t->teams[team2].name);
    }
    else
    {
        t->teams[team1].tied++;
        t->teams[team2].tied++;
        t->teams[team1].points++;
        t->teams[team2].points++;
        printf("Match Result: Tie\n");
    }

    calculateNRR(t);
}

void displayPointsTable(Tournament *t)
{
    int *rank;
    int i, index;

    calculateNRR(t);
    rank = getRanking(t);

    if (rank == NULL)
        return;

    printf("\n============================================================\n");
    printf("                     %s\n", t->name);
    printf("                    POINTS TABLE\n");
    printf("============================================================\n");

    printf("%-5s %-15s %-4s %-4s %-4s %-4s %-4s %-5s %-7s\n",
           "Rank", "Team", "P", "W", "L", "T", "NR", "Pts", "NRR");

    printf("------------------------------------------------------------\n");

    for (i = 0; i < t->teamCount; i++)
    {
        index = rank[i];

        printf("%-5d %-15s %-4d %-4d %-4d %-4d %-4d %-5d %+.2f\n",
               i + 1,
               t->teams[index].name,
               t->teams[index].played,
               t->teams[index].won,
               t->teams[index].lost,
               t->teams[index].tied,
               t->teams[index].noResult,
               t->teams[index].points,
               t->teams[index].nrr);
    }

    printf("============================================================\n");
    free(rank);
}

void determineTop4(Tournament *t)
{
    int *rank;
    int i;

    if (t->teamCount < TOP_TEAMS)
    {
        printf("At least 4 teams are required.\n");
        return;
    }

    calculateNRR(t);
    rank = getRanking(t);

    if (rank == NULL)
        return;

    t->qualifiedCount = TOP_TEAMS;

    for (i = 0; i < TOP_TEAMS; i++)
        t->qualified[i] = rank[i];

    printf("\n========== TOP 4 TEAMS ==========\n");

    for (i = 0; i < TOP_TEAMS; i++)
        printf("%d. %s\n",
               i + 1,
               t->teams[t->qualified[i]].name);

    free(rank);
}

void displayTop4(Tournament *t)
{
    int i;

    if (t->qualifiedCount != TOP_TEAMS)
    {
        printf("Top 4 teams are not determined yet.\n");
        return;
    }

    printf("\n========== QUALIFIED TEAMS ==========\n");

    for (i = 0; i < TOP_TEAMS; i++)
        printf("%d. %s\n",
               i + 1,
               t->teams[t->qualified[i]].name);
}

void createSemiFinals(Tournament *t)
{
    if (t->qualifiedCount != TOP_TEAMS)
    {
        printf("Please determine Top 4 teams first.\n");
        return;
    }

    t->semi1Team1 = t->qualified[0];
    t->semi1Team2 = t->qualified[3];
    t->semi2Team1 = t->qualified[1];
    t->semi2Team2 = t->qualified[2];

    t->semi1Completed = 0;
    t->semi2Completed = 0;
    t->finalTeam1 = -1;
    t->finalTeam2 = -1;
    t->finalCompleted = 0;
    t->winner = -1;

    printf("\n========== SEMI-FINALS ==========\n");
    printf("Semi-Final 1: %s vs %s\n",
           t->teams[t->semi1Team1].name,
           t->teams[t->semi1Team2].name);
    printf("Semi-Final 2: %s vs %s\n",
           t->teams[t->semi2Team1].name,
           t->teams[t->semi2Team2].name);
}

void recordSemiFinal(Tournament *t)
{
    int semi;
    int team1, team2;
    int runs1, runs2;
    int balls1, balls2;
    int winner;

    if (t->qualifiedCount != TOP_TEAMS)
    {
        printf("Please determine Top 4 teams first.\n");
        return;
    }

    if (t->semi1Team1 < 0 || t->semi2Team1 < 0)
        createSemiFinals(t);

    semi = readInt("\nEnter semi-final number (1 or 2): ", 1, 2);

    if (semi == 1)
    {
        if (t->semi1Completed)
        {
            printf("Semi-Final 1 is already completed.\n");
            return;
        }
        team1 = t->semi1Team1;
        team2 = t->semi1Team2;
    }
    else
    {
        if (t->semi2Completed)
        {
            printf("Semi-Final 2 is already completed.\n");
            return;
        }
        team1 = t->semi2Team1;
        team2 = t->semi2Team2;
    }

    printf("\n%s vs %s\n",
           t->teams[team1].name,
           t->teams[team2].name);

    runs1 = readInt("Enter runs scored by Team 1: ", 0, 1000);
    balls1 = readOvers("Enter overs faced by Team 1: ");
    runs2 = readInt("Enter runs scored by Team 2: ", 0, 1000);
    balls2 = readOvers("Enter overs faced by Team 2: ");

    printf("\n========== SEMI-FINAL RESULT ==========\n");
    printf("%s: %d runs in %.1f overs\n",
           t->teams[team1].name,
           runs1,
           balls1 / 6.0);
    printf("%s: %d runs in %.1f overs\n",
           t->teams[team2].name,
           runs2,
           balls2 / 6.0);

    if (runs1 > runs2)
        winner = team1;
    else if (runs2 > runs1)
        winner = team2;
    else
    {
        printf("Match is tied. Winner cannot be decided from the score.\n");
        return;
    }

    printf("Semi-Final Winner: %s\n",
           t->teams[winner].name);

    if (semi == 1)
    {
        t->semi1Completed = 1;
        t->finalTeam1 = winner;
    }
    else
    {
        t->semi2Completed = 1;
        t->finalTeam2 = winner;
    }

    if (t->semi1Completed && t->semi2Completed)
    {
        printf("\n========== FINAL READY ==========\n");
        printf("Final: %s vs %s\n",
               t->teams[t->finalTeam1].name,
               t->teams[t->finalTeam2].name);
    }
}

void recordFinal(Tournament *t)
{
    int runs1, runs2;
    int balls1, balls2;
    int winner;

    if (!t->semi1Completed || !t->semi2Completed)
    {
        printf("Both semi-finals must be completed first.\n");
        return;
    }

    if (t->finalCompleted)
    {
        printf("Final is already completed.\n");
        return;
    }

    printf("\n========== FINAL ==========\n");
    printf("%s vs %s\n",
           t->teams[t->finalTeam1].name,
           t->teams[t->finalTeam2].name);

    runs1 = readInt("Enter runs scored by Team 1: ", 0, 1000);
    balls1 = readOvers("Enter overs faced by Team 1: ");
    runs2 = readInt("Enter runs scored by Team 2: ", 0, 1000);
    balls2 = readOvers("Enter overs faced by Team 2: ");

    printf("\n========== FINAL RESULT ==========\n");
    printf("%s: %d runs in %.1f overs\n",
           t->teams[t->finalTeam1].name,
           runs1,
           balls1 / 6.0);
    printf("%s: %d runs in %.1f overs\n",
           t->teams[t->finalTeam2].name,
           runs2,
           balls2 / 6.0);

    if (runs1 > runs2)
        winner = t->finalTeam1;
    else if (runs2 > runs1)
        winner = t->finalTeam2;
    else
    {
        printf("Final is tied. Winner cannot be decided from the score.\n");
        return;
    }

    t->winner = winner;
    t->finalCompleted = 1;

    printf("Final Winner: %s\n",
           t->teams[winner].name);

    printf("\n========== TOURNAMENT WINNER ==========\n");
    printf("Tournament Winner: %s\n",
           t->teams[t->winner].name);
}

void displayStatus(Tournament *t)
{
    printf("\n========== TOURNAMENT STATUS ==========\n");

    if (t->qualifiedCount == TOP_TEAMS)
    {
        printf("Top 4: Determined\n");

        printf("Semi-Final 1: %s vs %s - %s\n",
               t->teams[t->semi1Team1].name,
               t->teams[t->semi1Team2].name,
               t->semi1Completed ? "Completed" : "Pending");

        printf("Semi-Final 2: %s vs %s - %s\n",
               t->teams[t->semi2Team1].name,
               t->teams[t->semi2Team2].name,
               t->semi2Completed ? "Completed" : "Pending");
    }
    else
    {
        printf("Top 4: Not determined\n");
    }

    if (t->semi1Completed && t->semi2Completed)
    {
        printf("Final: %s vs %s - %s\n",
               t->teams[t->finalTeam1].name,
               t->teams[t->finalTeam2].name,
               t->finalCompleted ? "Completed" : "Pending");
    }
    else
    {
        printf("Final: Not ready\n");
    }

    if (t->finalCompleted)
        printf("Winner: %s\n",
               t->teams[t->winner].name);
    else
        printf("Winner: Not decided\n");
}

void freeTournament(Tournament *t)
{
    if (t->teams != NULL)
    {
        free(t->teams);
        t->teams = NULL;
    }
    t->teamCount = 0;
}

void createTournament(Tournament *t)
{
    int i;

    printf("\n========== TOURNAMENT SETUP ==========\n");
    printf("Enter tournament name: ");
    readLine(t->name, NAME_SIZE);

    t->teamCount =
        readInt("Enter number of teams: ",
                4, MAX_TEAMS);

    t->teams =
        malloc(t->teamCount * sizeof(Team));

    if (t->teams == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (i = 0; i < t->teamCount; i++)
    {
        while (1)
        {
            printf("Enter Team %d name: ", i + 1);
            readLine(t->teams[i].name, NAME_SIZE);

            if (strlen(t->teams[i].name) == 0)
            {
                printf("Team name cannot be empty.\n");
                continue;
            }

            if (findTeamBefore(t,
                               t->teams[i].name,
                               i) != -1)
            {
                printf("Team name already exists.\n");
                continue;
            }

            break;
        }

        initializeTeam(&t->teams[i]);
    }

    t->qualifiedCount = 0;
    t->semi1Team1 = -1;
    t->semi1Team2 = -1;
    t->semi2Team1 = -1;
    t->semi2Team2 = -1;
    t->semi1Completed = 0;
    t->semi2Completed = 0;
    t->finalTeam1 = -1;
    t->finalTeam2 = -1;
    t->finalCompleted = 0;
    t->winner = -1;

    printf("\nTournament created successfully.\n");
}

int main(void)
{
    Tournament tournament;
    int choice;

    tournament.teams = NULL;
    tournament.teamCount = 0;

    createTournament(&tournament);

    do
    {
        printf("\n========== CRICKET TOURNAMENT ==========\n");
        printf("1. Display Teams\n");
        printf("2. Record League Match\n");
        printf("3. Display Points Table\n");
        printf("4. Determine Top 4\n");
        printf("5. Display Top 4\n");
        printf("6. Create Semi-Finals\n");
        printf("7. Record Semi-Final\n");
        printf("8. Record Final\n");
        printf("9. Display Status\n");
        printf("10. Exit\n");

        choice = readInt("Enter choice: ", 1, 10);

        switch (choice)
        {
            case 1:
                displayTeams(&tournament);
                break;
            case 2:
                recordLeagueMatch(&tournament);
                break;
            case 3:
                displayPointsTable(&tournament);
                break;
            case 4:
                determineTop4(&tournament);
                break;
            case 5:
                displayTop4(&tournament);
                break;
            case 6:
                createSemiFinals(&tournament);
                break;
            case 7:
                recordSemiFinal(&tournament);
                break;
            case 8:
                recordFinal(&tournament);
                break;
            case 9:
                displayStatus(&tournament);
                break;
            case 10:
                printf("Exiting Tournament Module.\n");
                break;
        }
    } while (choice != 10);

    freeTournament(&tournament);
    return 0;
}