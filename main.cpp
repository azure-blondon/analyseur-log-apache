/*************************************************************************
                           main  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation du module <main> (fichier main.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

#include "Configuration.h"
#include "Requete.h"
#include "Structures.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static vector<string> extensions_image = vector<string>(["gif", "png", "jpg", "jpeg"]);
//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques




int main(int argc, const char *argv[])
{
    // Arguments : [options] nom_fichier
    // Options   : -t heure:int
    //             -g fichier:string
    //             -e
    //             -c fichier:string
    Configuration config = Configuration::TrouverConfig(argc, argv);



    ifstream fichier(config.fichierSource.value_or(""));

    if (!fichier) {
        return 1;
    }

    Requete requeteCourante;


    AssociationURLHits top10;

    while (fichier >> requeteCourante) {
        if (config.exclureExtensions && requeteCourante.ExtensionDifferenteDe(extensions_image)) {
            continue;
        }
        AjouterDansAssociation(requeteCourante, top10);
    }

    AfficherTop10(top10);

    return 0;
} //----- fin de Nom

