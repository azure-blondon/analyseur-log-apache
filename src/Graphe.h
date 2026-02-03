/*************************************************************************
                                  Graphe 
                                    -
              Fonctions permettant la generation du graphe (.dot)
                             -------------------
    début                : 13/01/26
    copyright            : (C) 2026 par Mégane DEBUREAUX
    e-mail               : megane.debureaux@insa-lyon.fr
*************************************************************************/

//---------- Interface du module <Graphe> (fichier Graphe.h) -------------------
#if ! defined ( Graphe_H )
#define Graphe_H

//------------------------------------------------------------------------
// Rôle du module <Graphe>
// Ce module est destiné à la génération de graphe (.dot) a partir
// d'un dictionnaire spécialisé
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

