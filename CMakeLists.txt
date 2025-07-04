# Definie la version minimale de CMake requise
cmake_minimum_required(VERSION 3.15)

project(unnamed_project
        VERSION 0.0.1
        LANGUAGES C
        DESCRIPTION "Logiciele de gestion des notes d'etudiants")



add_subdirectory(src)

add_executable(unnamed_project ${SOURCE_FILES})

# Pour des tests
# add_subdirectory(test)
