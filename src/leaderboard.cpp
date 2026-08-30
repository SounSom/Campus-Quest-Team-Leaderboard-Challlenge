#include "leaderboard.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Look for a team by ID. Returns the index number, or -1 if not found.
int findTeamIndex(Team teams[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (teams[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Add a team to the array. Reallocates memory if full. Returns 1 if added, 0 if failed.
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam) {
    // Check that ID is positive and name is not empty
    if (newTeam.id <= 0 || strlen(newTeam.name) == 0 || newTeam.score < 0 || newTeam.missions < 0) {
        cout << "Error: Invalid team data.\n";
        return 0;
    }

    // Check if ID is already used
    if (findTeamIndex(teams, size, newTeam.id) != -1) {
        cout << "Error: Team ID " << newTeam.id << " already exists.\n";
        return 0;
    }

    // Double capacity if array is full
    if (size >= capacity) {
        int newCap = (capacity == 0) ? 2 : capacity * 2;
        Team* temp = (Team*) realloc(teams, newCap * sizeof(Team));
        if (temp == NULL) {
            cout << "Error: Out of memory.\n";
            return 0;
        }
        teams = temp;
        capacity = newCap;
    }

    // Insert new team at the end
    teams[size] = newTeam;
    size++;
    return 1;
}

// Add points (1-100) to a team's score and increase mission count by 1.
int recordMission(Team teams[], int size, int id, int points) {
    if (points < 1 || points > 100) {
        cout << "Error: Points must be between 1 and 100.\n";
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team ID " << id << " not found.\n";
        return 0;
    }

    teams[index].score += points;
    teams[index].missions += 1;
    return 1;
}

// Delete a team by moving remaining teams left to fill the gap.
int deleteTeam(Team teams[], int &size, int id) {
    if (size == 0) {
        cout << "Error: No teams to delete.\n";
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team ID " << id << " not found.\n";
        return 0;
    }

    // Shift elements left
    for (int i = index; i < size - 1; i++) {
        teams[i] = teams[i + 1];
    }

    size--;
    return 1;
}

// Sort teams descending by score. If scores are equal, team with more missions goes first.
void sortLeaderboard(Team teams[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool swapNeeded = false;

            // Check if next team has a higher score
            if (teams[j].score < teams[j + 1].score) {
                swapNeeded = true;
            }
            // If scores are equal, check who completed more missions
            else if (teams[j].score == teams[j + 1].score) {
                if (teams[j].missions < teams[j + 1].missions) {
                    swapNeeded = true;
                }
            }

            // Swap team structs
            if (swapNeeded) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}

// Print the leaderboard in a formatted table
void showLeaderboard(Team teams[], int size) {
    if (size == 0) {
        cout << "\nLeaderboard is currently empty.\n";
        return;
    }

    cout << "\n===========================================================\n";
    cout << "                CAMPUS QUEST LEADERBOARD                   \n";
    cout << "===========================================================\n";
    cout << left
         << setw(6)  << "Rank"
         << setw(8)  << "ID"
         << setw(25) << "Team Name"
         << setw(10) << "Score"
         << setw(10) << "Missions" << "\n";
    cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        cout << left
             << setw(6)  << (i + 1)
             << setw(8)  << teams[i].id
             << setw(25) << teams[i].name
             << setw(10) << teams[i].score
             << setw(10) << teams[i].missions << "\n";
    }

    cout << "===========================================================\n";
}

// Load teams from a file line by line (format: id|name|score|missions)
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[160];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Strip newline characters
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        // Split line by '|'
        char* token1 = strtok(line, "|");
        char* token2 = strtok(NULL, "|");
        char* token3 = strtok(NULL, "|");
        char* token4 = strtok(NULL, "|");

        if (token1 == NULL || token2 == NULL || token3 == NULL || token4 == NULL) {
            continue;
        }

        Team t;
        t.id = atoi(token1);
        strncpy(t.name, token2, sizeof(t.name) - 1);
        t.name[sizeof(t.name) - 1] = '\0';
        t.score = atoi(token3);
        t.missions = atoi(token4);

        if (addTeam(teams, size, capacity, t)) {
            count++;
        }
    }

    fclose(file);
    return count;
}

// Save all teams to a text file
int saveTeams(const char* filename, Team teams[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        cout << "Error: Cannot open " << filename << " for writing.\n";
        return 0;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d|%s|%d|%d\n", teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }

    fclose(file);
    return 1;
}

// Free allocated array memory
void freeMemory(Team* &teams, int &size, int &capacity) {
    free(teams);
    teams = NULL;
    size = 0;
    capacity = 0;
}
