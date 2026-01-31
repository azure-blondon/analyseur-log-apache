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

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

Configuration findConfig(int argc, const char *argv[])
{

    Configuration config;


    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (strcmp(arg, "-e") == 0) {
            config.exclureExtensions = true;
            continue;
        }
        if (strcmp(arg, "-t") == 0) {
            i++;
            istringstream tmp(argv[i]);
            config.creneauHoraire = Configuration::lire<int>(tmp);
            continue;
        }
        if (strcmp(arg, "-g") == 0) {
            i++;
            istringstream tmp(argv[i]);
            config.fichierGraphe = Configuration::lire<string>(tmp);
            continue;
        }
        if (strcmp(arg, "-c") == 0) {
            i++;
            istringstream tmp(argv[i]);
            config.fichierConfig = Configuration::lire<string>(tmp);
            continue;
        }
        config.fichierSource = argv[i];
    }

    Configuration configFichier(config.fichierConfig.value_or("config"));
    config.Charger(configFichier, false);

    cout << "config fichier :" << endl;
    cout << configFichier << endl << endl;

    cout << "config finale :" << endl;
    cout << config << endl;

    return config;
}



int main(int argc, const char *argv[])
{
    // Arguments : [options] nom_fichier
    // Options   : -t heure:int
    //             -g fichier:string
    //             -e
    Configuration config = findConfig(argc, argv);



    ifstream fichier(config.fichierSource.value_or(""));

    if (!fichier) {
        return 1;
    }

    Requete requeteCourante;



    while (fichier >> requeteCourante) {
        //cout << requeteCourante.AdresseIP << endl;
    }


    return 0;
} //----- fin de Nom

