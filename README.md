# Campus-Quest-Team-Leaderboard-Challlenge

Safe dynamic team challenge leaderboard in C++ with file persistence and interactive terminal interface for Campus Quest.

## Project Structure
```
Campus-Quest-Team-Leaderboard-Challlenge/
├── leaderboard.h       # Struct definitions & function prototypes
├── leaderboard.cpp     # Memory, record operations, file I/O & sort implementations
├── main.cpp            # Interactive 7-option console menu
├── teams.txt           # Sample pipe-delimited data file (101|Byte Bandits|120|2)
├── Makefile            # One-command build script
├── README.md           # Project overview
├── TEAM_ROLES.md       # Team responsibilities & defense cheat sheet
└── GETTING_STARTED.md  # Step-by-step setup & git guide
```

## Quick Start
```bash
# Build and Run on Linux / macOS
make
./leaderboard

# Build on Windows
g++ -Wall -Wextra -std=c++11 main.cpp leaderboard.cpp -o leaderboard.exe
leaderboard.exe
```

See [GETTING_STARTED.md](GETTING_STARTED.md) for full setup instructions and [TEAM_ROLES.md](TEAM_ROLES.md) for team role assignments.
