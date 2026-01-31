/*************************************************************************
                           Configuration  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Configuration> (fichier Configuration.h) ----------------
#if ! defined ( CONFIGURATION_H )
#define CONFIGURATION_H

//--------------------------------------------------- Interfaces utilisées
#include <optional>
#include <string>
#include <istream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Configuration>
//
//
//------------------------------------------------------------------------

struct Configuration
{
    std::optional<std::string> fichierSource;
    std::optional<std::string> fichierConfig;
    std::optional<std::string> fichierGraphe;
    std::optional<int> creneauHoraire;
    std::optional<bool> exclureExtensions;
//----------------------------------------------------- Méthodes publiques
    void MettreAJour(const std::string & clef, const std::string & valeur);
    void Charger(const Configuration &uneConfiguration, bool remplacer=true);

    
    template <typename T>
    static std::optional<T> lire(std::istream& flux)
    {
        T resultat;
        if (flux >> resultat) return resultat;
        else return {};
    }



//------------------------------------------------- Surcharge d'opérateurs
    Configuration & operator=(const Configuration & uneConfiguration);
    // Mode d'emploi :
    //
    // Contrat :
    //

    friend ostream & operator<<(ostream & flux, const Configuration & uneConfiguration);


//-------------------------------------------- Constructeurs - destructeur
    Configuration(const Configuration & unConfiguration);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Configuration(std::string nomFichierConfig);
    // Mode d'emploi :
    //
    // Contrat :
    //

    Configuration();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Configuration();
    // Mode d'emploi :
    //
    // Contrat :
    //

};

//-------------------------------- Autres définitions dépendantes de <Configuration>
inline ostream & operator<<(ostream & flux, const Configuration & uneConfiguration)
{
    flux << "fichier_source: " << uneConfiguration.fichierSource.value_or("{pas de fichier source}") << endl;
    flux << "fichier_graphe: " << uneConfiguration.fichierGraphe.value_or("{pas de fichier graphe}") << endl;
    flux << "fichier_config: " << uneConfiguration.fichierConfig.value_or("{pas de fichier config}") << endl;
    flux << "exclure_extensions: " << ((uneConfiguration.exclureExtensions.value_or(0)) ? "true" : "false") << endl;
    if (uneConfiguration.creneauHoraire.has_value()) {
        flux << "creneau_horaire: " << uneConfiguration.creneauHoraire.value_or(-1) << endl;
    } else {
        flux << "creneau_horaire: {pas de creneau horaire}" << endl;
    }
    
    return flux;
}



#endif // CONFIGURATION_H

