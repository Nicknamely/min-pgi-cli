#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include "../classe/classe.h"
#include "../classe/classe_matiere.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../note/note.h"
#include <stdio.h>
#include <stdlib.h>

// Fonctions utilitaires pour gestion CSV
/*
 * @brief lit une ligne CSV et la split selon le separateur
 * @param ligne la ligne a parser
 * @param delim le separateur
 * @param champs tableau de pointeurs resultat
 * @param max_champs nombre max de champs
 * @return nombre de champs trouves
 */
int split_csv_line(char *ligne, char delim, char **champs, int max_champs);
/*
 * @brief supprime le retour chariot d'une chaine
 * @param str chaine a nettoyer
 */
void trim_newline(char *str);
/*
permet de lire une ligne d'un fichier CSV et de la stocker dans un buffer, en
s'assurant de ne pas depasser la taille max du buffer.
* @brief lit une ligne du fichier et la place dans buf
* @param f fichier ouvert
* @param buf buffer de destination
* @param max taille max du buffer
* @return 1 si ok, 0 si fin
*/
int lire_ligne(FILE *f, char *buf, int max);
/*
 * @brief reinitialise le contenu du tableau dynamique
 * @param ptr pointeur vers le tableau
 * @param taille taille du tableau
 */
void reinit_tab(void *ptr, size_t taille);

/*
 * @brief charge les matieres depuis un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des matieres
 * @return 0 si succes, -1 sinon
 */
int charger_matieres_csv(const char *chemin, MatiereDB *db);
/*
 * @brief charge les classes depuis un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des classes
 * @return 0 si succes, -1 sinon
 */
int charger_classes_csv(const char *chemin, ClasseDB *db);
/*
 * @brief charge les etudiants depuis un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des etudiants
 * @return 0 si succes, -1 sinon
 */
int charger_etudiants_csv(const char *chemin, EtudiantDB *db);
/*
 * @brief charge les notes depuis un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des notes
 * @param etudiantDB base de donnees des etudiants
 * @param matiereDB base de donnees des matieres
 * @return 0 si succes, -1 sinon
 */
int charger_notes_csv(const char *chemin, NoteDB *db,
                      const EtudiantDB *etudiantDB, const MatiereDB *matiereDB);
/*
 * @brief exporte les classes vers un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des classes
 * @return 0 si succes, -1 sinon
 */
int exporter_classes_csv(const char *chemin, const ClasseDB *db);
/*
 * @brief exporte les matieres vers un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des matieres
 * @return 0 si succes, -1 sinon
 */
int exporter_matieres_csv(const char *chemin, const MatiereDB *db);
/*
 * @brief exporte les etudiants vers un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des etudiants
 * @return 0 si succes, -1 sinon
 */
int exporter_etudiants_csv(const char *chemin, const EtudiantDB *db);
/*
 * @brief exporte les notes vers un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des notes
 * @return 0 si succes, -1 sinon
 */
int exporter_notes_csv(const char *chemin, const NoteDB *db);
/*
 * @brief exporte les associations classe-matiere vers un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des associations
 * @param db_classe base de donnees des classes
 * @param db_matiere base de donnees des matieres
 * @return 0 si succes, -1 sinon
 */
int exporter_classe_matieres_csv(const char *chemin, const ClasseMatiereDB *db,
                                 const ClasseDB *db_classe,
                                 const MatiereDB *db_matiere);
/*
 * @brief charge les associations classe-matiere depuis un fichier CSV
 * @param chemin chemin du fichier CSV
 * @param db base de donnees des associations
 * @return 0 si succes, -1 sinon
 */
int charger_classe_matieres_csv(const char *chemin, ClasseMatiereDB *db);

#endif // !CSV_UTILS_H
