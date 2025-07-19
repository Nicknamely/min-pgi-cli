# PGI-CLI

## How to build the project

Dans le repertoir de depart assurez-vous d'avoir le repertoir `build/`

```bash
gcc -o build/projetC.exe ./src/main.c ./src/*/*.c

```
Make:
```bash
cmake -S . -B build
cmake --build build
# You will find the executable in  build/src/
```

Ninja:

```bash
cmake -S . -B build -G Ninja
cmake --build build
# You will find the executable in  build/src/
```

### Windows

To be verified !
But using WSL is the recomended way; a POSIX compliant environment (UNIX BSD LINUX)


#### vscode

install the cmake tools extenssion
Then run it (f5) *to be confirmed*

## Project structure

```
❯ tree
.
├── CMakeLists.txt
├── docs
│   └── projet2025.pdf
├── README.md
├── src
│   ├── affichage
│   │   ├── application.c
│   │   └── application.h
│   ├── classe
│   │   ├── classe.c
│   │   ├── classe.h
│   │   ├── classe_matiere.c
│   │   └── classe_matiere.h
│   ├── CMakeLists.txt
│   ├── etudiant
│   │   ├── etudiant.c
│   │   └── etudiant.h
│   ├── main.c
│   ├── matiere
│   │   ├── matiere.c
│   │   └── matiere.h
│   ├── note
│   │   ├── note.c
│   │   └── note.h
│   ├── ui
│   │   ├── menu.c
│   │   └── menu.h
│   └── utils
│       ├── csv_utils.c
│       ├── csv_utils.h
│       ├── fn_helper.c
│       ├── fn_helper.h
│       ├── init.c
│       └── init.h
└── submodules
    └── external
        └── PDcurses
            └── CMakeLists.txt

13 directories, 26 files
```

## Features

- Modular code (classe, matiere, etudiant, note, associations)
- Session system: each session has its own CSV files
- CRUD for all entities
- Import/export CSV for all entities
- Association management (classe-matiere)

## What was planned and remain to do

- TUI with PDcurses (not enough time)
- fn_helper: factorize dynamic array functions into a single function using double pointers
- Add Unity for unit testing

## what was painful
- memory management to avoid buffer overflow specially with dynamic table
- we had to research which data structure was optimal linked-list was the first option
- we thad to learn dynamic table
- error handling :(

