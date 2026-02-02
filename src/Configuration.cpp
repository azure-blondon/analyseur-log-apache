/*************************************************************************
                           Configuration  -  Une classe permettant de charger des fichiers de configuration
                             -------------------
    début                : 13/01/2026
    copyright            : (C) 2026 par Azure BLONDON
    e-mail               : azure.blondon@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Configuration> (fichier Configuration.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <optional>
using namespace boost::algorithm;
using namespace std;

//------------------------------------------------------ Include personnel
#include "Configuration.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Configuration::MettreAJour(const string & clef, const string & valeur)
{
    const char *cstr = clef.c_str();

    if (strcmp(cstr, "fichier_graphe") == 0) {
        this->fichierGraphe = valeur;
        return;
    }

    if (strcmp(cstr, "fichier_source") == 0) {
        this->fichierSource = valeur;
        return;
    }
    
    if (strcmp(cstr, "exclure_extensions") == 0) {
        this->exclureExtensions = (strcmp(valeur.c_str(), "true") == 0);
        return;
    } 
    
    if (strcmp(cstr, "creneau_horaire") == 0) {
        istringstream tmp(valeur);
        this->creneauHoraire = Configuration::Lire<int>(tmp);
        return;
    }   
} //----- Fin de MettreAJour

void Configuration::Charger(const Configuration & uneConfiguration, bool remplacer)
{
    if (!remplacer && !this->fichierSource.has_value())     this->fichierSource     = uneConfiguration.fichierSource;
    if (!remplacer && !this->fichierConfig.has_value())     this->fichierConfig     = uneConfiguration.fichierConfig;
    if (!remplacer && !this->fichierGraphe.has_value())     this->fichierGraphe     = uneConfiguration.fichierGraphe;
    if (!remplacer && !this->creneauHoraire.has_value())    this->creneauHoraire    = uneConfiguration.creneauHoraire;
    if (!remplacer && !this->exclureExtensions.has_value()) this->exclureExtensions = uneConfiguration.exclureExtensions;
} //----- Fin de Charger


//------------------------------------------------- Surcharge d'opérateurs
Configuration & Configuration::operator = (const Configuration & uneConfiguration)
{
    this->fichierSource     = uneConfiguration.fichierSource;
    this->fichierConfig     = uneConfiguration.fichierConfig;
    this->fichierGraphe     = uneConfiguration.fichierGraphe;
    this->creneauHoraire    = uneConfiguration.creneauHoraire;
    this->exclureExtensions = uneConfiguration.exclureExtensions;
    
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Configuration::Configuration(const Configuration & uneConfiguration)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Configuration>" << endl;
#endif
    this->fichierSource     = uneConfiguration.fichierSource;
    this->fichierConfig     = uneConfiguration.fichierConfig;
    this->fichierGraphe     = uneConfiguration.fichierGraphe;
    this->creneauHoraire    = uneConfiguration.creneauHoraire;
    this->exclureExtensions = uneConfiguration.exclureExtensions;
} //----- Fin de Configuration (constructeur de copie)


Configuration::Configuration(string nomFichierConfig)
:fichierSource(), fichierConfig(nomFichierConfig), creneauHoraire(), fichierGraphe(), exclureExtensions()
{
#ifdef MAP
    cout << "Appel au constructeur de <Configuration>" << endl;
#endif
    ifstream fichier(this->fichierConfig.value_or(""));
    
    if (!fichier) return;
    
    string ligne;
    while(getline(fichier, ligne)) {
        if (ligne.find(':') == string::npos || ligne[0] == '#') {
            continue;
        }
        istringstream flux_ligne(ligne);
        string clef, valeur;
        getline(flux_ligne, clef, ':'); getline(flux_ligne,valeur);
        trim(clef); trim(valeur);
        this->MettreAJour(clef, valeur);
    }
} //----- Fin de Configuration


Configuration::Configuration()
:fichierSource(), fichierConfig(), creneauHoraire(), fichierGraphe(), exclureExtensions()
{
#ifdef MAP
    cout << "Appel au constructeur de <Configuration>" << endl;
#endif
} //----- Fin de Configuration



Configuration::~Configuration()
{
#ifdef MAP
    cout << "Appel au destructeur de <Configuration>" << endl;
#endif
} //----- Fin de ~Configuration


Configuration Configuration::TrouverConfig(int argc, const char *argv[])
{
    Configuration config;

    for (int i = 1; i < argc; ++i) {
        const char *arg = argv[i];

        if (strcmp(arg, "-e") == 0) {
            config.exclureExtensions = true;
            continue;
        }

        if (strcmp(arg, "-t") == 0) {
            ++i;
            istringstream tmp(argv[i]);
            config.creneauHoraire = Configuration::Lire<int>(tmp);
            continue;
        }

        if (strcmp(arg, "-g") == 0) {
            ++i;
            istringstream tmp(argv[i]);
            config.fichierGraphe = Configuration::Lire<string>(tmp);
            continue;
        }

        if (strcmp(arg, "-c") == 0) {
            ++i;
            istringstream tmp(argv[i]);
            config.fichierConfig = Configuration::Lire<string>(tmp);
            continue;
        }

        // si l'argument n'est pas une option
        config.fichierSource = arg;
    }

    Configuration configFichier(config.fichierConfig.value_or("config"));
    config.Charger(configFichier, false);

    return config;
}

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
