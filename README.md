# Campus Quest: Team Challenge Leaderboard

A simple C++ console program that lets you manage and rank teams in a campus competition.

## What It Does

- Register teams with ID, name, score, and missions
- Add mission points to teams
- Search for a team by ID
- Remove teams
- Sort and display a leaderboard (highest score first, ties broken by missions)
- Save and load team data from a text file

## Files

```
leaderboard.h      - Team struct and function declarations
leaderboard.cpp    - All the functions (add, delete, sort, save, load, etc.)
main.cpp           - The menu that runs the program
teams.txt          - Where team data is saved (id|name|score|missions)
Makefile           - Build script
```

## How to Build and Run

### Linux / macOS
```bash
make
./leaderboard
```

### Windows
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

## Menu

```
=========================================
      CAMPUS QUEST: LEADERBOARD
=========================================
 1. Register New Team
 2. Record Mission Points
 3. Find Team by ID
 4. Remove Team
 5. Show Ranked Leaderboard
 6. Save Leaderboard to File
 7. Exit Program
-----------------------------------------
```

## Data Format

Teams are stored in `teams.txt`, one per line, separated by `|`:

```
101|Byte Bandits|120|2
102|Pointer Pirates|90|1
103|Logic Legends|150|3
```

## Team Members

| Member | Role | What They Work On |
| :--- | :--- | :--- |
| Tha Sotheara (Soun Som) | Leader | Menu loop in main.cpp, project coordination |
| Thong Dyna | Vice Lead | Memory allocation (addTeam, freeMemory) |
| Hoeurn Puthirathanak | Member | File loading and saving (loadTeams, saveTeams) |
| Houth Lyheng | Member | Team struct, search, mission points, delete |
| Chao Achharatepy | Member | Sorting and display (sortLeaderboard, showLeaderboard) |
