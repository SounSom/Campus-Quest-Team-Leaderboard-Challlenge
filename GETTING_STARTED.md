# Campus Quest: Leaderboard - Beginner GitHub & Setup Guide

**Repository:** [https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git](https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git)  
**Project Goal:** Safe Dynamic C++ Leaderboard for Campus Quest  
**Supported OS:** Windows, macOS, Linux

---

## 1. Prerequisites

Before starting, make sure you have:
* **Git** installed on your system.
* A **C++ Compiler** (`g++` or `clang++`):
  * **Windows:** MinGW / MSYS2 / WSL / Visual Studio C++ tools
  * **Linux:** `sudo apt install g++ build-essential` (Ubuntu/Debian)
  * **macOS:** `xcode-select --install` (Apple Clang / g++)

---

## 2. Step 1: Clone the Repository

Open your terminal and run:

```bash
git clone https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git
cd Campus-Quest-Team-Leaderboard-Challlenge
```

---

## 3. Step 2: Recommended Project Structure

```
Campus-Quest-Team-Leaderboard-Challlenge/
├── leaderboard.h       # Struct definitions & function prototypes
├── leaderboard.cpp     # Memory, record operations, file I/O & sort implementations
├── main.cpp            # Interactive 7-option console menu
├── teams.txt           # Sample pipe-delimited data file (101|Byte Bandits|120|2)
├── Makefile            # One-command build script
├── README.md           # Project overview
├── TEAM_ROLES.md       # Team responsibilities & defense cheat sheet
├── MEMBER_GUIDE.md     # Individual teammate action & presentation guide
└── GETTING_STARTED.md  # Step-by-step setup guide
```

---

## 4. Step 3: Create Your Feature Branch

* **Tha Sotheara (Leader):** `git checkout -b feature/menu-ui`
* **Thong Dyna (Vice Lead):** `git checkout -b feature/memory-guardian`
* **Hoeurn Puthirathanak:** `git checkout -b feature/file-persistence`
* **Houth Lyheng:** `git checkout -b feature/record-operations`
* **Chao Achharatepy:** `git checkout -b feature/sort-and-tests`

---

## 5. Step 4: How to Build and Run

### On Linux & macOS:
```bash
make
./leaderboard
```

### On Windows:
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

---

## 6. Step 5: Save, Commit, and Push Your Work

```bash
git add .
git commit -m "Implement assigned function"
git push origin <your-branch-name>
```
