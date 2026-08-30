#include "leaderboard.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Look for a team by ID. Returns the index number, or -1 if not found.
int findTeamIndex(Team teams[], int size, int id) {
    // Skim through records to look for a match
    for (int i = 0; i < size; i++) {
        if (teams[i].id == id) {
            return i;
        }
    }
    // No match is found
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
        cout << "Error: Team ID " << newTeam.id << " is already taken.\n";
        return 0;
    }

    // If array is full, double its size
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 2 : capacity * 2;
        Team* temp = (Team*) realloc(teams, newCapacity * sizeof(Team));
        if (temp == NULL) {
            cout << "Error: Memory allocation failed.\n";
            return 0;
        }
        teams = temp;
        capacity = newCapacity;
    }

    // Insert new team record into array
    teams[size] = newTeam;
    size++;
    return 1;
}

// Add points (1-100) to a team by ID. Returns 1 on success, 0 on failure.
int recordMission(Team teams[], int size, int id, int points) {
    // Validate score point bound
    if (points < 1 || points > 100) {
        cout << "Error: Mission points must be between 1 and 100.\n";
        return 0;
    }

    // Retrieve team index by ID
    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team with ID " << id << " not found.\n";
        return 0;
    }

    // Update team score and mission count
    teams[index].score += points;
    teams[index].missions += 1;
    cout << "Recorded " << points << " points for team \"" << teams[index].name << "\".\n";
    return 1;
}

// Delete team by ID by shifting array elements left. Returns 1 on success, 0 on failure.
int deleteTeam(Team teams[], int &size, int id) {
    // Retrieve team index by ID
    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team with ID " << id << " not found.\n";
        return 0;
    }

    // Shift elements left to cover deleted index
    for (int i = index; i < size - 1; i++) {
        teams[i] = teams[i + 1];
    }
    size--;
    cout << "Team with ID " << id << " removed successfully.\n";
    return 1;
}

// Sort teams descending by score (tie-breaker: mission count)
void sortLeaderboard(Team teams[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            // Swap if next element is strictly higher score or equal score with more missions
            if (teams[j].score < teams[j + 1].score ||
               (teams[j].score == teams[j + 1].score && teams[j].missions < teams[j + 1].missions)) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}

// Show leaderboard in formatted tabular view
void showLeaderboard(Team teams[], int size) {
    if (size == 0) {
        cout << "\nLeaderboard is empty. No teams registered yet.\n";
        return;
    }

    cout << "\n===========================================================\n"
         << "                CAMPUS QUEST LEADERBOARD                   \n"
         << "===========================================================\n";
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

// Load records from filename into team array
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity) {
    FILE* file = fopen(filename, "r");
    // Validation of file opening failure
    if (file == NULL) return 0;

    char line[160];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Strip trailing line breaks (\r\n)
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') continue;

        char* idStr = strtok(line, "|");
        char* nameStr = strtok(NULL, "|");
        char* scoreStr = strtok(NULL, "|");
        char* missStr = strtok(NULL, "|");

        if (idStr == NULL || nameStr == NULL || scoreStr == NULL || missStr == NULL)
            continue;

        Team t;
        t.id = atoi(idStr);
        strncpy(t.name, nameStr, sizeof(t.name) - 1);
        t.name[sizeof(t.name) - 1] = '\0';
        t.score = atoi(scoreStr);
        t.missions = atoi(missStr);

        addTeam(teams, size, capacity, t);
        count++;
    }

    fclose(file);
    return count;
}

// Save records from team array into filename
int saveTeams(const char* filename, Team teams[], int size) {
    FILE* file = fopen(filename, "w");
    // Validation of file opening failure
    if (file == NULL) return 0;

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d|%s|%d|%d\n", teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }

    fclose(file);
    return 1;
}

// Deallocate teams heap memory
void freeMemory(Team* &teams, int &size, int &capacity) {
    if (teams != NULL) {
        free(teams);
        teams = NULL;
    }
    size = 0;
    capacity = 0;
}
