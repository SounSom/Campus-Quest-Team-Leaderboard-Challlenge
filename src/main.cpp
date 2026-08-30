#include "leaderboard.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

// Variable holding the file name
const char* DATA_FILE = "teams.txt";

// Helper function to read a text line safely
void readText(const char* prompt, char text[], int limit) {
    // Inform the user what to input
    cout << prompt;
    // IF the user input successfully THEN trim \n away
    if (fgets(text, limit, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }
}

// Helper function to read an integer and reject letters, floats, or empty input
bool readInt(const char* prompt, int &result) {
    // Temporary input buffer
    char line[100];

    // Inform the user what to input
    cout << prompt;
    // IF the input failed
    if (fgets(line, sizeof(line), stdin) == NULL) return false;

    // Strip trailing line break
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\0') return false;

    // Skip minus sign if present
    int start = 0;
    if (line[0] == '-') start = 1;
    if (line[start] == '\0') return false;

    // Check each character to ensure it's a digit
    for (int i = start; line[i] != '\0'; i++) {
        if (line[i] < '0' || line[i] > '9') return false;
    }

    // Convert string to integer
    result = atoi(line);
    return true;
}

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;
    int choice;

    // Load existing team records on program startup
    int loaded = loadTeams(DATA_FILE, teams, size, capacity);
    if (loaded > 0) {
        cout << "Loaded " << loaded << " team(s) from " << DATA_FILE << ".\n";
    }

    do {
        cout << "\n=========================================\n"
             << "      CAMPUS QUEST: LEADERBOARD          \n"
             << "=========================================\n"
             << " 1. Register New Team                    \n"
             << " 2. Record Mission Points                \n"
             << " 3. Find Team by ID                      \n"
             << " 4. Remove Team                          \n"
             << " 5. Show Ranked Leaderboard              \n"
             << " 6. Save Leaderboard to File             \n"
             << " 7. Exit Program                         \n"
             << "-----------------------------------------\n";

        if (!readInt("Enter your choice (1-7): ", choice)) {
            cout << "Error: Please enter a number from 1 to 7.\n";
            continue;
        }

        if (choice == 1) {
            Team newTeam = {0, "", 0, 0};
            if (!readInt("Enter Team ID: ", newTeam.id)) {
                cout << "Error: Invalid ID. ID must be a whole number.\n";
                continue;
            }
            readText("Enter Team Name: ", newTeam.name, sizeof(newTeam.name));
            if (strlen(newTeam.name) == 0) {
                cout << "Error: Team name cannot be empty.\n";
                continue;
            }
            addTeam(teams, size, capacity, newTeam);

        } else if (choice == 2) {
            int id, points;
            if (!readInt("Enter Team ID: ", id)) {
                cout << "Error: Invalid ID.\n";
                continue;
            }
            if (!readInt("Enter Mission Points (1-100): ", points)) {
                cout << "Error: Points must be a number.\n";
                continue;
            }
            recordMission(teams, size, id, points);

        } else if (choice == 3) {
            int id;
            if (!readInt("Enter Team ID to search: ", id)) {
                cout << "Error: Invalid ID.\n";
                continue;
            }
            int idx = findTeamIndex(teams, size, id);
            if (idx != -1) {
                cout << "\n--- Team Details ---\n"
                     << "ID:       " << teams[idx].id << "\n"
                     << "Name:     " << teams[idx].name << "\n"
                     << "Score:    " << teams[idx].score << "\n"
                     << "Missions: " << teams[idx].missions << "\n";
            } else {
                cout << "Error: Team with ID " << id << " not found.\n";
            }

        } else if (choice == 4) {
            int id;
            if (!readInt("Enter Team ID to remove: ", id)) {
                cout << "Error: Invalid ID.\n";
                continue;
            }
            deleteTeam(teams, size, id);

        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            showLeaderboard(teams, size);

        } else if (choice == 6) {
            if (saveTeams(DATA_FILE, teams, size)) {
                cout << "Saved " << size << " team(s) to " << DATA_FILE << ".\n";
            } else {
                cout << "Error: Failed to save data.\n";
            }

        } else if (choice == 7) {
            if (saveTeams(DATA_FILE, teams, size)) {
                cout << "Saved " << size << " team(s) to " << DATA_FILE << ".\n";
            }
            cout << "Exiting Campus Quest Leaderboard. Goodbye!\n";

        } else {
            cout << "Error: Please pick a choice between 1 and 7.\n";
        }

    } while (choice != 7);

    // Clean up heap memory before exiting
    freeMemory(teams, size, capacity);
    return 0;
}
