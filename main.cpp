#include "leaderboard.h"
#include <iostream>
#include <limits>
#include <cstring>

const char* DATA_FILE = "teams.txt";

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Team* teams = NULL;
    int size = 0;
    int capacity = 0;

    // Automatically load existing records on startup
    int loaded = loadTeams(DATA_FILE, &teams, &size, &capacity);
    if (loaded > 0) {
        std::cout << "[Startup] Loaded " << loaded << " team(s) from " << DATA_FILE << ".\n";
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
        std::cout << "Enter your choice (1-7): ";

        if (!(std::cin >> choice)) {
            std::cout << "[Error] Invalid input. Please enter a number from 1 to 7.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: {
                Team newTeam;
                std::cout << "Enter Team ID (positive integer): ";
                if (!(std::cin >> newTeam.id) || newTeam.id <= 0) {
                    std::cout << "[Error] ID must be a positive integer.\n";
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                std::cout << "Enter Team Name (max 39 characters): ";
                std::cin.getline(newTeam.name, sizeof(newTeam.name));
                if (strlen(newTeam.name) == 0) {
                    std::cout << "[Error] Team name cannot be empty.\n";
                    break;
                }

                std::cout << "Enter Initial Score (non-negative): ";
                if (!(std::cin >> newTeam.score) || newTeam.score < 0) {
                    std::cout << "[Error] Score must be non-negative.\n";
                    clearInputBuffer();
                    break;
                }

                std::cout << "Enter Completed Missions (non-negative): ";
                if (!(std::cin >> newTeam.missions) || newTeam.missions < 0) {
                    std::cout << "[Error] Completed missions must be non-negative.\n";
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (addTeam(&teams, &size, &capacity, newTeam)) {
                    std::cout << "[Success] Team '" << newTeam.name << "' registered successfully.\n";
                }
                break;
            }

            case 2: {
                int id, points;
                std::cout << "Enter Team ID: ";
                if (!(std::cin >> id)) {
                    std::cout << "[Error] Invalid ID input.\n";
                    clearInputBuffer();
                    break;
                }
                std::cout << "Enter Mission Points (1 to 100): ";
                if (!(std::cin >> points)) {
                    std::cout << "[Error] Invalid points input.\n";
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (recordMission(teams, size, id, points)) {
                    std::cout << "[Success] Recorded " << points << " points for team ID " << id << ".\n";
                }
                break;
            }

            case 3: {
                int id;
                std::cout << "Enter Team ID to search: ";
                if (!(std::cin >> id)) {
                    std::cout << "[Error] Invalid ID input.\n";
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                int idx = findTeamIndex(teams, size, id);
                if (idx != -1) {
                    std::cout << "\n[Team Found]\n";
                    std::cout << "  ID:       " << teams[idx].id << "\n";
                    std::cout << "  Name:     " << teams[idx].name << "\n";
                    std::cout << "  Score:    " << teams[idx].score << "\n";
                    std::cout << "  Missions: " << teams[idx].missions << "\n";
                } else {
                    std::cout << "[Info] Team with ID " << id << " was not found.\n";
                }
                break;
            }

            case 4: {
                int id;
                std::cout << "Enter Team ID to remove: ";
                if (!(std::cin >> id)) {
                    std::cout << "[Error] Invalid ID input.\n";
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (deleteTeam(teams, &size, id)) {
                    std::cout << "[Success] Team ID " << id << " removed.\n";
                }
                break;
            }

            case 5: {
                sortLeaderboard(teams, size);
                showLeaderboard(teams, size);
                break;
            }

            case 6: {
                if (saveTeams(DATA_FILE, teams, size)) {
                    std::cout << "[Success] Saved " << size << " team(s) to " << DATA_FILE << ".\n";
                }
                break;
            }

            case 7: {
                // Save before exit
                saveTeams(DATA_FILE, teams, size);
                std::cout << "[Exit] Saved data and cleaning up memory...\n";
                break;
            }

            default:
                std::cout << "[Error] Please choose a valid option (1-7).\n";
                break;
        }
    }

    // Safe memory cleanup
    freeLeaderboard(&teams, &size, &capacity);
    std::cout << "Goodbye!\n";
    return 0;
}
