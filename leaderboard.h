#ifndef LEADERBOARD_H
#define LEADERBOARD_H

// Required Data Model
typedef struct {
    int id;
    char name[40];
    int score;
    int missions;
} Team;

// Core Function Prototypes (Cross-Platform C++)

// 1. Search: Returns 0-based array index, or -1 if not found
int findTeamIndex(const Team* teams, int size, int id);

// 2. Memory & Registration: Adds team and doubles capacity if full using safe realloc
int addTeam(Team** teams, int* size, int* capacity, Team newTeam);

// 3. Record Mission: Adds 1..100 points and increments mission count
int recordMission(Team* teams, int size, int id, int points);

// 4. Delete Team: Shifts elements left and decrements size
int deleteTeam(Team* teams, int* size, int id);

// 5. Sorting: Descending by score, tie-breaking by mission count
void sortLeaderboard(Team* teams, int size);

// 6. Display: Formatted console table
void showLeaderboard(const Team* teams, int size);

// 7. File Loading: Reads pipe-separated lines (id|name|score|missions)
int loadTeams(const char* filename, Team** teams, int* size, int* capacity);

// 8. File Saving: Writes current leaderboard to file
int saveTeams(const char* filename, const Team* teams, int size);

// 9. Memory Cleanup: Safely frees memory and sets pointer to NULL
void freeLeaderboard(Team** teams, int* size, int* capacity);

#endif // LEADERBOARD_H
