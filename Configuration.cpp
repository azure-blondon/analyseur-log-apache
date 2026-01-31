/*************************************************************************
                           Configuration  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
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
        this->exclureExtensions = (valeur == "true");
        return;
    } 
    
    if (strcmp(cstr, "creneau_horaire") == 0) {
        istringstream tmp(valeur);
        this->creneauHoraire = Configuration::lire<int>(tmp);
        return;
    }   
}
void Configuration::Charger(const Configuration & uneConfiguration, bool remplacer)
{

    if (!remplacer && !this->fichierSource.has_value()) this->fichierSource = uneConfiguration.fichierSource;
    if (!remplacer && !this->fichierConfig.has_value()) this->fichierConfig = uneConfiguration.fichierConfig;
    if (!remplacer && !this->fichierGraphe.has_value()) this->fichierGraphe = uneConfiguration.fichierGraphe;
    if (!remplacer && !this->creneauHoraire.has_value()) this->creneauHoraire = uneConfiguration.creneauHoraire;
    if (!remplacer && !this->exclureExtensions.has_value()) this->exclureExtensions = uneConfiguration.exclureExtensions;
}




//------------------------------------------------- Surcharge d'opérateurs
Configuration & Configuration::operator = ( const Configuration & uneConfiguration )
// Algorithme :
//
{
    this->fichierSource = uneConfiguration.fichierSource;
    this->fichierConfig = uneConfiguration.fichierConfig;
    this->fichierGraphe = uneConfiguration.fichierGraphe;
    this->creneauHoraire = uneConfiguration.creneauHoraire;
    this->exclureExtensions = uneConfiguration.exclureExtensions;
    
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Configuration::Configuration(const Configuration & uneConfiguration)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Configuration>" << endl;
#endif
    this->fichierSource = uneConfiguration.fichierSource;
    this->fichierConfig = uneConfiguration.fichierConfig;
    this->fichierGraphe = uneConfiguration.fichierGraphe;
    this->creneauHoraire = uneConfiguration.creneauHoraire;
    this->exclureExtensions = uneConfiguration.exclureExtensions;
} //----- Fin de Configuration (constructeur de copie)


Configuration::Configuration(string nomFichierConfig)
:fichierSource(), fichierConfig(nomFichierConfig), creneauHoraire(), fichierGraphe(), exclureExtensions(false)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Configuration>" << endl;
#endif
    ifstream fichier(this->fichierConfig.value_or(""));
    
    if (!fichier) {
        return;
    }

    string line;
    while(getline(fichier, line)) {
        if  (line.find(':') == string::npos || line[0] == '#') {
            continue;
        }
        istringstream s(line);
        string clef, valeur;
        getline(s, clef, ':'); getline(s,valeur);
        trim(clef); trim(valeur);
        this->MettreAJour(clef, valeur);
    }
    
} //----- Fin de Configuration


Configuration::Configuration()
:fichierSource(), fichierConfig(), creneauHoraire(), fichierGraphe(), exclureExtensions(false)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Configuration>" << endl;
#endif
} //----- Fin de Configuration



Configuration::~Configuration()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Configuration>" << endl;
#endif
} //----- Fin de ~Configuration


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
