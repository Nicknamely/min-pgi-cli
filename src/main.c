#include "./classe/classe.h"
#include "./etudiant/etudiant.h"
#include "./matiere/matiere.h"
#include "./note/note.h"
/* #include <stdio.h> */
#include <stdlib.h>
#include <stdio.h>

int main() {
    ClasseDB db;
    initialiser_ClasseDB(&db, 2);

    Classe c1 = {1, "L1 Info", LICENSE};
    Classe c2 = {2, "L2 Info", LICENSE};
    Classe c3 = {3, "M1 Info", MASTER};

    printf("Ajout des classes...\n");
    ajouter_classe(&db, c1);
    ajouter_classe(&db, c2);
    ajouter_classe(&db, c3);

    printf("\nAffichage des classes :\n");
    afficher_classes(&db);

    printf("\nSuppression de la classe à l'index 1...\n");
    supprimer_classe(&db, 1);
    afficher_classes(&db);

    printf("\nModification de la classe à l'index 0...\n");
    Classe c_modif = {10, "L1 Modifiée", LICENSE};
    modifier_classe(&db, 0, c_modif);
    afficher_classes(&db);

    printf("\nRecherche de la classe avec code 3...\n");
    int idx = rechercher_classe(&db, 3);
    if (idx != -1) {
        printf("Classe trouvée à l'index %d : %s\n", idx, db.classes[idx].nom);
    } else {
        printf("Classe non trouvée.\n");
    }

    freeClasseDB(&db);
    return 0;
}
