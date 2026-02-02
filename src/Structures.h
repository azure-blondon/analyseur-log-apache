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
#include <iostream>
#include <unordered_map>
#include <string>
#include <array>

#include "Requete.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

typedef std::string URL;

typedef std::unordered_map<URL, int> AssociationURLHits;
typedef std::unordered_map<URL, AssociationURLHits> DicoGraphe;

void createTop10(const AssociationURLHits& uneAsso,std::array<std::pair<int,URL>,10>& top10);
//remplie un tableau de dix avec les dix plus grand élément de l'association
//le tableau est évidemment trié

void AfficherTop10(const AssociationURLHits& uneAsso);
//affiche de manière trié (plus haut en haut) les 10 élément avec le plus de hits de l'association sous la forme "URL  (nhits hits)
  
void AjouterDansAssociation(const Requete & uneRequete, AssociationURLHits & uneAssociation);
//ajoute la cible de la requete dans l'association avec un hit de 1.
//le deuxième élément correspond à l'hit de l'url, le nombre de fois où l'url est ajouté dans l'association


void AjouterDansDicoGraphe(const Requete & uneRequete, DicoGraphe &unDicoGraphe);
//ajoute une requete dans un graphe.

std::ostream& operator<<(std::ostream& os,const AssociationURLHits& uneAsso);
//un affichage pour les tests vous enlever si vous voulez


#endif // Structures_H


