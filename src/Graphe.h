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

std::ostream & GenererGraphe(std::ostream & flux, DicoGraphe unDicoGraphe);
std::unordered_map<std::string, int> GenererTableIndex(const DicoGraphe & unDicoGraphe);
std::ostream & GenererNode(std::ostream & flux, std::string uneNode, int index);
std::ostream & GenererAretes(std::ostream & flux, std::string unReferenceur, const AssociationURLHits & uneAssociation, const std::unordered_map<std::string, int> & tableIndex);



#endif // Graphe_H

