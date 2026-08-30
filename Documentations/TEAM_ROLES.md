# Team Roles

**Course:** Algorithm Mini Project
**Project:** Campus Quest: Team Challenge Leaderboard
**Repo:** https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git

## Who Does What

| Member | Position | Role | What They Handle |
| :--- | :--- | :--- | :--- |
| Tha Sotheara (Soun Som) | Leader | Integration & Presenter | Menu loop in main.cpp, connecting everything together, live demo |
| Thong Dyna | Vice Lead | Memory Management | Dynamic array (addTeam), freeing memory (freeMemory) |
| Hoeurn Puthirathanak | Member | File I/O | Loading and saving teams (loadTeams, saveTeams) |
| Houth Lyheng | Member | Team Operations | Team struct, finding by ID, adding points, deleting teams |
| Chao Achharatepy | Member | Sorting & Display | Sorting leaderboard, printing table, testing |

## How to Build

### Linux / macOS:
```bash
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard
./leaderboard
```

### Windows:
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

## What Each Person Should Know for Presentation

### Tha Sotheara (Leader)
- **Your file:** main.cpp
- **What you did:** Built the menu loop that takes user input and calls the right functions
- **If asked:** "The main loop shows a menu, reads input, and calls functions in leaderboard.cpp based on what the user picks. It also saves data when you exit."

### Thong Dyna (Vice Lead)
- **Your file:** leaderboard.cpp (addTeam and freeMemory)
- **What you did:** Made the array grow when it's full, and clean up memory when done
- **If asked:** "We start with no space. When we add a team and the array is full, we double the size using realloc. We use a temp pointer so if it fails, we don't lose our data."

### Hoeurn Puthirathanak
- **Your file:** leaderboard.cpp (loadTeams and saveTeams)
- **What you did:** Reading and writing teams from/to teams.txt
- **If asked:** "We save teams as id|name|score|missions, one per line. When loading, we split each line by the | character. We also handle both Windows and Linux line endings."

### Houth Lyheng
- **Your file:** leaderboard.h and leaderboard.cpp (findTeamIndex, recordMission, deleteTeam)
- **What you did:** The Team struct and operations on it
- **If asked:** "Each team is a struct with id, name, score, and missions. To delete, we shift everything after it one spot left. To find a team, we loop through and check the ID."

### Chao Achharatepy
- **Your file:** leaderboard.cpp (sortLeaderboard, showLeaderboard)
- **What you did:** Sorting and displaying the teams
- **If asked:** "We use bubble sort to put the highest score first. If two teams have the same score, the one with more missions goes higher."
