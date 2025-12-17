# PF Theory Assignment – Tic Tac Toe

This is a 4x4 Tic Tac Toe game developed as a **Programming Fundamentals (PF) theory assignment** for the 1st semester.  
The program is written in C and includes the following features:

## Features
- Two-player console-based game
- Displays the board and updates after each move
- Checks for row, column, and diagonal wins
- Logs each game to `games_log.txt`
- Search past games by player name
- Shows statistics of the top three players by wins
- Handles tied games and invalid moves

## How to Run
1. Compile the source code:
   ```bash
   gcc main.c -o tictactoe.exe  # Windows
   gcc main.c -o tictactoe      # Linux/macOS
./tictactoe.exe   # Windows
./tictactoe       # Linux/macOS
