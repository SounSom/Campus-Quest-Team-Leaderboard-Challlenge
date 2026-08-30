#include "leaderboard.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

const char* DATA_FILE = "teams.txt";

// Helper function to read a text line safely
void readText(const char* prompt, char text[], int limit) {
    cout << prompt;
    if (fgets(text, limit, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

// Helper function to read an integer and reject letters, floats, or empty input
bool readInt(const char* prompt, int &result) {
    char line[100];
    cout << prompt;
    if (fgets(line, sizeof(line), stdin) == NULL) return false;

    // Strip newline
    line[strcspn(line, "\n")] = '\0';

    // Reject empty input
    if (line[0] == '\0') return false;

    // Check every character is a digit
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

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;
    int choice = 0;

    // Load saved data on startup
    int loaded = loadTeams(DATA_FILE, teams, size, capacity);
    if (loaded > 0) {
        cout << "Loaded " << loaded << " team(s) from " << DATA_FILE << ".\n";
    }

    while (choice != 7) {
        cout << "\n=========================================\n";
        cout << "      CAMPUS QUEST: LEADERBOARD          \n";
        cout << "=========================================\n";
        cout << " 1. Register New Team                    \n";
        cout << " 2. Record Mission Points                \n";
        cout << " 3. Find Team by ID                      \n";
        cout << " 4. Remove Team                          \n";
        cout << " 5. Show Ranked Leaderboard              \n";
        cout << " 6. Save Leaderboard to File             \n";
        cout << " 7. Exit Program                         \n";
        cout << "-----------------------------------------\n";

        if (!readInt("Enter your choice (1-7): ", choice)) {
            cout << "Error: Please enter a number from 1 to 7.\n";
            continue;
        }

        // Option 1: Register New Team
        if (choice == 1) {
            Team t;
            t.score = 0;
            t.missions = 0;

            if (!readInt("Enter Team ID (positive number): ", t.id) || t.id <= 0) {
                cout << "Error: ID must be a positive whole number.\n";
                continue;
            }

            readText("Enter Team Name: ", t.name, sizeof(t.name));
            if (strlen(t.name) == 0) {
                cout << "Error: Team name cannot be empty.\n";
                continue;
            }

            if (!readInt("Enter Initial Score: ", t.score) || t.score < 0) {
                cout << "Error: Score must be 0 or more.\n";
                continue;
            }

            if (!readInt("Enter Initial Missions: ", t.missions) || t.missions < 0) {
                cout << "Error: Missions must be 0 or more.\n";
                continue;
            }

            if (addTeam(teams, size, capacity, t)) {
                cout << "Team \"" << t.name << "\" added successfully!\n";
            }

        // Option 2: Record Mission Points
        } else if (choice == 2) {
            int id, points;
            if (!readInt("Enter Team ID: ", id)) {
                cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (!readInt("Enter Mission Points (1-100): ", points)) {
                cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (recordMission(teams, size, id, points)) {
                cout << "Added " << points << " points to Team " << id << "!\n";
            }

        // Option 3: Find Team by ID
        } else if (choice == 3) {
            int id;
            if (!readInt("Enter Team ID to find: ", id)) {
                cout << "Error: Please enter a valid number.\n";
                continue;
            }

            int index = findTeamIndex(teams, size, id);
            if (index == -1) {
                cout << "Team ID " << id << " was not found.\n";
            } else {
                cout << "\n--- Team Found ---\n";
                cout << "ID:       " << teams[index].id << "\n";
                cout << "Name:     " << teams[index].name << "\n";
                cout << "Score:    " << teams[index].score << "\n";
                cout << "Missions: " << teams[index].missions << "\n";
            }

        // Option 4: Remove Team
        } else if (choice == 4) {
            int id;
            if (!readInt("Enter Team ID to remove: ", id)) {
                cout << "Error: Please enter a valid number.\n";
                continue;
            }

            if (deleteTeam(teams, size, id)) {
                cout << "Team " << id << " removed successfully.\n";
            }

        // Option 5: Show Ranked Leaderboard
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            showLeaderboard(teams, size);

        // Option 6: Save Leaderboard to File
        } else if (choice == 6) {
            if (saveTeams(DATA_FILE, teams, size)) {
                cout << "Saved " << size << " team(s) to " << DATA_FILE << ".\n";
            }

        // Option 7: Exit Program
        } else if (choice == 7) {
            saveTeams(DATA_FILE, teams, size);
            cout << "Data saved. Goodbye!\n";

        } else {
            cout << "Error: Please choose a number from 1 to 7.\n";
        }
    }

    freeMemory(teams, size, capacity);
    return 0;
}
