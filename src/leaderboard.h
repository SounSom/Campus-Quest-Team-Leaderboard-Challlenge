#ifndef LEADERBOARD_H
#define LEADERBOARD_H

struct Team {
    int id;
    char name[40];
    int score;
    int missions;
};

int findTeamIndex(Team teams[], int size, int id);
int addTeam(Team* &teams, int &size, int &capacity, Team newTeam);
int recordMission(Team teams[], int size, int id, int points);
int deleteTeam(Team teams[], int &size, int id);
void sortLeaderboard(Team teams[], int size);
void showLeaderboard(Team teams[], int size);
int loadTeams(const char* filename, Team* &teams, int &size, int &capacity);
int saveTeams(const char* filename, Team teams[], int size);
void freeMemory(Team* &teams, int &size, int &capacity);

#endif
