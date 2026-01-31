/*************************************************************************
                           Structures  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <Structures> (fichier Structures.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Structures.h"
#include "Requete.h"
#include <algorithm>
#include <unordered_map>
#include <utility>//pour le make pair
#include <array>
using namespace std;
///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées
//static type nom ( liste de paramètres )
// Mode d'emploi :
//
// Contrat :
//
// Algorithme :
//
//{
//} //----- fin de nom

//////////////////////////////////////////////////////////////////  PUBLIC

//---------------------------------------------------- Fonctions publiques
void afficherTop10(AssociationURLHits & unDicoAsso)
{
  array<pair<int,URL>,10> top10;
  AssociationURLHits::const_iterator itDico;
  int taille=0;
  array<pair<int,URL>,10>::iterator itTop10;
  bool elemInsere;


  for(itDico=unDicoAsso.cbegin();itDico<unDicoAsso.cend();itDico++)
  {
    elemInsere=false;
    itTop10=top10.begin();
    while(itTop10<taille&&itTop10!=end&& (!elemInsere) )
    {
      //lienTop10Dico=unDicoAsso.find(top10[i]);
      if(itDico->second>itTop10->first){
        itDico->first,itDico);
        elemInsere=true;
        taille++;
      }
      else
      {
        itTop10++;
      }
    }

    if (itTop10==taille && taille<10)
    {
      top10[taille]=itDico->first;
      taille++;
    }
    
  }
  


}


void AjouterDansAssociation(const Requete & uneRequete, AssociationURLHits & uneAssociation)
// Algorithme : Recherche l'URL geté de la requête dans le dictionnaire
//             si il n'y a pas de correspondance, l'URL est ajouté au dictionnaire et le hit qu'elle identifie est initialisé a 1
//             si il y a une correspondance, on incrémente le hit (le fait d'avoir deux fois le même site
//
{
  URL URLGet(uneRequete.URLCible);
  AssociationURLHits::iterator pAsso;

  if(!URLGet.empty())
    {
      pAsso=uneAssociation.find(URLGet);
      if(pAsso==uneAssociation.end())
        {
          uneAssociation.insert(make_pair(URLGet,1));
        }
      else
        {
          pAsso->second+=1;
        }
    }
}


//typedef AssociationURLHits = unordered_map<URL, int>;
///typedef DicoGraphe = unordered_map<URL, AssociationURLHits>;
void AjouterDansDicoGraphe(const Requete & uneRequete, DicoGraphe &unDicoGraphe)
// Algorithme : recherche dans le graphe l'entrée correspondant à l'url qui fait la  requête
//               si il n'y a pas d'entrée correspondante, on en crée une en initialisant une AssociationURLHits
//               si il y a une entrée, on met a jour ses association (qui vont correspondre aux requete qui partent de la source)
//
{
  URL URLSrc(uneRequete.URLReferenceur);

  AssociationURLHits* DicoURLHits;
  DicoGraphe::iterator pAsso;
  if(!URLSrc.empty())
    {
      pAsso=unDicoGraphe.find(URLSrc);
      if(pAsso==unDicoGraphe.end())
        {
          DicoURLHits=new AssociationURLHits();
          AjouterDansAssociation(uneRequete,*DicoURLHits);

          unDicoGraphe.insert(make_pair(URLSrc,*DicoURLHits));
          delete DicoURLHits;//le new+delete permet de ne pas avoir à gérer l'instanciation dans le cas où le dicoHit est déjà présent dans le dicoGraphe
        }
      else
        {
          AjouterDansAssociation(uneRequete,pAsso->second);

        }
    }


}
