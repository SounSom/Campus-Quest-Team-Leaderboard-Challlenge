#include "leaderboard.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

const char* DATA_FILE = "teams.txt";

// Read an integer from the user. Returns true if valid, false if not.
// This rejects floats, letters, and empty input.
bool readInt(const char* prompt, int &result) {
    char line[100];
    std::cout << prompt;
    if (!fgets(line, sizeof(line), stdin)) return false;

    // Remove the newline
    line[strcspn(line, "\n")] = '\0';

    // Check that the line is not empty
    if (line[0] == '\0') return false;

    // Check every character is a digit (or a leading minus sign)
    int start = 0;
    if (line[0] == '-') start = 1;
    if (line[start] == '\0') return false;

    for (int i = start; line[i] != '\0'; i++) {
        if (line[i] < '0' || line[i] > '9') {
            return false;
        }
    }

    result = atoi(line);
    return true;
}

// Read a line of text from the user
void readText(const char* prompt, char text[], int maxLen) {
    std::cout << prompt;
    if (fgets(text, maxLen, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;

    // Load saved teams on startup
    int loaded = loadTeams(DATA_FILE, teams, size, capacity);
    if (loaded > 0) {
        std::cout << "Loaded " << loaded << " team(s) from " << DATA_FILE << ".\n";
    }

    int choice = 0;
    while (choice != 7) {
        std::cout << "\n=========================================\n";
        std::cout << "      CAMPUS QUEST: LEADERBOARD          \n";
        std::cout << "=========================================\n";
        std::cout << " 1. Register New Team\n";
        std::cout << " 2. Record Mission Points\n";
        std::cout << " 3. Find Team by ID\n";
        std::cout << " 4. Remove Team\n";
        std::cout << " 5. Show Ranked Leaderboard\n";
        std::cout << " 6. Save Leaderboard to File\n";
        std::cout << " 7. Exit Program\n";
        std::cout << "-----------------------------------------\n";

        if (!readInt("Enter your choice (1-7): ", choice)) {
            std::cout << "Error: Please enter a number from 1 to 7.\n";
            continue;
        }

        if (choice == 1) {
            Team t;

            if (!readInt("Enter Team ID (positive number): ", t.id) || t.id <= 0) {
                std::cout << "Error: ID must be a positive whole number.\n";
                continue;
            }

            readText("Enter Team Name: ", t.name, sizeof(t.name));
            if (strlen(t.name) == 0) {
                std::cout << "Error: Team name cannot be empty.\n";
                continue;
            }

            if (!readInt("Enter Initial Score (0 or more): ", t.score) || t.score < 0) {
                std::cout << "Error: Score must be 0 or more.\n";
                continue;
            }

            if (!readInt("Enter Completed Missions (0 or more): ", t.missions) || t.missions < 0) {
                std::cout << "Error: Missions must be 0 or more.\n";
                continue;
            }

            if (addTeam(teams, size, capacity, t)) {
                std::cout << "Team '" << t.name << "' registered!\n";
            }

        } else if (choice == 2) {
            int id, points;

            if (!readInt("Enter Team ID: ", id)) {
                std::cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (!readInt("Enter Mission Points (1 to 100): ", points)) {
                std::cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (recordMission(teams, size, id, points)) {
                std::cout << "Recorded " << points << " points for team ID " << id << ".\n";
            }

        } else if (choice == 3) {
            int id;

            if (!readInt("Enter Team ID to search: ", id)) {
                std::cout << "Error: Please enter a valid number.\n";
                continue;
            }

            int index = findTeamIndex(teams, size, id);
            if (index != -1) {
                std::cout << "\nTeam Found:\n";
                std::cout << "  ID:       " << teams[index].id << "\n";
                std::cout << "  Name:     " << teams[index].name << "\n";
                std::cout << "  Score:    " << teams[index].score << "\n";
                std::cout << "  Missions: " << teams[index].missions << "\n";
            } else {
                std::cout << "Team with ID " << id << " was not found.\n";
            }

        } else if (choice == 4) {
            int id;

            if (!readInt("Enter Team ID to remove: ", id)) {
                std::cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (deleteTeam(teams, size, id)) {
                std::cout << "Team ID " << id << " removed.\n";
            }

        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            showLeaderboard(teams, size);

        } else if (choice == 6) {
            if (saveTeams(DATA_FILE, teams, size)) {
                std::cout << "Saved " << size << " team(s) to " << DATA_FILE << ".\n";
            }

        } else if (choice == 7) {
            saveTeams(DATA_FILE, teams, size);
            std::cout << "Data saved. Goodbye!\n";

        } else {
            std::cout << "Error: Please choose a number from 1 to 7.\n";
        }
    }

    freeMemory(teams, size, capacity);
    return 0;
}
