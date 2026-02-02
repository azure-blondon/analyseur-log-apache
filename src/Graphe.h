/*************************************************************************
                           Graphe  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface du module <Graphe> (fichier Graphe.h) -------------------
#if ! defined ( Graphe_H )
#define Graphe_H

//------------------------------------------------------------------------
// Rôle du module <Graphe>
//
//
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées
#include <ostream>
#include <unordered_map>
#include "Structures.h"


//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
// type Nom ( liste de paramètres );
// Mode d'emploi :
//
// Contrat :
//


std::ostream & GenererGraphe(std::ostream & flux, DicoGraphe unDicoGraphe);
std::unordered_map<string, int> GenererTableIndex(const DicoGraphe & unDicoGraphe);
std::ostream & GenererNode(std::ostream & flux, std::string uneNode, int index);
std::ostream & GenererAretes(std::ostream & flux, std::string unReferenceur, const AssociationURLHits & uneAssociation, const unordered_map<string, int> & tableIndex);



#endif // Graphe_H

