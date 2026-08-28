# Campus Quest: Leaderboard - Teammate Action & Defense Guide

This guide explains what each team member needs to do now that the repository has been cloned, including how to run the program and answer questions from the lecturer.

---

## 1. Quick Start: Pulling and Running the Project

Since you have already cloned the repository, follow these steps:

### A. Pull the latest code
Open your terminal inside the project directory and run:
```bash
git checkout main
git pull origin main
```

### B. Compile and Run

* **On Linux / macOS:**
  ```bash
  make
  ./leaderboard
  ```

* **On Windows (Command Prompt / PowerShell / Git Bash):**
  ```cmd
  g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
  leaderboard.exe
  ```

---

## 2. Individual Member Guides

---

### 1. Tha Sotheara (Soun Som) - Leader & Integration Captain

* **Your Core File:** `main.cpp`
* **What You Handled:**
  * Interactive 7-option console menu loop.
  * User input cleaning (`clearInputBuffer`) and numerical validation.
  * System wiring between user actions, memory structures, and file I/O.
  * Project coordination and live demo leadership.

* **What to Show the Lecturer:**
  1. Open `main.cpp` and highlight the `switch (choice)` block.
  2. Show how invalid input (such as typing letters instead of numbers 1–7) is handled cleanly without crashing.

* **How to Answer Lecturer Questions:**
  * *Question:* "How does the program process user requests?"
  * *Answer:* "The `main()` loop presents the menu options, cleans input with `clearInputBuffer()`, and routes valid requests to dedicated functions in `leaderboard.cpp`. When exiting, it automatically saves the leaderboard to `teams.txt` and frees heap memory."

---

### 2. Thong Dyna - Vice Lead & Memory Guardian

* **Your Core File:** `leaderboard.cpp` (Functions: `addTeam` and `freeLeaderboard`)
* **What You Handled:**
  * Dynamic memory allocation starting at `capacity = 0`.
  * Array doubling strategy when `size >= capacity`.
  * Safe memory reallocation using temporary pointers.
  * Heap cleanup upon program termination.

* **What to Show the Lecturer:**
  1. Open `leaderboard.cpp` and point to `addTeam`.
  2. Highlight `realloc` with `Team* temp`.
  3. Show `freeLeaderboard` where `free(*teams)` is called.

* **How to Answer Lecturer Questions:**
  * *Question:* "Why use a temporary pointer during realloc?"
  * *Answer:* "If `realloc` fails and returns `NULL`, assigning directly to `*teams` would overwrite our pointer and lose existing data. By storing the result in a `temp` pointer first, old state remains safe even if memory allocation fails."

---

### 3. Hoeurn Puthirathanak - Persistence Architect

* **Your Core File:** `leaderboard.cpp` (Functions: `loadTeams` and `saveTeams`)
* **What You Handled:**
  * Text file persistence in pipe-delimited format (`id|name|score|missions`).
  * Cross-platform line ending trimming (`\r\n` for Windows and `\n` for Linux/macOS).
  * Line-by-line parsing using `fgets` and `strtok`.
  * Skipping malformed or corrupted file lines safely.

* **What to Show the Lecturer:**
  1. Open `teams.txt` to show sample records (`101|Byte Bandits|120|2`).
  2. Open `leaderboard.cpp` and show `loadTeams`.
  3. Highlight the trimming loop that removes `\r` and `\n` characters.

* **How to Answer Lecturer Questions:**
  * *Question:* "How do you handle corrupted lines when reading files?"
  * *Answer:* "We use `strtok` to check for all four required pipe fields. If any field is missing or malformed, the loop skips that line and continues reading valid records without crashing."

---

### 4. Houth Lyheng - Record Architect

* **Your Core File:** `leaderboard.h` & `leaderboard.cpp` (Functions: `findTeamIndex`, `recordMission`, `deleteTeam`)
* **What You Handled:**
  * `Team` struct design holding `id`, `name`, `score`, and `missions`.
  * Team lookup by unique integer ID (`findTeamIndex`).
  * Mission point validation (1 to 100 points) and team updating.
  * Left-shift deletion preserving array continuity (`deleteTeam`).

* **What to Show the Lecturer:**
  1. Open `leaderboard.h` and point to `typedef struct { ... } Team;`.
  2. Open `leaderboard.cpp` and show `deleteTeam` where elements shift left.

* **How to Answer Lecturer Questions:**
  * *Question:* "Why shift full struct records when deleting a team?"
  * *Answer:* "Each team is an atomic `Team` struct object. Shifting the whole struct left ensures ID, name, score, and mission counts always stay connected without separating."

---

### 5. Chao Achharatepy - Test Captain & Display Lead

* **Your Core File:** `leaderboard.cpp` (Functions: `sortLeaderboard` and `showLeaderboard`)
* **What You Handled:**
  * Formatting the console output into a clear, aligned table.
  * Sorting teams descending by score.
  * Implementing mission count as a tie-breaker when scores are equal.
  * Verifying boundary test cases (empty list, duplicates, invalid scores).

* **What to Show the Lecturer:**
  1. Open `leaderboard.cpp` and point to `sortLeaderboard`.
  2. Highlight the tie-breaker condition `if (teams[j].score == teams[j+1].score)`.
  3. Show `showLeaderboard` formatted with `std::setw`.

* **How to Answer Lecturer Questions:**
  * *Question:* "How does tie-breaking work in your sorting algorithm?"
  * *Answer:* "We use bubble sort on struct objects. If two teams have identical scores, we compare their completed mission counts and place the team with more missions higher on the leaderboard."

---

## 3. Recommended Lecturer Live Demo Steps

1. **Start the program:** Run `./leaderboard` or `leaderboard.exe`. Show that 3 teams load automatically from `teams.txt`.
2. **Display Leaderboard (Option 5):** Show the ranked table sorted by score.
3. **Register New Team (Option 1):** Add ID `104`, Name `Code Knights`, Score `200`, Missions `4`.
4. **Test Validation (Option 2):** Try adding `0` or `150` mission points to show error handling, then enter valid points (`50`).
5. **Show Leaderboard (Option 5):** Demonstrate that Team 104 moved to Rank 1.
6. **Remove Team (Option 4):** Delete team `102` to demonstrate left-shifting.
7. **Exit & Reload (Option 7):** Exit the program, restart it, and select Option 5 to prove the updated list was saved to `teams.txt` and restored.
