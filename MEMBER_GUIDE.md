# Teammate Guide

How to pull the code, run it, and present your part.

## 1. Get the Latest Code

```bash
git checkout main
git pull origin main
```

## 2. Build and Run

**Linux / macOS:**
```bash
make
./leaderboard
```

**Windows:**
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

## 3. What Each Person Should Show

### Tha Sotheara - Leader
- **File:** main.cpp
- **Show:** The switch/if block that handles menu choices, and how bad input (letters, floats) gets rejected
- **If asked "How does the program work?":**
  "main() shows a menu, reads what the user picks, and calls the right function in leaderboard.cpp. When you exit, it saves the data and frees memory."

### Thong Dyna - Vice Lead
- **File:** leaderboard.cpp (addTeam and freeMemory)
- **Show:** The part where realloc doubles the array, using a temp pointer
- **If asked "Why use a temp pointer with realloc?":**
  "If realloc fails and returns NULL, we'd lose our data if we wrote it directly. The temp pointer keeps our original data safe."

### Hoeurn Puthirathanak
- **File:** leaderboard.cpp (loadTeams and saveTeams)
- **Show:** How we read the file line by line and split by `|`
- **If asked "How do you handle bad lines in the file?":**
  "We check that strtok finds all 4 parts. If any part is missing, we skip that line and keep going."

### Houth Lyheng
- **File:** leaderboard.h and leaderboard.cpp (findTeamIndex, recordMission, deleteTeam)
- **Show:** The Team struct and the delete function that shifts records left
- **If asked "How does delete work?":**
  "We find the team's position, then move everything after it one spot to the left and decrease the count."

### Chao Achharatepy
- **File:** leaderboard.cpp (sortLeaderboard, showLeaderboard)
- **Show:** The bubble sort with the tie-breaker check
- **If asked "How does tie-breaking work?":**
  "If two teams have the same score, we compare their mission counts. More missions = higher rank."

## 4. Demo Steps for Presentation

1. Run `./leaderboard` - show that teams load from teams.txt
2. Press 5 - show the sorted leaderboard
3. Press 1 - add a new team (ID 104, name Code Knights, score 200, missions 4)
4. Press 2 - try adding 0 and 150 points (both get rejected), then add 50 points
5. Press 5 - show the updated leaderboard (new team should be at top)
6. Press 4 - remove team 102
7. Press 7 - exit and restart to prove data was saved
