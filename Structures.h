/*************************************************************************
                           Structures  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Structures> (fichier Structures.h) -------------------
#if ! defined ( Structures_H )
#define Structures_H

//------------------------------------------------------------------------
// Rôle du module <Structures>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <unordered_map>
#include <string>
#include  "Requete.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//

typedef string URL;

typedef std::unordered_map<URL, int> AssociationURLHits;
typedef std::unordered_map<URL, AssociationURLHits> DicoGraphe;


void AjouterDansAssociation(const Requete & uneRequete, AssociationURLHits & uneAssociation);

void AjouterDansDicoGraphe(const Requete & uneRequete, DicoGraphe &unDicoGraphe);




#endif // Structures_H

