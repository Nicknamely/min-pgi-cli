#ifndef INIT_H
#define INIT_H

int creer_repertoire_session(char *nom_session, char *chemin_complet);
void creer_csv_session(const char *chemin_classes, const char *chemin_matieres,
                       const char *chemin_etudiants, const char *chemin_notes, const char *chemin_associations);
/*
* @brief genere les chemins des fichiers CSV pour une session
* @param base chemin du dossier de session
* @param chemin_classes buffer pour chemin classes.csv
* @param chemin_matieres buffer pour chemin matieres.csv
* @param chemin_etudiants buffer pour chemin etudiants.csv
* @param chemin_notes buffer pour chemin notes.csv
* @param chemin_associations buffer pour chemin matiere_clas_asso.csv
*/
void generer_chemins_csv(const char *base, char *chemin_classes, char *chemin_matieres, char *chemin_etudiants, char *chemin_notes, char *chemin_associations);
/*
* @brief initialise une session (chemins + fichiers)
* @param base chemin du dossier de session
* @param chemin_classes buffer pour chemin classes.csv
* @param chemin_matieres buffer pour chemin matieres.csv
* @param chemin_etudiants buffer pour chemin etudiants.csv
* @param chemin_notes buffer pour chemin notes.csv
* @param chemin_associations buffer pour chemin matiere_clas_asso.csv
*/
void initialiser_session(const char *base, char *chemin_classes, char *chemin_matieres, char *chemin_etudiants, char *chemin_notes, char *chemin_associations);

#endif // !INIT_H
