#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define MAX_QUALIFIED 4

/*
    CRICKET TOURNAMENT / POINTS TABLE MODULE

    Rules used:
    - Win      = 2 points
    - Tie      = 1 point each
    - No Result= 1 point each
    - Loss     = 0 points
    - NRR = aggregate runs scored / aggregate overs faced
           - aggregate runs conceded / aggregate overs bowled
    - Overs are cricket notation: 19.4 = 19 overs + 4 balls.
    - If a team is all out before its full quota, the full quota is
      used for NRR.
    - No Result matches are excluded from NRR.
    - Top 4 qualify.
    - Semi-final 1: 1st vs 4th
    - Semi-final 2: 2nd vs 3rd
    - Semi-final winners play the final.
    - Semi-final/final winner is selected directly; a tied knockout
      match should be decided by the tournament's Super Over procedure.
*/

typedef struct
{
    char name[NAME_SIZE];

    int played;
    int won;
    int lost;
    int tied;
    int noResult;
    int points;

    int runsScored;
    int ballsFacedForNRR;

    int runsConceded;
    int ballsBowledForNRR;

    float nrr;
} Team;

typedef struct
{
    char name[NAME_SIZE];

    int teamCount;
    Team *teams;

    int qualified[MAX_QUALIFIED];
    int qualifiedCount;

    char semi1Team1[NAME_SIZE];
    char semi1Team2[NAME_SIZE];
    char semi2Team1[NAME_SIZE];
    char semi2Team2[NAME_SIZE];

    int semi1Completed;
    int semi2Completed;

    char finalTeam1[NAME_SIZE];
    char finalTeam2[NAME_SIZE];

    int finalCompleted;
    char winner[NAME_SIZE];
} Tournament;

/* ----------------------------------------------------- */
/* Clear invalid input */
/* ----------------------------------------------------- */

void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ----------------------------------------------------- */
/* Read a full line safely */
/* ----------------------------------------------------- */

void readLine(char text[], int size)
{
    if (fgets(text, size, stdin) == NULL)
    {
        text[0] = '\0';
        return;
    }

    text[strcspn(text, "\n")] = '\0';
}

/* ----------------------------------------------------- */
/* Read a positive/non-negative integer */
/* ----------------------------------------------------- */

int readInt(const char *message, int minValue)
{
    int value;

    while (1)
    {
        printf("%s", message);

        if (scanf("%d", &value) == 1 && value >= minValue)
        {
            clearInputBuffer();
            return value;
        }

        printf("Invalid input. Try again.\n");
        clearInputBuffer();
    }
}

/* ----------------------------------------------------- */
/* Find team index */
/* ----------------------------------------------------- */

int findTeam(Tournament *t, const char name[])
{
    int i;

    for (i = 0; i < t->teamCount; i++)
    {
        if (strcmp(t->teams[i].name, name) == 0)
            return i;
    }

    return -1;
}

/* ----------------------------------------------------- */
/* Convert cricket overs notation to legal balls */
/*
   19.4 means 19 overs and 4 balls = 118 balls.
   The part after '.' must be 0 to 5.
   Input 20 means 20.0 overs.
*/
/* ----------------------------------------------------- */

int oversToBalls(float overs)
{
    int wholeOvers;
    int balls;
    float fraction;

    wholeOvers = (int)overs;
    fraction = overs - wholeOvers;

    balls = (int)(fraction * 10.0f + 0.01f);

    if (balls < 0 || balls > 5)
        return -1;

    return wholeOvers * 6 + balls;
}

/* ----------------------------------------------------- */
/* Read overs in cricket notation */
/* ----------------------------------------------------- */

int readOvers(const char *message)
{
    float overs;
    int balls;

    while (1)
    {
        printf("%s", message);

        if (scanf("%f", &overs) == 1 && overs >= 0)
        {
            clearInputBuffer();

            balls = oversToBalls(overs);

            if (balls >= 0)
                return balls;
        }

        printf("Invalid overs. Use cricket notation such as 20, 19.4 or 10.2.\n");
        clearInputBuffer();
    }
}

/* ----------------------------------------------------- */
/* Initialize a team */
/* ----------------------------------------------------- */

void initializeTeam(Team *team)
{
    team->played = 0;
    team->won = 0;
    team->lost = 0;
    team->tied = 0;
    team->noResult = 0;
    team->points = 0;

    team->runsScored = 0;
    team->ballsFacedForNRR = 0;

    team->runsConceded = 0;
    team->ballsBowledForNRR = 0;

    team->nrr = 0.0f;
}

/* ----------------------------------------------------- */
/* Create tournament */
/* ----------------------------------------------------- */

void createTournament(Tournament *t)
{
    int i;

    printf("\n============================================\n");
    printf("        CRICKET TOURNAMENT SETUP\n");
    printf("============================================\n");

    printf("Enter tournament name: ");
    readLine(t->name, NAME_SIZE);

    t->teamCount = readInt("Enter number of teams: ", 2);

    t->teams = (Team *)malloc(t->teamCount * sizeof(Team));

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

            if (findTeam(t, t->teams[i].name) != -1)
            {
                printf("Team name already exists. Enter a different name.\n");
                continue;
            }

            break;
        }

        initializeTeam(&t->teams[i]);
    }

    t->qualifiedCount = 0;

    t->semi1Team1[0] = '\0';
    t->semi1Team2[0] = '\0';
    t->semi2Team1[0] = '\0';
    t->semi2Team2[0] = '\0';

    t->semi1Completed = 0;
    t->semi2Completed = 0;

    t->finalTeam1[0] = '\0';
    t->finalTeam2[0] = '\0';

    t->finalCompleted = 0;
    t->winner[0] = '\0';

    printf("\nTournament created successfully.\n");
}

/* ----------------------------------------------------- */
/* Calculate tournament NRR */
/* ----------------------------------------------------- */

void calculateNRR(Tournament *t)
{
    int i;

    for (i = 0; i < t->teamCount; i++)
    {
        if (t->teams[i].ballsFacedForNRR > 0 &&
            t->teams[i].ballsBowledForNRR > 0)
        {
            float runRateFor;
            float runRateAgainst;

            runRateFor =
                ((float)t->teams[i].runsScored * 6.0f) /
                t->teams[i].ballsFacedForNRR;

            runRateAgainst =
                ((float)t->teams[i].runsConceded * 6.0f) /
                t->teams[i].ballsBowledForNRR;

            t->teams[i].nrr = runRateFor - runRateAgainst;
        }
        else
        {
            t->teams[i].nrr = 0.0f;
        }
    }
}

/* ----------------------------------------------------- */
/* Compare teams for points table */
/*
   Primary: Points
   Secondary: NRR
   Tertiary: Wins

   Exact competition tie-breakers can differ, so this
   module keeps the ranking rules simple and configurable.
*/
/* ----------------------------------------------------- */

int isHigherRank(Team *a, Team *b)
{
    if (a->points != b->points)
        return a->points > b->points;

    if (a->nrr != b->nrr)
        return a->nrr > b->nrr;

    if (a->won != b->won)
        return a->won > b->won;

    return strcmp(a->name, b->name) < 0;
}

/* ----------------------------------------------------- */
/* Create ranking index */
/* ----------------------------------------------------- */

int *createRanking(Tournament *t)
{
    int *rank;
    int i;
    int j;
    int temp;

    rank = (int *)malloc(t->teamCount * sizeof(int));

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
            if (!isHigherRank(&t->teams[rank[j]],
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

/* ----------------------------------------------------- */
/* Record a league/group match */
/* ----------------------------------------------------- */

void recordMatchResult(Tournament *t)
{
    char team1[NAME_SIZE];
    char team2[NAME_SIZE];

    int index1;
    int index2;

    int result;
    int runs1;
    int runs2;
    int balls1;
    int balls2;

    int quotaBalls;
    int allOut1;
    int allOut2;

    printf("\n============================================\n");
    printf("             RECORD LEAGUE MATCH\n");
    printf("============================================\n");

    printf("Enter Team 1: ");
    readLine(team1, NAME_SIZE);

    printf("Enter Team 2: ");
    readLine(team2, NAME_SIZE);

    index1 = findTeam(t, team1);
    index2 = findTeam(t, team2);

    if (index1 == -1 || index2 == -1)
    {
        printf("One or both teams were not found.\n");
        return;
    }

    if (index1 == index2)
    {
        printf("A team cannot play against itself.\n");
        return;
    }

    printf("\n1. %s Won\n", t->teams[index1].name);
    printf("2. %s Won\n", t->teams[index2].name);
    printf("3. Tie\n");
    printf("4. No Result\n");

    result = readInt("Enter result: ", 1);

    if (result > 4)
    {
        printf("Invalid result.\n");
        return;
    }

    /* No Result: do not add runs/balls to NRR. */
    if (result == 4)
    {
        t->teams[index1].played++;
        t->teams[index2].played++;

        t->teams[index1].noResult++;
        t->teams[index2].noResult++;

        t->teams[index1].points++;
        t->teams[index2].points++;

        calculateNRR(t);

        printf("\nNo Result recorded. This match does not affect NRR.\n");
        return;
    }

    runs1 = readInt("Enter runs scored by Team 1: ", 0);
    balls1 = readOvers("Enter overs faced by Team 1: ");

    runs2 = readInt("Enter runs scored by Team 2: ", 0);
    balls2 = readOvers("Enter overs faced by Team 2: ");

    if (balls1 <= 0 || balls2 <= 0)
    {
        printf("Overs must be greater than 0 for a completed innings.\n");
        return;
    }

    /*
       For a proper NRR calculation, ask whether either team
       was all out before its full quota.

       If all out, use the full quota instead of actual balls.
    */
    allOut1 = readInt("Was Team 1 all out before the full quota? (1=Yes, 0=No): ", 0);
    if (allOut1 != 0 && allOut1 != 1)
    {
        printf("Invalid choice.\n");
        return;
    }

    allOut2 = readInt("Was Team 2 all out before the full quota? (1=Yes, 0=No): ", 0);
    if (allOut2 != 0 && allOut2 != 1)
    {
        printf("Invalid choice.\n");
        return;
    }

    /*
       Ask for the match quota only when it is needed.
       Example: T20 = 20 overs, ODI = 50 overs.
    */
    quotaBalls = 0;

    if (allOut1 == 1 || allOut2 == 1)
    {
        quotaBalls = readOvers(
            "Enter full innings quota in overs (e.g. 20 or 50): "
        );

        if (quotaBalls <= 0)
        {
            printf("Invalid full quota.\n");
            return;
        }
    }

    if (allOut1 == 1)
        balls1 = quotaBalls;

    if (allOut2 == 1)
        balls2 = quotaBalls;

    t->teams[index1].played++;
    t->teams[index2].played++;

    t->teams[index1].runsScored += runs1;
    t->teams[index1].ballsFacedForNRR += balls1;

    t->teams[index1].runsConceded += runs2;
    t->teams[index1].ballsBowledForNRR += balls2;

    t->teams[index2].runsScored += runs2;
    t->teams[index2].ballsFacedForNRR += balls2;

    t->teams[index2].runsConceded += runs1;
    t->teams[index2].ballsBowledForNRR += balls1;

    if (result == 1)
    {
        t->teams[index1].won++;
        t->teams[index2].lost++;
        t->teams[index1].points += 2;
    }
    else if (result == 2)
    {
        t->teams[index2].won++;
        t->teams[index1].lost++;
        t->teams[index2].points += 2;
    }
    else
    {
        t->teams[index1].tied++;
        t->teams[index2].tied++;

        t->teams[index1].points++;
        t->teams[index2].points++;
    }

    calculateNRR(t);

    printf("\nMatch recorded successfully.\n");
}

/* ----------------------------------------------------- */
/* Display teams */
/* ----------------------------------------------------- */

void displayTeams(Tournament *t)
{
    int i;

    printf("\n============================================\n");
    printf("              TOURNAMENT TEAMS\n");
    printf("============================================\n");

    for (i = 0; i < t->teamCount; i++)
        printf("%d. %s\n", i + 1, t->teams[i].name);
}

/* ----------------------------------------------------- */
/* Display points table */
/* ----------------------------------------------------- */

void displayPointsTable(Tournament *t)
{
    int *rank;
    int i;
    int index;

    calculateNRR(t);
    rank = createRanking(t);

    if (rank == NULL)
        return;

    printf("\n====================================================================\n");
    printf("                       %s\n", t->name);
    printf("                       POINTS TABLE\n");
    printf("====================================================================\n");

    printf("%-5s %-20s %-4s %-4s %-4s %-4s %-4s %-6s %-8s\n",
           "Rank", "Team", "P", "W", "L", "T", "NR", "Pts", "NRR");

    printf("--------------------------------------------------------------------\n");

    for (i = 0; i < t->teamCount; i++)
    {
        index = rank[i];

        printf("%-5d %-20s %-4d %-4d %-4d %-4d %-4d %-6d %+.2f\n",
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

    printf("====================================================================\n");

    free(rank);
}

/* ----------------------------------------------------- */
/* Determine Top 4 */
/* ----------------------------------------------------- */

void determineQualifiedTeams(Tournament *t)
{
    int *rank;
    int i;
    int number;

    calculateNRR(t);
    rank = createRanking(t);

    if (rank == NULL)
        return;

    if (t->teamCount < 4)
    {
        printf("\nAt least 4 teams are required for semi-finals.\n");
        free(rank);
        return;
    }

    number = MAX_QUALIFIED;
    t->qualifiedCount = number;

    for (i = 0; i < number; i++)
        t->qualified[i] = rank[i];

    printf("\n============================================\n");
    printf("                 TOP 4 TEAMS\n");
    printf("============================================\n");

    for (i = 0; i < number; i++)
    {
        printf("%d. %s\n",
               i + 1,
               t->teams[t->qualified[i]].name);
    }

    free(rank);
}

/* ----------------------------------------------------- */
/* Display qualified teams */
/* ----------------------------------------------------- */

void displayQualifiedTeams(Tournament *t)
{
    int i;

    if (t->qualifiedCount != 4)
    {
        printf("\nTop 4 teams have not been determined yet.\n");
        return;
    }

    printf("\n============================================\n");
    printf("                 QUALIFIED TEAMS\n");
    printf("============================================\n");

    for (i = 0; i < 4; i++)
    {
        printf("%d. %s\n",
               i + 1,
               t->teams[t->qualified[i]].name);
    }
}

/* ----------------------------------------------------- */
/* Create semi-finals */
/* ----------------------------------------------------- */

void createSemiFinals(Tournament *t)
{
    if (t->qualifiedCount != 4)
    {
        printf("\nPlease determine Top 4 teams first.\n");
        return;
    }

    strcpy(t->semi1Team1,
           t->teams[t->qualified[0]].name);

    strcpy(t->semi1Team2,
           t->teams[t->qualified[3]].name);

    strcpy(t->semi2Team1,
           t->teams[t->qualified[1]].name);

    strcpy(t->semi2Team2,
           t->teams[t->qualified[2]].name);

    t->semi1Completed = 0;
    t->semi2Completed = 0;

    t->finalTeam1[0] = '\0';
    t->finalTeam2[0] = '\0';
    t->finalCompleted = 0;
    t->winner[0] = '\0';

    printf("\n============================================\n");
    printf("                 SEMI-FINALS\n");
    printf("============================================\n");

    printf("Semi-Final 1 : %s vs %s\n",
           t->semi1Team1,
           t->semi1Team2);

    printf("Semi-Final 2 : %s vs %s\n",
           t->semi2Team1,
           t->semi2Team2);
}

/* ----------------------------------------------------- */
/* Record a semi-final winner */
/* ----------------------------------------------------- */

void recordSemiFinalResult(Tournament *t)
{
    int semi;
    int choice;

    if (t->qualifiedCount != 4)
    {
        printf("\nPlease determine Top 4 first.\n");
        return;
    }

    if (t->semi1Team1[0] == '\0')
        createSemiFinals(t);

    printf("\n============================================\n");
    printf("             SEMI-FINAL RESULT\n");
    printf("============================================\n");

    printf("1. Semi-Final 1\n");
    printf("2. Semi-Final 2\n");

    semi = readInt("Enter semi-final number: ", 1);

    if (semi == 1)
    {
        if (t->semi1Completed)
        {
            printf("Semi-Final 1 is already completed.\n");
            return;
        }

        printf("\n1. %s Won\n", t->semi1Team1);
        printf("2. %s Won\n", t->semi1Team2);

        choice = readInt("Enter winner: ", 1);

        if (choice == 1)
        {
            strcpy(t->finalTeam1, t->semi1Team1);
        }
        else if (choice == 2)
        {
            strcpy(t->finalTeam1, t->semi1Team2);
        }
        else
        {
            printf("Invalid winner choice.\n");
            return;
        }

        t->semi1Completed = 1;
        printf("\nSemi-Final 1 winner: %s\n", t->finalTeam1);
    }
    else if (semi == 2)
    {
        if (t->semi2Completed)
        {
            printf("Semi-Final 2 is already completed.\n");
            return;
        }

        printf("\n1. %s Won\n", t->semi2Team1);
        printf("2. %s Won\n", t->semi2Team2);

        choice = readInt("Enter winner: ", 1);

        if (choice == 1)
        {
            strcpy(t->finalTeam2, t->semi2Team1);
        }
        else if (choice == 2)
        {
            strcpy(t->finalTeam2, t->semi2Team2);
        }
        else
        {
            printf("Invalid winner choice.\n");
            return;
        }

        t->semi2Completed = 1;
        printf("\nSemi-Final 2 winner: %s\n", t->finalTeam2);
    }
    else
    {
        printf("Invalid semi-final number.\n");
        return;
    }

    if (t->semi1Completed && t->semi2Completed)
    {
        printf("\n============================================\n");
        printf("                 FINAL READY\n");
        printf("============================================\n");
        printf("Final : %s vs %s\n",
               t->finalTeam1,
               t->finalTeam2);
    }
}

/* ----------------------------------------------------- */
/* Record final winner */
/* ----------------------------------------------------- */

void recordFinalResult(Tournament *t)
{
    int choice;

    if (!t->semi1Completed || !t->semi2Completed)
    {
        printf("\nBoth semi-finals must be completed first.\n");
        return;
    }

    if (t->finalCompleted)
    {
        printf("\nFinal result is already recorded.\n");
        return;
    }

    printf("\n============================================\n");
    printf("                   FINAL\n");
    printf("============================================\n");

    printf("1. %s Won\n", t->finalTeam1);
    printf("2. %s Won\n", t->finalTeam2);

    choice = readInt("Enter winner: ", 1);

    if (choice == 1)
        strcpy(t->winner, t->finalTeam1);
    else if (choice == 2)
        strcpy(t->winner, t->finalTeam2);
    else
    {
        printf("Invalid winner choice.\n");
        return;
    }

    t->finalCompleted = 1;

    printf("\n============================================\n");
    printf("             TOURNAMENT WINNER\n");
    printf("============================================\n");
    printf("Winner: %s\n", t->winner);
}

/* ----------------------------------------------------- */
/* Display tournament status */
/* ----------------------------------------------------- */

void displayTournamentStatus(Tournament *t)
{
    printf("\n============================================\n");
    printf("            TOURNAMENT STATUS\n");
    printf("============================================\n");

    if (t->qualifiedCount == 4)
    {
        printf("Top 4: Determined\n");

        printf("Semi-Final 1: %s vs %s - %s\n",
               t->semi1Team1,
               t->semi1Team2,
               t->semi1Completed ? "Completed" : "Pending");

        printf("Semi-Final 2: %s vs %s - %s\n",
               t->semi2Team1,
               t->semi2Team2,
               t->semi2Completed ? "Completed" : "Pending");
    }
    else
    {
        printf("Top 4: Not determined\n");
    }

    if (t->semi1Completed && t->semi2Completed)
    {
        printf("Final: %s vs %s - %s\n",
               t->finalTeam1,
               t->finalTeam2,
               t->finalCompleted ? "Completed" : "Pending");
    }
    else
    {
        printf("Final: Not ready\n");
    }

    if (t->finalCompleted)
        printf("Winner: %s\n", t->winner);
    else
        printf("Winner: Not decided\n");
}

/* ----------------------------------------------------- */
/* Free memory */
/* ----------------------------------------------------- */

void freeTournament(Tournament *t)
{
    if (t->teams != NULL)
    {
        free(t->teams);
        t->teams = NULL;
    }

    t->teamCount = 0;
    t->qualifiedCount = 0;
}

/* ----------------------------------------------------- */
/* Main */
/* ----------------------------------------------------- */

int main(void)
{
    Tournament tournament;
    int choice;

    tournament.teamCount = 0;
    tournament.teams = NULL;
    tournament.qualifiedCount = 0;
    tournament.semi1Completed = 0;
    tournament.semi2Completed = 0;
    tournament.finalCompleted = 0;
    tournament.winner[0] = '\0';

    createTournament(&tournament);

    do
    {
        printf("\n\n============================================\n");
        printf("          CRICKET TOURNAMENT MODULE\n");
        printf("============================================\n");
        printf("1. Display Teams\n");
        printf("2. Record League Match Result\n");
        printf("3. Display Points Table\n");
        printf("4. Determine Top 4 Teams\n");
        printf("5. Display Qualified Teams\n");
        printf("6. Create Semi-Finals\n");
        printf("7. Record Semi-Final Result\n");
        printf("8. Record Final Result\n");
        printf("9. Display Tournament Status\n");
        printf("10. Exit\n");
        printf("============================================\n");

        choice = readInt("Enter choice: ", 1);

        switch (choice)
        {
            case 1:
                displayTeams(&tournament);
                break;

            case 2:
                recordMatchResult(&tournament);
                break;

            case 3:
                displayPointsTable(&tournament);
                break;

            case 4:
                determineQualifiedTeams(&tournament);
                break;

            case 5:
                displayQualifiedTeams(&tournament);
                break;

            case 6:
                createSemiFinals(&tournament);
                break;

            case 7:
                recordSemiFinalResult(&tournament);
                break;

            case 8:
                recordFinalResult(&tournament);
                break;

            case 9:
                displayTournamentStatus(&tournament);
                break;

            case 10:
                printf("\nExiting Tournament Module.\n");
                break;

            default:
                printf("\nInvalid choice. Enter 1 to 10.\n");
        }

    } while (choice != 10);

    freeTournament(&tournament);

    return 0;
}
