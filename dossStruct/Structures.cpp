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
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>
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
void createTop10(const AssociationURLHits& uneAsso,array<pair<URL,int>,10>& top10)
//remplie un tableau de 10 cases avec de association URL hits en les triants au passage
//si l'élément à insérer est plus petit que le dernier élément il n'est pas inclus
//algorithme: à chaque élément du dictionnaire: si l'élément est plus grand que le dernier élément du tableau, on commence l'insertion
//ensuite on parcours le tableau à l'envers: si l'élément est plus grand que l'élément suivant, on swap les 2 et on augmente d'un cran l'itérateur
//                                           sinon on s'arrete
  
{
  AssociationURLHits::const_iterator itAsso;
  array<pair<URL,int>,10>::reverse_iterator rit;
  bool insere;  
  top10.fill(make_pair(string(),0));

  for(itAsso=uneAsso.cbegin();itAsso!=uneAsso.cend();itAsso++)
    {
      insere=false;
      rit=top10.rbegin();
      if(itAsso->second>rit->second)
      	{
      	  *rit=*itAsso;
      	  while( (rit+1)<top10.rend() && !insere )
      	    {
      	      if(rit->second>(rit+1)->second)
            		{
            		  swap(*rit,*(rit+1));
            		  rit++;
            		}
            	else
            		{
            		  insere=true;
            		}
	          }//while
	  
	       }//if
      
    }//for
  
}//createTop10


void AfficherTop10(const AssociationURLHits& uneAsso)
//on crée d'abord le top 10 puis on l'affiche
{
  array<pair<URL,int>,10> top10;
  array<pair<URL,int>,10>::const_iterator it;
  createTop10(uneAsso,top10);
  for(it=top10.cbegin();it!=top10.cend();it++)
    {
      if(!(it->first).empty())
      {
	      cout<<it->first<<" ("<<it->second<<"hits)"<<endl;
      }
    }
}
  
ostream& operator<<(ostream& os, const AssociationURLHits& uneAsso)
{
  AssociationURLHits::const_iterator it;
  for(it=uneAsso.cbegin();it!=uneAsso.cend();it++)
    {
      os<<"URL :"<<it->first<<"\t hits:"<<it->second<<endl;
    }
  return os;
}



  

  

void AjouterDansAssociation(const Requete & uneRequete, AssociationURLHits & uneAssociation)
// Algorithme : Recherche l'URL geté de la requête dans le dictionnaire
//             si il n'y a pas de correspondance, l'URL est ajouté au dictionnaire et le hit qu'elle identifie est initialisé a 1
//             si il y a une correspondance, on incrémente le hit (le fait d'avoir deux fois le même site  
//
{
  URL URLGet(uneRequete.GetURLCible());//getURL a changer au besoins(elle n'est pas trop utilisée donc ça devrait aller)
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
  URL URLSrc(uneRequete.GetURLSrc());//pareil vous changez au besoins
  
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

