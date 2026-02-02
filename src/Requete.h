/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Requete> (fichier Requete.h) ----------------
#if ! defined ( Requete_H )
#define Requete_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <istream>
#include <vector>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
//
//
//------------------------------------------------------------------------
typedef std::string URL;

struct Requete
{
//----------------------------------------------------- Attributs
    std::string AdresseIP;
    std::string NomUtilisateurVisiteur;
    std::string NomUtilisateurDonne;
    std::string Instant;
    std::string TypeAction;
    URL URLCible;
    std::string Protocole;
    unsigned int CodeRetour;
    unsigned int TailleReponse;
    URL URLReferenceur;
    std::string Navigateur;
    


//----------------------------------------------------- Méthodes
    std::string SupprimerNomDeDomaine(const URL & uneURL) const;
    // Mode d'emploi :
    // Renvoie l'URL placée en paramètre sans le nom de domaine


    bool EstOK() const;
    // Mode d'emploi :
    // Vérifie que le code HTTP n'est pas une erreur


    bool EstDansLeCreneauHoraire(unsigned short unHoraire) const;
    // Mode d'emploi :
    // Vérifie si la requête est dans le créneau horaire placé en paramètres

    bool ExtensionDifferenteDe(std::vector<std::string> extensions) const;
    //------------------------------------------------- Surcharge d'opérateurs
    
    Requete & operator = (const Requete & unRequete);
    
    friend std::ostream & operator << (std::ostream & flux, Requete & uneRequete);
    friend std::istream & operator >> (std::istream & flux, Requete & uneRequete);


//-------------------------------------------- Constructeurs - destructeur
    Requete(const Requete & uneRequete);

    Requete();

    virtual ~Requete();

};

//-------------------------------- Autres définitions dépendantes de <Requete>

std::istream & operator >> (std::istream & flux, Requete & uneRequete);

#endif // Requete_H

