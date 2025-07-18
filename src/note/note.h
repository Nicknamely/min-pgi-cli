#ifndef NOTE_H
#define NOTE_H
#include "../classe/classe_matiere.h"
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include <stdlib.h>

// Structure Note (etre_note)
typedef struct {
  int numero_etudiant;
  int reference_matiere;
  float noteCC;
  float noteDS;
} Note;

// Tableau dynamique de notes
typedef struct {
  Note *notes;
  size_t capacite;
  size_t taille;
} NoteDB;

// Fonctions CRUD pour Note
/*
 * @brief initialise la structure NoteDB avec une capacite initiale
 * @param db pointeur vers NoteDB a initialiser
 * @param capacite_initial taille de depart du tableau
 */
void initialiser_NoteDB(NoteDB *db, size_t capacite_initial);

/*
 * @brief ajoute une note si l'etudiant et la matiere existent
 * @param db base de donnees des notes
 * @param nouvelle_note la note a ajouter
 * @param etudiantDB base de donnees des etudiants
 * @param matiereDB base de donnees des matieres
 * @return 1 si ajoute, 0 sinon
 */
int ajouter_note(NoteDB *db, Note nouvelle_note, const EtudiantDB *etudiantDB,
                 const MatiereDB *matiereDB);

// supprime la note a l'index donne
void supprimer_note(NoteDB *db, size_t index);

/*
 * @brief affiche toutes les notes avec details etudiant et matiere
 * @param db base de donnees des notes
 * @param db_etudiant base de donnees des etudiants
 * @param db_matiere base de donnees des matieres
 */
void afficher_notes(const NoteDB *db, const EtudiantDB *db_etudiant,
                    const MatiereDB *db_matiere);

// modifie la note a l'index donne
void modifier_note(NoteDB *db, size_t index, Note nouvelle_note);

/*
 * @brief cherche une note par etudiant et matiere
 * @param db base de donnees des notes
 * @param numero_etudiant identifiant etudiant
 * @param reference_matiere identifiant matiere
 * @return index si trouve, -1 sinon
 */
int rechercher_note(const NoteDB *db, int numero_etudiant,
                    int reference_matiere);

/*
 * @brief libere la memoire du NoteDB
 * @param db base de donnees des notes
 */
void freeNoteDB(NoteDB *db);

/*
 * @brief ajoute toutes les notes d'un etudiant pour chaque matiere de sa classe
 * @param db base de donnees des notes
 * @param numero_etudiant identifiant etudiant
 * @param db_etudiant base de donnees des etudiants
 * @param db_classe_matiere associations classe-matiere
 * @param db_matiere base de donnees des matieres
 * @return nombre de notes ajoutees
 */
int ajouter_notes_etudiant_toutes_matieres(
    NoteDB *db, int numero_etudiant, const EtudiantDB *db_etudiant,
    const ClasseMatiereDB *db_classe_matiere, const MatiereDB *db_matiere);

/*
 * @brief ajoute les notes de tous les etudiants d'une classe pour une matiere
 * @param db base de donnees des notes
 * @param code_classe identifiant classe
 * @param ref_matiere identifiant matiere
 * @param db_etudiant base de donnees des etudiants
 * @param db_classe_matiere associations classe-matiere
 * @param db_matiere base de donnees des matieres
 * @return nombre de notes ajoutees
 */
int ajouter_notes_classe_matiere(NoteDB *db, int code_classe, int ref_matiere,
                                 const EtudiantDB *db_etudiant,
                                 const ClasseMatiereDB *db_classe_matiere,
                                 const MatiereDB *db_matiere);

#endif // !NOTE_H
