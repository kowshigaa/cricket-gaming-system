#include <stdio.h>
#include <string.h>

struct Match
{
    int matchId;
    char team1[30];
    char team2[30];
    char winner[30];
    int runs1;
    int runs2;
    int wickets1;
    int wickets2;
};

struct Match matches[100];
int count = 0;

/* Add Match */
void addMatch()
{
    printf("\nEnter Match ID: ");
    scanf("%d", &matches[count].matchId);

    printf("Enter Team 1: ");
    scanf("%s", matches[count].team1);

    printf("Enter Team 2: ");
    scanf("%s", matches[count].team2);

    printf("Enter Team 1 Runs: ");
    scanf("%d", &matches[count].runs1);

    printf("Enter Team 1 Wickets: ");
    scanf("%d", &matches[count].wickets1);

    printf("Enter Team 2 Runs: ");
    scanf("%d", &matches[count].runs2);

    printf("Enter Team 2 Wickets: ");
    scanf("%d", &matches[count].wickets2);

    if (matches[count].runs1 > matches[count].runs2)
    {
        strcpy(matches[count].winner, matches[count].team1);
    }
    else if (matches[count].runs2 > matches[count].runs1)
    {
        strcpy(matches[count].winner, matches[count].team2);
    }
    else
    {
        strcpy(matches[count].winner, "Draw");
    }

    count++;

    printf("\nMatch added successfully!\n");
}

/* Display Match History */
void displayMatches()
{
    int i;

    if (count == 0)
    {
        printf("\nNo match history available.\n");
        return;
    }

    printf("\n========== MATCH HISTORY ==========\n");

    for (i = 0; i < count; i++)
    {
        printf("\nMatch ID : %d", matches[i].matchId);
        printf("\nTeam 1   : %s", matches[i].team1);
        printf("\nTeam 2   : %s", matches[i].team2);

        printf("\nScore    : %d/%d - %d/%d",
               matches[i].runs1,
               matches[i].wickets1,
               matches[i].runs2,
               matches[i].wickets2);

        printf("\nWinner   : %s\n", matches[i].winner);
    }
}

/* Search Match */
void searchMatch()
{
    int id, i, found = 0;

    printf("\nEnter Match ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < count; i++)
    {
        if (matches[i].matchId == id)
        {
            printf("\nMatch Found!");
            printf("\nMatch ID : %d", matches[i].matchId);
            printf("\nTeam 1   : %s", matches[i].team1);
            printf("\nTeam 2   : %s", matches[i].team2);

            printf("\nScore    : %d/%d - %d/%d",
                   matches[i].runs1,
                   matches[i].wickets1,
                   matches[i].runs2,
                   matches[i].wickets2);

            printf("\nWinner   : %s\n", matches[i].winner);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nMatch not found!\n");
    }
}

/* Display Records */
void displayRecords()
{
    int i;
    int highestRuns = -1;
    int highestMatch = -1;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (matches[i].runs1 > highestRuns)
        {
            highestRuns = matches[i].runs1;
            highestMatch = i;
        }

        if (matches[i].runs2 > highestRuns)
        {
            highestRuns = matches[i].runs2;
            highestMatch = i;
        }
    }

    printf("\n========== RECORDS ==========\n");

    printf("\nHighest Team Score: %d", highestRuns);

    printf("\nMatch ID : %d", matches[highestMatch].matchId);
    printf("\n%s vs %s",
           matches[highestMatch].team1,
           matches[highestMatch].team2);

    printf("\n=============================\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n\n===== CRICKET MATCH HISTORY =====");
        printf("\n1. Add Match");
        printf("\n2. Display Match History");
        printf("\n3. Search Match");
        printf("\n4. Display Records");
        printf("\n5. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addMatch();
                break;

            case 2:
                displayMatches();
                break;

            case 3:
                searchMatch();
                break;

            case 4:
                displayRecords();
                break;

            case 5:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
