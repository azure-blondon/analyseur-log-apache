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
#include <fstream>
#include <iostream>
using namespace std;

#include "Configuration.h"
#include "Requete.h"
#include "Structures.h"
#include "Graphe.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques
static const string extensions_image_array[] = {"gif", "png", "jpg", "jpeg", "ico"};
static const vector<string> extensions_image_vector = vector<string>(extensions_image_array, extensions_image_array + sizeof(extensions_image_array) / sizeof(char *));
//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques




int main(int argc, const char *argv[])
{
    // Arguments : [options] nom_fichier
    // Options   : -t heure:int
    //             -g fichier:string
    //             -c fichier:string
    //             -e
    Configuration config = Configuration::TrouverConfig(argc, argv);
    ifstream fichier(config.fichierSource.value_or(""));
    if (!fichier) return 1;

    AssociationURLHits top10;
    DicoGraphe graphe;
    
    Requete requeteCourante;
    while (fichier >> requeteCourante) {
        if (config.exclureExtensions.value_or(false) && !requeteCourante.ExtensionDifferenteDe(extensions_image_vector)) continue;
        if ((config.creneauHoraire.value_or(-1) != -1) && !requeteCourante.EstDansLeCreneauHoraire(config.creneauHoraire.value_or(0))) continue;

        AjouterDansAssociation(requeteCourante, top10);
        if (config.fichierGraphe) {
            AjouterDansDicoGraphe(requeteCourante, graphe);
        }
    }

    AfficherTop10(top10);
    
    if (config.fichierGraphe) {
        ofstream fichier_graphe(config.fichierGraphe.value_or(""));
        if (!fichier_graphe) return 1;
        GenererGraphe(fichier_graphe, graphe);
        cout << config.fichierGraphe.value_or("") << " généré !" << endl;
    }
    
    return 0;
} //----- fin de Nom

