# PGI - C - TUI

## How to build the project

### Linux or WSL (prefered dev env)

Requirements:

- CMake version >=3.15
- gcc with C23 support
- Make or ninja

If using make:

```bash
mkdir build/
cd build/
cmake ..
make
# You will find the executable in  build/src/unnamed_project
```

Feeling like a Ninja ?

```bash
cd build/
cmake -G Ninja ..
ninja
# You will find the executable in  build/src/unnamed_project
```

### Windows

To be verified !
But using WSL is the recomended way

#### sublime ?

... ?

#### vscode

install the cmake tools extenssion

## Project structure

```
CMakeLists.txt
README.md
docs/
  projet2025.pdf
  samples/
    classes.csv
    etudiants.csv
    matiere_clas_asso.csv
    matieres.csv
    notes.csv
lib/
src/
  CMakeLists.txt
  main.c
  affichage/
    application.c
    application.h
  classe/
    classe_matiere.c
    classe_matiere.h
    classe.c
    classe.h
  etudiant/
    etudiant.c
    etudiant.h
  matiere/
    matiere.c
    matiere.h
  note/
    note.c
    note.h
  ui/
    menu.c
    menu.h
  utils/
    csv_utils.c
    csv_utils.h
    fn_helper.c
    fn_helper.h
    init.c
    init.h
submodules/
  external/
    PDcurses/
      CMakeLists.txt
test/
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
