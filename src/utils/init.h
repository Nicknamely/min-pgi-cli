#ifndef INIT_H
#define INIT_H

int creer_repertoire_session(char *nom_session, char *chemin_complet);
void creer_csv_session(const char *chemin_classes, const char *chemin_matieres,
                       const char *chemin_etudiants, const char *chemin_notes, const char *chemin_associations);

#endif // !INIT_H
