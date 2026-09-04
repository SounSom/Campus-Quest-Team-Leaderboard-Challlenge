#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

#define NAME_LEN 40
#define LINE_LEN 160

struct Team {
    int id;
    char name[NAME_LEN];
    int score;
    int missions;
};

int findTeamIndex(Team teams[], int size, int id);
int ensureCapacity(Team* &teams, int &capacity, int needed);
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
        cout << "\n=== CAMPUS QUEST LEADERBOARD ===\n"
             << "1. Register a team\n"
             << "2. Record mission points\n"
             << "3. Find a team\n"
             << "4. Remove a team\n"
             << "5. Show leaderboard\n"
             << "6. Save and exit\n";

        if (!readInt("Choose: ", choice)) {
            cout << "Invalid choice. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            Team t = {0, "", 0, 0};
            if (!readInt("Enter Team ID: ", t.id)) {
                cout << "Invalid Team ID.\n";
                continue;
            }
            readText("Enter Team Name: ", t.name, NAME_LEN);
            if (!readInt("Enter Initial Score: ", t.score)) {
                cout << "Invalid Score.\n";
                continue;
            }
            if (!readInt("Enter Missions Completed: ", t.missions)) {
                cout << "Invalid Mission count.\n";
                continue;
            }

            if (addTeam(teams, size, capacity, t)) {
                cout << "Team registered successfully!\n";
            }
        } else if (choice == 2) {
            int id, points;
            if (!readInt("Enter Team ID: ", id)) {
                cout << "Invalid Team ID.\n";
                continue;
            }
            if (!readInt("Enter Mission Points (1-100): ", points)) {
                cout << "Invalid Points.\n";
                continue;
            }
            recordMission(teams, size, id, points);
        } else if (choice == 3) {
            int id;
            if (!readInt("Enter Team ID to search: ", id)) {
                cout << "Invalid Team ID.\n";
                continue;
            }
            int index = findTeamIndex(teams, size, id);
            if (index != -1) {
                cout << "\n--- Team Found ---\n";
                cout << "ID: " << teams[index].id << "\n";
                cout << "Name: " << teams[index].name << "\n";
                cout << "Score: " << teams[index].score << "\n";
                cout << "Missions: " << teams[index].missions << "\n";
            } else {
                cout << "Team not found.\n";
            }
        } else if (choice == 4) {
            int id;
            if (!readInt("Enter Team ID to remove: ", id)) {
                cout << "Invalid Team ID.\n";
                continue;
            }
            deleteTeam(teams, size, id);
        } else if (choice == 5) {
            sortLeaderboard(teams, size);
            displayTeams(teams, size);
        } else if (choice == 6) {
            if (saveTeams("teams.txt", teams, size)) {
                cout << "Data saved successfully. Goodbye!\n";
            } else {
                cout << "Warning: Data could not be saved.\n";
            }
        } else {
            cout << "Invalid choice. Pick a number from 1 to 6.\n";
        }
    } while (choice != 6);

    free(teams);
    teams = NULL;
    return 0;
}

// Find a team by ID. Returns the index, or -1 if not found.
int findTeamIndex(Team teams[], int size, int id) {
    for (int i = 0; i < size; i++) {
        if (teams[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Make the array bigger if needed
int ensureCapacity(Team* &teams, int &capacity, int needed) {
    if (needed <= capacity) return 1;

    int newCapacity = (capacity == 0) ? 2 : capacity * 2;
    while (newCapacity < needed) {
        newCapacity *= 2;
    }

    Team* temp = (Team*)realloc(teams, newCapacity * sizeof(Team));
    if (temp == NULL) {
        cout << "Error: Out of memory!\n";
        return 0;
    }

    teams = temp;
    capacity = newCapacity;
    return 1;
}

// Add a team. Check for duplicate ID first.
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam) {
    if (findTeamIndex(teams, size, newTeam.id) != -1) {
        cout << "Error: Team ID " << newTeam.id << " already exists.\n";
        return 0;
    }

    if (!ensureCapacity(teams, capacity, size + 1)) {
        return 0;
    }

    teams[size] = newTeam;
    size++;
    return 1;
}

// Add mission points (1-100) to a team
int recordMission(Team teams[], int size, int id, int points) {
    if (points < 1 || points > 100) {
        cout << "Error: Mission points must be between 1 and 100.\n";
        return 0;
    }

    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team with ID " << id << " not found.\n";
        return 0;
    }

    teams[index].score += points;
    teams[index].missions += 1;
    cout << "Recorded " << points << " points for team \"" << teams[index].name << "\".\n";
    return 1;
}

// Remove a team by shifting the rest left
int deleteTeam(Team teams[], int &size, int id) {
    int index = findTeamIndex(teams, size, id);
    if (index == -1) {
        cout << "Error: Team with ID " << id << " not found.\n";
        return 0;
    }

    for (int i = index; i < size - 1; i++) {
        teams[i] = teams[i + 1];
    }
    size--;
    cout << "Team with ID " << id << " removed successfully.\n";
    return 1;
}

// Sort teams by score (highest first)
void sortLeaderboard(Team teams[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (teams[j].score < teams[j + 1].score ||
               (teams[j].score == teams[j + 1].score && teams[j].missions < teams[j + 1].missions)) {
                Team temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
}

// Print all teams in a table
void displayTeams(Team teams[], int size) {
    if (size == 0) {
        cout << "\nLeaderboard is empty. No teams registered yet.\n";
        return;
    }

    cout << "\n===========================================================\n"
         << "                CAMPUS QUEST LEADERBOARD                   \n"
         << "===========================================================\n";
    cout << "Rank  ID      Team Name                 Score     Missions\n";
    cout << "-----------------------------------------------------------\n";

    for (int i = 0; i < size; i++) {
        printf("%-6d%-8d%-26s%-10d%-10d\n",
               i + 1, teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }
    cout << "===========================================================\n";
}

// Load teams from a file
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return 0;

    char line[LINE_LEN];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
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

// Save teams to a file
int saveTeams(const char* filename, Team teams[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d|%s|%d|%d\n", teams[i].id, teams[i].name, teams[i].score, teams[i].missions);
    }

    fclose(file);
    return 1;
}

// Read a line of text from the user
void readText(const char* prompt, char text[], int limit) {
    cout << prompt;
    if (fgets(text, limit, stdin) != NULL)
        text[strcspn(text, "\n")] = '\0';
}

// Read a whole number from the user. Returns true if valid.
bool readInt(const char* prompt, int &value) {
    char line[LINE_LEN];
    cout << prompt;
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
