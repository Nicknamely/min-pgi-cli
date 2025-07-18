#include "csv_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonctions de chargement CSV
// Lecture ligne par ligne, decoupage, ajout dans la base

int charger_matieres_csv(const char *chemin, MatiereDB *db) {
  FILE *f = fopen(chemin, "r");
  if (!f) {
    // Fichier absent
    return -1;
  }
  char ligne[256];
  while (fgets(ligne, sizeof(ligne), f)) {
    Matiere m;
    char *token = strtok(ligne, ",");
    if (!token)
      continue;
    m.reference = atoi(token);

    token = strtok(NULL, ",");
    if (!token)
      continue;
    strncpy(m.libelle, token, sizeof(m.libelle));
    m.libelle[sizeof(m.libelle) - 1] = 0;

    token = strtok(NULL, ",");
    if (!token)
      continue;
    m.coeficient = atoi(token);

    ajouter_matiere(db, m);
  }
  fclose(f);
  return 0;
}

int charger_classes_csv(const char *chemin, ClasseDB *db) {
  FILE *f = fopen(chemin, "r");
  if (!f) {
    // Fichier absent
    return -1;
  }
  char ligne[256];
  while (fgets(ligne, sizeof(ligne), f)) {
    Classe c;
    char *token = strtok(ligne, ",");
    if (!token)
      continue;
    c.code = atoi(token);
    token = strtok(NULL, ",");
    if (!token)
      continue;
    strncpy(c.nom, token, sizeof(c.nom));
    c.nom[sizeof(c.nom) - 1] = 0;
    token = strtok(NULL, ",");
    if (!token)
      continue;
    c.niveau = strcmp(token, "LICENSE") == 0 ? LICENSE : MASTER;
    ajouter_classe(db, c);
  }
  fclose(f);
  return 0;
}

int charger_etudiants_csv(const char *chemin, EtudiantDB *db) {
  FILE *f = fopen(chemin, "r");
  if (!f) return -1;
  char ligne[128];
  fgets(ligne, sizeof(ligne), f); // ignore l'en-tête
  db->taille = 0;
  while (fgets(ligne, sizeof(ligne), f)) {
    Etudiant e;
    char date[20];
    sscanf(ligne, "%d,%29[^,],%19[^,],%19[^,],%19[^,],%d/%d/%d,%d",
           &e.numero, e.nom, e.prenom, e.email, date,
           &e.date_naissance.jour, &e.date_naissance.mois, &e.date_naissance.annee, &e.classe_code);
    db->etudiants[db->taille++] = e;
  }
  fclose(f);
  return 0;
}

int charger_notes_csv(const char *chemin, NoteDB *db,
                      const EtudiantDB *etudiantDB,
                      const MatiereDB *matiereDB) {
  FILE *f = fopen(chemin, "r");
  if (!f) {
    // Fichier absent
    return -1;
  }
  char ligne[256];
  while (fgets(ligne, sizeof(ligne), f)) {
    Note n;
    char *token = strtok(ligne, ",");
    if (!token)
      continue;
    n.numero_etudiant = atoi(token);
    token = strtok(NULL, ",");
    if (!token)
      continue;
    n.reference_matiere = atoi(token);
    token = strtok(NULL, ",");
    if (!token)
      continue;
    n.noteCC = atof(token);
    token = strtok(NULL, ",");
    if (!token)
      continue;
    n.noteDS = atof(token);
    ajouter_note(db, n, etudiantDB, matiereDB);
  }
  fclose(f);
  return 0;
}

// Fonctions d'export CSV
// Ecriture complete du fichier a chaque appel

int exporter_classes_csv(const char *chemin, const ClasseDB *db) {
  FILE *f = fopen(chemin, "w");
  if (!f) {
    printf("Erreur ouverture %s pour ecrire les classes\n", chemin);
    return -1;
  }
  fprintf(f, "code,nom,niveau\n");
  for (int i = 0; i < db->taille; i++) {
    fprintf(f, "%d,%s,%s\n", db->classes[i].code, db->classes[i].nom,
            db->classes[i].niveau == LICENSE ? "LICENSE" : "MASTER");
  }
  fclose(f);
  return 0;
}

int exporter_matieres_csv(const char *chemin, const MatiereDB *db) {
  FILE *f = fopen(chemin, "w");
  if (!f) {
    printf("Erreur ouverture %s pour ecrire les matieres\n", chemin);
    return -1;
  }
  fprintf(f, "reference,libelle,coefficient\n");
  for (int i = 0; i < db->taille; i++) {
    fprintf(f, "%d,%s,%d\n", db->matieres[i].reference, db->matieres[i].libelle,
            db->matieres[i].coeficient);
  }
  fclose(f);
  return 0;
}

int exporter_etudiants_csv(const char *chemin, const EtudiantDB *db) {
  FILE *f = fopen(chemin, "w");
  if (!f) {
    printf("Erreur ouverture %s pour ecrire les etudiants\n", chemin);
    return -1;
  }
  fprintf(f, "numero,nom,prenom,email,jour,mois,annee,classe_code\n");
  for (int i = 0; i < db->taille; i++) {
    Etudiant *e = &db->etudiants[i];
    fprintf(f, "%d,%s,%s,%s,%d,%d,%d,%d\n", e->numero, e->nom, e->prenom, e->email,
            e->date_naissance.jour, e->date_naissance.mois,
            e->date_naissance.annee, e->classe_code);
  }
  fclose(f);
  return 0;
}

int exporter_notes_csv(const char *chemin, const NoteDB *db) {
  FILE *f = fopen(chemin, "w");
  if (!f) {
    printf("Erreur ouverture %s pour ecrire les notes\n", chemin);
    return -1;
  }
  fprintf(f, "numero_etudiant,reference_matiere,noteCC,noteDS\n");
  for (int i = 0; i < db->taille; i++) {
    Note *n = &db->notes[i];
    fprintf(f, "%d,%d,%.2f,%.2f\n", n->numero_etudiant, n->reference_matiere,
            n->noteCC, n->noteDS);
  }
  fclose(f);
  return 0;
}

// TODO: Gestions des erreurs de format CSV

