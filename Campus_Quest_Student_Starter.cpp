#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define NAME_LEN 40
#define LINE_LEN 160

struct Team {
    int id;
    char name[NAME_LEN];
    int score;
    int missions;
};

int findTeamIndex(Team teams[], int size, int id);
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam);
int recordMission(Team teams[], int size, int id, int points);
int deleteTeam(Team teams[], int &size, int id);
void sortLeaderboard(Team teams[], int size);
void displayTeams(Team teams[], int size);
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity);
int saveTeams(const char* filename, Team teams[], int size);
void readText(const char* prompt, char text[], int limit);
bool readInt(const char* prompt, int &value);

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;
    int choice;

    loadTeams("teams.txt", teams, size, capacity);

    do {
        std::cout << "\n=== CAMPUS QUEST LEADERBOARD ===\n"
                  << "1. Register a team\n2. Record mission points\n3. Find a team\n"
                  << "4. Remove a team\n5. Show leaderboard\n6. Save and exit\n";

        if (!readInt("Choose: ", choice)) {
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            Team t = {0, "", 0, 0};
            readInt("Team ID: ", t.id);
            readText("Team name: ", t.name, NAME_LEN);
            /* TODO: call addTeam and tell the user if it worked */
        } else if (choice == 2) {
            int id, points;
            readInt("Team ID: ", id);
            readInt("Mission points (1-100): ", points);
            /* TODO: call recordMission and tell the user if it worked */
        } else if (choice == 3) {
            int id;
            readInt("Team ID: ", id);
            /* TODO: find the team and print its info */
        } else if (choice == 4) {
            int id;
            readInt("Team ID: ", id);
            /* TODO: call deleteTeam and tell the user if it worked */
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            displayTeams(teams, size);
        } else if (choice == 6) {
            if (!saveTeams("teams.txt", teams, size))
                std::cout << "Warning: data could not be saved.\n";
        } else {
            std::cout << "Pick a number from 1 to 6.\n";
        }
    } while (choice != 6);

    free(teams);
    teams = NULL;
    return 0;
}

// Find a team by ID. Returns the index, or -1 if not found.
int findTeamIndex(Team teams[], int size, int id) {
    /* TODO: loop through teams[0] to teams[size-1] and return the matching index */
    (void)teams; (void)size; (void)id;
    return -1;
}

// Make the array bigger if needed
int ensureCapacity(Team* &teams, int &capacity, int needed) {
    /* TODO: if needed > capacity, double the capacity using realloc */
    (void)teams; (void)capacity; (void)needed;
    return 0;
}

// Add a team. Check for duplicate ID first.
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam) {
    /* TODO: check ID is unique, make sure there's room, then add */
    (void)teams; (void)size; (void)capacity; (void)newTeam;
    return 0;
}

// Add mission points (1-100) to a team
int recordMission(Team teams[], int size, int id, int points) {
    /* TODO: check points are 1-100, find the team, add to score and missions */
    (void)teams; (void)size; (void)id; (void)points;
    return 0;
}

// Remove a team by shifting the rest left
int deleteTeam(Team teams[], int &size, int id) {
    /* TODO: find the team, shift everything after it left, decrease size */
    (void)teams; (void)size; (void)id;
    return 0;
}

// Sort teams by score (highest first)
void sortLeaderboard(Team teams[], int size) {
    /* TODO: bubble sort, highest score first. If scores are equal, more missions wins */
    (void)teams; (void)size;
}

// Print all teams in a table
void displayTeams(Team teams[], int size) {
    /* TODO: print each team's rank, id, name, score, missions */
    (void)teams; (void)size;
}

// Load teams from a file
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity) {
    /* TODO: open file, read each line, parse id|name|score|missions, add team */
    (void)filename; (void)teams; (void)size; (void)capacity;
    return 0;
}

// Save teams to a file
int saveTeams(const char* filename, Team teams[], int size) {
    /* TODO: write each team as id|name|score|missions on its own line */
    (void)filename; (void)teams; (void)size;
    return 0;
}

// Read a line of text from the user
void readText(const char* prompt, char text[], int limit) {
    std::cout << prompt;
    if (fgets(text, limit, stdin) != NULL)
        text[strcspn(text, "\n")] = '\0';
}

// Read a whole number from the user. Returns true if valid.
bool readInt(const char* prompt, int &value) {
    char line[LINE_LEN];
    std::cout << prompt;
    if (fgets(line, sizeof(line), stdin) == NULL) return false;

    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\0') return false;

    int start = 0;
    if (line[0] == '-') start = 1;
    if (line[start] == '\0') return false;

    for (int i = start; line[i] != '\0'; i++) {
        if (line[i] < '0' || line[i] > '9') return false;
    }

    value = atoi(line);
    return true;
}
