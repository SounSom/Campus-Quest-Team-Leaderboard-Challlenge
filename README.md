# 🏆 Campus Quest: Team Challenge Leaderboard

[![Language](https://img.shields.io/badge/Language-C%2B%2B11-blue.svg)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)]()
[![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)]()
[![License](https://img.shields.io/badge/License-MIT-orange.svg)]()

> A robust, cross-platform C++ console application designed to manage, rank, and persist team competition records dynamically and safely.

---

## 📌 Project Overview

**Campus Quest Leaderboard** is an in-memory, file-persisted tournament management system written in pure standard C++. Built with defensive memory architecture, it dynamically expands capacity as teams register, validates inputs, logs earned mission points, and produces a real-time ranked leaderboard with mission tie-breaking.

---

## ✨ Key Features

* **⚡ Dynamic Array Expansion:** Automatically doubles heap allocation using a safe `realloc` strategy with temporary pointer guards to prevent memory corruption.
* **🛡️ Defensive Input Validation:** Enforces positive unique IDs, non-empty team names, non-negative scores, and strictly bounded mission points (`1` to `100`).
* **💾 Cross-Platform File Persistence:** Loads and saves pipe-delimited records (`id|name|score|missions`), handling both Windows (`\r\n`) and Unix (`\n`) line endings seamlessly.
* **📊 Ranked Sorting & Tie-Breaking:** Orders teams descending by score. If scores are equal, completed mission counts resolve ties.
* **🧹 Leak-Free Memory Cleanup:** Explicitly frees all allocated heap memory and resets pointers upon exit.

---

## 📂 Project Architecture

```
Campus-Quest-Team-Leaderboard-Challlenge/
├── Documentations/      # Project documentation and team guides
│   ├── GETTING_STARTED.md
│   ├── MEMBER_GUIDE.md
│   ├── TEAM_ROLES.md
│   └── mini project.md
├── src/                # C++ Source files
│   ├── leaderboard.h   # Data model (Team struct) and shared function prototypes
│   ├── leaderboard.cpp # Dynamic memory, record operations, file I/O & sort logic
│   └── main.cpp        # Interactive 7-option console menu loop
├── teams.txt           # Pipe-delimited data file (id|name|score|missions)
├── Makefile            # Cross-platform 1-command build script
└── README.md           # Master project overview & guide
```

---

## 📄 Data Format Specification

Team records are stored in `teams.txt`, with one record per line using pipe (`|`) delimiters:

```txt
101|Byte Bandits|120|2
102|Pointer Pirates|90|1
103|Logic Legends|150|3
```

| Field Index | Attribute | Constraints | Example |
| :---: | :--- | :--- | :--- |
| **1** | `ID` | Positive Integer, Unique | `101` |
| **2** | `Name` | Non-empty string (max 39 chars) | `Byte Bandits` |
| **3** | `Score` | Non-negative Integer | `120` |
| **4** | `Missions` | Non-negative Integer | `2` |

---

## 🚀 Quick Start & Build Guide

### Prerequisites
* A standard C++ compiler supporting C++11 (`g++` or `clang++`).
* `make` (optional, for Linux/macOS).

### Build & Run Instructions

#### 🐧 Linux & 🍎 macOS
```bash
# Build using Makefile
make

# Run application
./leaderboard
```

#### 🪟 Windows (Command Prompt / PowerShell / Git Bash)
```cmd
# Compile with g++
g++ -Wall -Wextra -std=c++11 src/main.cpp src/leaderboard.cpp -o leaderboard.exe

# Run application
leaderboard.exe
```

---

## 🖥️ Interactive Console Interface

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
Enter your choice (1-7): 
```

---

## 👥 Team Roster & Roles

| Member | Role | Assigned Modules & Functions |
| :--- | :--- | :--- |
| **Tha Sotheara** *(Soun Som)* | **Leader & Integration Captain** | Menu loop UI (`main.cpp`), Input cleaning, System wiring, Live demo |
| **Thong Dyna** | **Vice Lead & Memory Guardian** | Dynamic allocation (`addTeam`), Memory cleanup (`freeLeaderboard`) |
| **Hoeurn Puthirathanak** | **Persistence Architect** | File parsing (`loadTeams`), File saving (`saveTeams`), CRLF normalization |
| **Houth Lyheng** | **Record Architect** | `Team` struct, Search (`findTeamIndex`), Mission update, Deletion shift |
| **Chao Achharatepy** | **Test Captain & Display Lead** | Ranking (`sortLeaderboard`), Formatted table (`showLeaderboard`), Test suite |

---

## 🧪 Benchmark Test Matrix (T1 – T11)

| Test ID | Scenario | Expected Behavior | Status |
| :---: | :--- | :--- | :---: |
| **T1** | Empty State | Displays clean empty notice without crashing | Pass |
| **T2** | First Addition | Adds team; size increments to 1; fields intact | Pass |
| **T3** | Growth Boundary | Array capacity doubles safely when full | Pass |
| **T4** | Duplicate ID | Rejects duplicate ID; size remains unchanged | Pass |
| **T5** | Invalid Points | Rejects points outside 1..100; score unchanged | Pass |
| **T6** | Search Absent | Returns -1 for non-existent team ID | Pass |
| **T7** | Delete Shift | Shifts elements left; size decrements by 1 | Pass |
| **T8** | Tie-Break Sort | Highest score first; mission count tie-breaker | Pass |
| **T9** | Malformed Line | Skips corrupted file lines without crashing | Pass |
| **T10**| Persistence | Saves and restores records accurately across runs | Pass |
| **T11**| Safe Cleanup | Frees all heap memory on exit cleanly | Pass |

---

## 📜 License

This project is open source and available under the [MIT License](LICENSE).
