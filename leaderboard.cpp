#include "leaderboard.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// 1. Search Team by ID
int findTeamIndex(const Team* teams, int size, int id) {
    if (teams == NULL || size <= 0) {
        return -1;
    }
    for (int i = 0; i < size; ++i) {
        if (teams[i].id == id) {
            return i;
        }
    }
    return -1;
}

// 2. Add Team with Safe Dynamic Array Doubling
int addTeam(Team** teams, int* size, int* capacity, Team newTeam) {
    if (teams == NULL || size == NULL || capacity == NULL) {
        return 0;
    }

    // Validation: Positive ID, non-empty name, non-negative score/missions
    if (newTeam.id <= 0 || strlen(newTeam.name) == 0 || newTeam.score < 0 || newTeam.missions < 0) {
        std::cout << "[Error] Invalid team data provided.\n";
        return 0;
    }

    // Validation: Unique ID
    if (findTeamIndex(*teams, *size, newTeam.id) != -1) {
        std::cout << "[Error] Team ID " << newTeam.id << " already exists.\n";
        return 0;
    }

    // Dynamic capacity expansion (doubling strategy)
    if (*size >= *capacity) {
        int newCap = (*capacity == 0) ? 2 : (*capacity * 2);
        Team* temp = (Team*)realloc(*teams, newCap * sizeof(Team));
        if (temp == NULL) {
            std::cout << "[Error] Memory allocation failed. Existing data preserved.\n";
            return 0;
        }
        *teams = temp;
        *capacity = newCap;
    }

    // Copy complete record and increment size
    (*teams)[*size] = newTeam;
    (*size)++;
    return 1;
}

// 3. Record Mission Points (1 - 100 points)
int recordMission(Team* teams, int size, int id, int points) {
    if (points < 1 || points > 100) {
        std::cout << "[Error] Mission points must be between 1 and 100.\n";
        return 0;
    }
    int idx = findTeamIndex(teams, size, id);
    if (idx == -1) {
        std::cout << "[Error] Team ID " << id << " not found.\n";
        return 0;
    }
    teams[idx].score += points;
    teams[idx].missions += 1;
    return 1;
}

// 4. Delete Team and Shift Remaining Records Left
int deleteTeam(Team* teams, int* size, int id) {
    if (teams == NULL || size == NULL || *size <= 0) {
        std::cout << "[Error] Leaderboard is empty.\n";
        return 0;
    }
    int idx = findTeamIndex(teams, *size, id);
    if (idx == -1) {
        std::cout << "[Error] Team ID " << id << " not found.\n";
        return 0;
    }
    // Shift complete records left
    for (int i = idx; i < *size - 1; ++i) {
        teams[i] = teams[i + 1];
    }
    (*size)--;
    return 1;
}

// 5. Sort Leaderboard (Descending by Score, Tie-Break by Missions)
void sortLeaderboard(Team* teams, int size) {
    if (teams == NULL || size <= 1) {
        return;
    }
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            bool shouldSwap = false;
           
            if (teams[j].score < teams[j + 1].score) {
                shouldSwap = true;
            } else if (teams[j].score == teams[j + 1].score) {
                if (teams[j].missions < teams[j + 1].missions) {
                    shouldSwap = true;
                }
            }
            if (shouldSwap) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}

// 6. Display Leaderboard Table
void showLeaderboard(const Team* teams, int size) {
    if (teams == NULL || size <= 0) {
        std::cout << "\n[Info] Leaderboard is currently empty.\n";
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

    for (int i = 0; i < size; ++i) {
        std::cout << std::left 
                  << std::setw(6)  << (i + 1)
                  << std::setw(8)  << teams[i].id
                  << std::setw(28) << teams[i].name
                  << std::setw(10) << teams[i].score
                  << std::setw(10) << teams[i].missions << "\n";
    }
    std::cout << "==============================================================\n";
}

// 7. Load Teams from File (Handles both Windows \r\n and Unix \n)
int loadTeams(const char* filename, Team** teams, int* size, int* capacity) {
    if (filename == NULL || teams == NULL || size == NULL || capacity == NULL) {
        return 0;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // File doesn't exist yet, return 0 without error
        return 0;
    }

    char line[256];
    int loadedCount = 0;

    while (fgets(line, sizeof(line), file)) {
        // Strip trailing \r and \n (cross-platform safe)
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\r' || line[len - 1] == '\n')) {
            line[len - 1] = '\0';
            len--;
        }
        if (len == 0) continue; // Skip empty lines

        // Parse: id|name|score|missions
        char* token1 = strtok(line, "|");
        char* token2 = strtok(NULL, "|");
        char* token3 = strtok(NULL, "|");
        char* token4 = strtok(NULL, "|");

        if (token1 == NULL || token2 == NULL || token3 == NULL || token4 == NULL) {
            // Malformed line: skip safely
            continue;
        }

        Team candidate;
        candidate.id = atoi(token1);
        strncpy(candidate.name, token2, sizeof(candidate.name) - 1);
        candidate.name[sizeof(candidate.name) - 1] = '\0';
        candidate.score = atoi(token3);
        candidate.missions = atoi(token4);

        // Add team using safe validation and expansion
        if (addTeam(teams, size, capacity, candidate)) {
            loadedCount++;
        }
    }

    fclose(file);
    return loadedCount;
}

// 8. Save Teams to File (pipe-separated format)
int saveTeams(const char* filename, const Team* teams, int size) {
    if (filename == NULL) {
        return 0;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        std::cout << "[Error] Unable to open " << filename << " for writing.\n";
        return 0;
    }
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d|%s|%d|%d\n", teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }
    fclose(file);
    return 1;
}

// 9. Memory Cleanup
void freeLeaderboard(Team** teams, int* size, int* capacity) {
    if (teams != NULL && *teams != NULL) {
        free(*teams);
        *teams = NULL;
    }
    if (size != NULL) *size = 0;
    if (capacity != NULL) *capacity = 0;
}
