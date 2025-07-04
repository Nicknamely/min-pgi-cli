# Definie la version minimale de CMake requise
cmake_minimum_required(VERSION 3.15)

project(unnamed_project
        VERSION 0.0.1
        LANGUAGES C
        DESCRIPTION "Logiciele de gestion des notes d'etudiants")


set(SOURCE_FILES
                src/main.c
                src/etudiant.c
                src/matiere.c
                src/note.c
                src/classe.c
                src/helper.c)

include_directories(include)

add_executable(unnamed_project ${SOURCE_FILES})

# Pour des tests
# add_subdirectory(test)
