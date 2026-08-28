#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define NAME_LEN 40
#define LINE_LEN 160

typedef struct {
    int id;
    char name[NAME_LEN];
    int score;
    int missions;
} Team;

int findTeamIndex(const Team teams[], int size, int id);
int ensureCapacity(Team **teams, int *capacity, int required);
int addTeam(Team **teams, int *size, int *capacity, Team candidate);
int recordMission(Team teams[], int size, int id, int points);
int deleteTeam(Team teams[], int *size, int id);
void sortLeaderboard(Team teams[], int size);
void displayTeams(const Team teams[], int size);
int loadTeams(const char *filename, Team **teams, int *size, int *capacity);
int saveTeams(const char *filename, const Team teams[], int size);
void readText(const char *prompt, char text[], int limit);
int readInt(const char *prompt, int *value);

int main(void)
{
    Team *teams = nullptr;
    int size = 0;
    int capacity = 0;
    int choice;

    loadTeams("teams.txt", &teams, &size, &capacity);

    do {
        std::cout << "\n=== CAMPUS QUEST LEADERBOARD ===\n"
                  << "1. Register a team\n2. Record mission points\n3. Find a team\n"
                  << "4. Remove a team\n5. Show leaderboard\n6. Save and exit\n";

        if (!readInt("Choose: ", &choice)) {
            std::cout << "Invalid menu input.\n";
            continue;
        }

        if (choice == 1) {
            Team candidate = {0, "", 0, 0};
            readInt("Team ID: ", &candidate.id);
            readText("Team name: ", candidate.name, NAME_LEN);
            /* TODO: call addTeam and report success/failure */
        } else if (choice == 2) {
            int id, points;
            readInt("Team ID: ", &id);
            readInt("Mission points (1-100): ", &points);
            /* TODO: call recordMission and report success/failure */
        } else if (choice == 3) {
            int id;
            readInt("Team ID: ", &id);
            /* TODO: search and display the matching complete record */
        } else if (choice == 4) {
            int id;
            readInt("Team ID: ", &id);
            /* TODO: call deleteTeam and report success/failure */
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            displayTeams(teams, size);
        } else if (choice == 6) {
            if (!saveTeams("teams.txt", teams, size))
                std::cout << "Warning: data could not be saved.\n";
        } else {
            std::cout << "Choose a number from 1 to 6.\n";
        }
    } while (choice != 6);

    std::free(teams);
    teams = nullptr;
    return 0;
}

int findTeamIndex(const Team teams[], int size, int id)
{
    (void)teams; (void)size; (void)id;
    /* TODO: search only indexes 0 through size - 1 */
    return -1;
}

int ensureCapacity(Team **teams, int *capacity, int required)
{
    (void)teams; (void)capacity; (void)required;
    /* TODO: grow by doubling; use a temporary pointer with realloc */
    return 0;
}

int addTeam(Team **teams, int *size, int *capacity, Team candidate)
{
    (void)teams; (void)size; (void)capacity; (void)candidate;
    /* TODO: validate, reject duplicate ID, ensure capacity, then commit */
    return 0;
}

int recordMission(Team teams[], int size, int id, int points)
{
    (void)teams; (void)size; (void)id; (void)points;
    /* TODO: validate points, find by ID, then update score and missions */
    return 0;
}

int deleteTeam(Team teams[], int *size, int id)
{
    (void)teams; (void)size; (void)id;
    /* TODO: find by ID, shift complete Team records left, reduce size */
    return 0;
}

void sortLeaderboard(Team teams[], int size)
{
    (void)teams; (void)size;
    /* TODO: descending score; swap complete Team objects */
}

void displayTeams(const Team teams[], int size)
{
    (void)teams; (void)size;
    /* TODO: print a readable table without inspecting unused capacity */
}

int loadTeams(const char *filename, Team **teams, int *size, int *capacity)
{
    (void)filename; (void)teams; (void)size; (void)capacity;
    /* TODO: open; read one line; parse temporary fields; validate; commit */
    return 0;
}

int saveTeams(const char *filename, const Team teams[], int size)
{
    (void)filename; (void)teams; (void)size;
    /* TODO: write id|name|score|missions and report write/close failure */
    return 0;
}

void readText(const char *prompt, char text[], int limit)
{
    std::cout << prompt;
    if (fgets(text, limit, stdin) != NULL)
        text[std::strcspn(text, "\n")] = '\0';
}

int readInt(const char *prompt, int *value)
{
    char line[LINE_LEN], extra;
    std::cout << prompt;
    if (fgets(line, sizeof line, stdin) == NULL) return 0;
    return sscanf(line, "%d %c", value, &extra) == 1;
}
