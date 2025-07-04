# Les fichiers ".c"
file(GLOB_RECURSE APP_SOURCES "*.c")

# Inclure les sous-répertoires qui contiennent les headers
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/etudiant
    ${CMAKE_CURRENT_SOURCE_DIR}/classe
    ${CMAKE_CURRENT_SOURCE_DIR}/helper
    ${CMAKE_CURRENT_SOURCE_DIR}/matiere
    ${CMAKE_CURRENT_SOURCE_DIR}/note
)

# Definir le nom de l'executable qui resulterons de la compilation des fichiers
# sources
add_executable(unnamed_project ${APP_SOURCES})
