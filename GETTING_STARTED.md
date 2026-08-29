# Getting Started

**Repo:** https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git

## What You Need

- Git installed
- A C++ compiler (g++ or clang++):
  - Windows: MinGW or WSL
  - Linux: `sudo apt install g++ build-essential`
  - macOS: `xcode-select --install`

## Step 1: Clone the Repo

```bash
git clone https://github.com/SounSom/Campus-Quest-Team-Leaderboard-Challlenge.git
cd Campus-Quest-Team-Leaderboard-Challlenge
```

## Step 2: Create Your Branch

- Tha Sotheara: `git checkout -b feature/menu-ui`
- Thong Dyna: `git checkout -b feature/memory-guardian`
- Hoeurn Puthirathanak: `git checkout -b feature/file-persistence`
- Houth Lyheng: `git checkout -b feature/record-operations`
- Chao Achharatepy: `git checkout -b feature/sort-and-tests`

## Step 3: Build and Run

### Linux / macOS:
```bash
make
./leaderboard
```

### Windows:
```cmd
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

## Step 4: Save Your Work

```bash
git add .
git commit -m "Implement my assigned function"
git push origin <your-branch-name>
```
