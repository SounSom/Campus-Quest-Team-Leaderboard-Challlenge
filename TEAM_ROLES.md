# Campus Quest: Leaderboard - Fast-Track Team Guide (Due Tonight)

**Course:** Algorithm Mini Project  
**Project:** Campus Quest: Team Challenge Leaderboard  
**Target Platforms:** Windows, Linux, and macOS (Cross-Platform)  
**Timeline:** Fast-Track Sprint (Deadline: Tonight)  
**GitHub Repo:** [Campus-Quest-Team-Leaderboard-Challlenge](https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git)

---

## 1. Complete Team Roster & Role Assignments (5 Members)

| Team Member | Position | Assigned Role | What You Code / Handle |
| :--- | :--- | :--- | :--- |
| **Tha Sotheara** *(Soun Som)* | Leader | **Integration Captain & Presenter** | Simple text menu loop (`main.cpp`), program coordination & cross-platform live demo |
| **Thong Dyna** | Vice Lead | **Memory Guardian** | Dynamic array allocation, capacity doubling when full (`realloc`), memory cleanup (`freeLeaderboard`) |
| **Hoeurn Puthirathanak** | Member | **Persistence Architect** | Cross-platform file I/O (`loadTeams`, `saveTeams`), handling both Windows `\r\n` and Linux/macOS `\n` line endings |
| **Houth Lyheng** | Member | **Record Architect** | `Team` struct, finding team by ID (`findTeamIndex`), adding mission points (`recordMission`), deleting team (`deleteTeam`) |
| **Chao Achharatepy** | Member | **Test Captain & Display** | Sorting leaderboard descending by score (`sortLeaderboard`), printing table (`showLeaderboard`), running T1–T11 tests |

---

## 2. Cross-Platform Compatibility Rules

To ensure the project builds and runs identically on Windows, Linux, and macOS:

1. **Standard C++ Only:** Use only portable standard libraries (`<iostream>`, `<cstring>`, `<cstdlib>`, `<cstdio>`, `<iomanip>`). Avoid OS-specific headers like `<windows.h>`, `<conio.h>`, or `<unistd.h>`.
2. **Line Ending Safety (CRLF vs LF):** When reading `teams.txt` in `loadTeams`, trim both `\r` (Windows carriage return) and `\n` (Unix newline) from line ends.
3. **Path Separators:** Use relative filenames (e.g. `"teams.txt"`) without hardcoded Windows backslashes `\` or Unix slashes `/`.

---

## 3. Checkpoint Defense Cheat Sheet (Simple Answers)

### 1. Tha Sotheara (Leader - Integration & Presenter)
* **Assigned Code:** `main.cpp`, Menu Loop, Demo
* **Presentation Answer:** "I built the cross-platform interactive menu in `main.cpp` that drives the program. It connects user choices to our memory and file functions, making sure invalid choices are handled cleanly on all operating systems."

### 2. Thong Dyna (Vice Lead - Memory Guardian)
* **Assigned Code:** Dynamic allocation in `leaderboard.cpp` (`addTeam`, `freeLeaderboard`)
* **Presentation Answer:** "We start with capacity 0 and double it when the array is full. We use a temporary pointer with `realloc` so if allocation fails, our original data is preserved without causing memory leaks or crashes."

### 3. Hoeurn Puthirathanak (Member - Persistence Architect)
* **Assigned Code:** File I/O in `leaderboard.cpp` (`loadTeams`, `saveTeams`)
* **Presentation Answer:** "I handle file persistence with pipe formatting (`id|name|score|missions`). When loading, our code strips both Windows `\r` and Unix `\n` line endings so files created on Windows work seamlessly on Linux or macOS."

### 4. Houth Lyheng (Member - Record Architect)
* **Assigned Code:** Struct & operations in `leaderboard.cpp` (`findTeamIndex`, `recordMission`, `deleteTeam`)
* **Presentation Answer:** "Each team is stored as a complete `Team` struct. When deleting a team, we shift complete struct records left to keep ID, name, score, and missions together as one atomic unit."

### 5. Chao Achharatepy (Member - Test Captain & Display)
* **Assigned Code:** `sortLeaderboard`, `showLeaderboard`, Test Verification
* **Presentation Answer:** "We sort descending by score and use missions as a tie-breaker. We tested boundary cases including empty lists, duplicate IDs, invalid points (0 or 101), and file reload persistence."

---

## 4. How to Build & Run on Any OS

### On Linux and macOS:
```bash
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard
./leaderboard
```

### On Windows (Command Prompt / PowerShell / MinGW / Git Bash):
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```
