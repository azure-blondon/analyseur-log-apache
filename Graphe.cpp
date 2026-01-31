/*************************************************************************
                                  Graphe 
                                    -
              Fonctions permettant la generation du graphe (.dot)
                             -------------------
    début                : 13/01/26
    copyright            : (C) 2026 par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//-------- Réalisation du module <Graphe> (fichier Graphe.cpp) -----------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Structures.h"
#include "Graphe.h"
#include <ostream>
#include <unordered_map>


///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
std::ostream & GenererGraphe(std::ostream & flux, DicoGraphe unDicoGraphe)
  /*
    Algorithme :
      On genere la table d'index correspondant au DicoGraphe
      On genere toutes les lignes pour initialiser les noeuds
      On genere ensuite les aretes
      Et on termine le fichier
  */

  {
    std::unordered_map<string, int> tableIndex;
    tableIndex = GenererTableIndex(unDicoGraphe);

    flux << "digraph {" << endl;

    // Premier parcours du graphe : generation des noeuds
    DicoGraphe::const_iterator debut, fin;
    debut = unDicoGraphe.begin();
    fin = unDicoGraphe.end();

    while(debut != fin)
    {
      GenererNode(flux, debut->first, tableIndex.at(debut->first));
      debut++;
    }
    
    // Premier parcours du graphe : generation des aretes
    debut = unDicoGraphe.begin();

    while(debut != fin)
    {
      GenererAretes(flux, debut->first, debut->second, tableIndex);
      debut++;
    }

    flux << "}" << endl;

    return flux;
  }



std::unordered_map<string, int> GenererTableIndex(const DicoGraphe & unDicoGraphe)
  //Algorithme
  // Cree une map tableIndex
  // Parcourt la map unDicoGraphe, avec un compteur en parallele, et stocke dans tableIndex
  // des couples URL / indice (avec indice un entier distinct pour chaque URL)
  {
    // Creation de la map
    std::unordered_map<std::string, int> tableIndex;

    // Declaration et definition des iterateurs, et d'indice_url
    DicoGraphe::const_iterator debut, fin;
    debut = unDicoGraphe.begin();
    fin = unDicoGraphe.end();
    int indice_url = 0;

    // Parcours de la map (graphe) et remplissage de la map (table indices)
    while(debut != fin)
    {
      tableIndex.insert(make_pair(debut->first, indice_url));
      indice_url++;
      debut++;
    }

    return tableIndex;
  }




std::ostream & GenererNode(std::ostream & flux, std::string uneNode, int index)
  {
    return flux << "node" << index << " [label=\"" << uneNode << "\"];" << endl;
  }




std::ostream & GenererAretes(std::ostream & flux, std::string unReferenceur, const AssociationURLHits & uneAssociation, const std::unordered_map<string, int> & tableIndex)
  /*
    Algorithme :
      On recupere les infos du referenceur (indice)
      Definition des iterateurs
      On parcourt la map pour generer chaque arete partant du referenceur :
        On recupere les infos sur la cible (URL, indice, nbHits)
        On genere la ligne
  */
  {
    // Declaration des variables
    std::string uneCible;
    int nbHits;
    int indReferenceur = tableIndex.at(unReferenceur);
    int indCible;

    // Declaration et definition des iterateurs
    AssociationURLHits::const_iterator debut, fin;
    debut = uneAssociation.begin();
    fin = uneAssociation.end();

    // Parcours de la map et generation des lignes de graphe
    while(debut != fin)
    {
      uneCible = debut->first;
      indCible = tableIndex.at(uneCible);
      nbHits = debut->second;

      flux << "node" << indReferenceur << " -> node" << indCible << " [label=\"" << nbHits << "\"];" << endl;
      
      debut++;
    }

    return flux;
  }