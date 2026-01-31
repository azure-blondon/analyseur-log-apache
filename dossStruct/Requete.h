/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Requete> (fichier Requete.h) ----------------
#if ! defined ( REQUETE_H )
#define REQUETE_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <iostream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
//
//
//------------------------------------------------------------------------

class Requete
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
  std::string GetURLSrc()const;
  std::string GetURLCible()const;

  friend std::ostream& operator<<(std::ostream& os, const Requete& req);


//------------------------------------------------- Surcharge d'opérateurs
    
//-------------------------------------------- Constructeurs - destructeur
  Requete ( const std::string& uneURLSrc="",const std::string& uneURLCible="");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Requete ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  std::string URLSrc;
  std::string URLCible;
};

//-------------------------------- Autres définitions dépendantes de <Requete>
Requete getFromLine(const std::string& ligne);//prend une ligne au format décrit dans le tp et renvoie une requete
//comme pour l'intégralité de cette classe l'objectif est de tester le module Structures.h
//ce qui signifie que cette fonction ne doit pas être considéré comme la version finale (vous en faite ce que vous voulez).



#endif // REQUETE_H

