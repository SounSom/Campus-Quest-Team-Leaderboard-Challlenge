#include "leaderboard.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>

// Find a team by ID. Returns the index, or -1 if not found.
int findTeamIndex(Team teams[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (teams[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Add a new team to the array. Returns 1 if added, 0 if not.
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam) {
    // Check the data is valid
    if (newTeam.id <= 0 || strlen(newTeam.name) == 0 || newTeam.score < 0 || newTeam.missions < 0) {
        std::cout << "Error: Invalid team data.\n";
        return 0;
    }

    // Make sure this ID doesn't already exist
    if (findTeamIndex(teams, size, newTeam.id) != -1) {
        std::cout << "Error: Team ID " << newTeam.id << " already exists.\n";
        return 0;
    }

    // If the array is full, make it bigger
    if (size >= capacity) {
        int newCapacity = (capacity == 0) ? 2 : capacity * 2;
        Team* bigger = (Team*)realloc(teams, newCapacity * sizeof(Team));
        if (bigger == NULL) {
            std::cout << "Error: Out of memory.\n";
            return 0;
        }
        teams = bigger;
        capacity = newCapacity;
    }

    // Put the new team at the end
    teams[size] = newTeam;
    size++;
    return 1;
}

// Add mission points to a team. Points must be 1-100.
int recordMission(Team teams[], int size, int id, int points) {
    if (points < 1 || points > 100) {
        std::cout << "Error: Points must be between 1 and 100.\n";
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        std::cout << "Error: Team ID " << id << " not found.\n";
        return 0;
    }

    teams[index].score += points;
    teams[index].missions += 1;
    return 1;
}

// Delete a team by ID, shift the rest left. Returns 1 if deleted, 0 if not.
int deleteTeam(Team teams[], int &size, int id) {
    if (size <= 0) {
        std::cout << "Error: No teams to delete.\n";
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        std::cout << "Error: Team ID " << id << " not found.\n";
        return 0;
    }

    // Shift everything after this team one spot to the left
    for (int i = index; i < size - 1; i++) {
        teams[i] = teams[i + 1];
    }
    size--;
    return 1;
}

// Sort teams by score (highest first). If scores are equal, more missions = higher rank.
void sortLeaderboard(Team teams[], int size) {
    if (size <= 1) return;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool swap = false;

            if (teams[j].score < teams[j + 1].score) {
                swap = true;
            } else if (teams[j].score == teams[j + 1].score) {
                if (teams[j].missions < teams[j + 1].missions) {
                    swap = true;
                }
            }

            if (swap) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}

// Print the leaderboard as a nice table
void showLeaderboard(Team teams[], int size) {
    if (size <= 0) {
        std::cout << "\nThe leaderboard is empty.\n";
        return;
    }

    std::cout << "\n==============================================================\n";
    std::cout << "                     CAMPUS QUEST LEADERBOARD                 \n";
    std::cout << "==============================================================\n";

    std::cout << std::left
              << std::setw(6)  << "Rank"
              << std::setw(8)  << "ID"
              << std::setw(28) << "Team Name"
              << std::setw(10) << "Score"
              << std::setw(10) << "Missions" << "\n";
    std::cout << "--------------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        std::cout << std::left
                  << std::setw(6)  << (i + 1)
                  << std::setw(8)  << teams[i].id
                  << std::setw(28) << teams[i].name
                  << std::setw(10) << teams[i].score
                  << std::setw(10) << teams[i].missions << "\n";
    }
    std::cout << "==============================================================\n";
}

// Load teams from a text file. Returns how many were loaded.
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove newline characters (works on Windows and Linux)
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n')) {
            line[len - 1] = '\0';
            len--;
        }
        if (len == 0) continue;

        // Split line by '|' -> id|name|score|missions
        char* part1 = strtok(line, "|");
        char* part2 = strtok(NULL, "|");
        char* part3 = strtok(NULL, "|");
        char* part4 = strtok(NULL, "|");

        // Skip lines that don't have all 4 parts
        if (part1 == NULL || part2 == NULL || part3 == NULL || part4 == NULL) {
            continue;
        }

        Team t;
        t.id = atoi(part1);
        strncpy(t.name, part2, sizeof(t.name) - 1);
        t.name[sizeof(t.name) - 1] = '\0';
        t.score = atoi(part3);
        t.missions = atoi(part4);

        if (addTeam(teams, size, capacity, t)) {
            count++;
        }
    }

    fclose(file);
    return count;
}

// Save all teams to a text file. Returns 1 on success, 0 on failure.
int saveTeams(const char* filename, Team teams[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        std::cout << "Error: Cannot open " << filename << " for writing.\n";
        return 0;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d|%s|%d|%d\n", teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }

    fclose(file);
    return 1;
}

// Free all memory and reset counters
void freeMemory(Team* &teams, int &size, int &capacity) {
    free(teams);
    teams = NULL;
    size = 0;
    capacity = 0;
}
