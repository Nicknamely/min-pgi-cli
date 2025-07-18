# Definie la version minimale de CMake requise
cmake_minimum_required(VERSION 3.15)

project(mini-pgi-cli
        VERSION 1.0.0
        LANGUAGES C
        DESCRIPTION "Logiciele de gestion des notes d'etudiants")



add_subdirectory(src)


# Pour des tests
# add_subdirectory(test)
