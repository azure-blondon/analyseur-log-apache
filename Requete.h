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

using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Requete>
//
//
//------------------------------------------------------------------------
typedef string URL;

struct Requete
{
//----------------------------------------------------- Attributs
    string AdresseIP;
    string NomUtilisateurVisiteur;
    string NomUtilisateurDonne;
    string Instant;
    string TypeAction;
    URL URLCible;
    string Protocole;
    unsigned int CodeRetour;
    unsigned int TailleReponse;
    URL URLReferenceur;
    string Navigateur;
    


//----------------------------------------------------- Méthodes
    string SupprimerNomDeDomaine(const URL & uneURL) const;
    // Mode d'emploi :
    // Renvoie l'URL placée en paramètre sans le nom de domaine


    bool EstOK() const;
    // Mode d'emploi :
    // Vérifie que le code HTTP n'est pas une erreur


    bool EstDansLeCreneauHoraire(unsigned short unHoraire) const;
    // Mode d'emploi :
    // Vérifie si la requête est dans le créneau horaire placé en paramètres

    bool ExtensionDifferenteDe(vector<string> extensions) const;
    // Mode d'emploi :
    // Renvoie faux si l'URLCible a une des extensions placées en paramètres, vrai sinon
    
    //------------------------------------------------- Surcharge d'opérateurs
    
    Requete & operator = ( const Requete & unRequete );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    friend ostream & operator<<(ostream & flux, Requete & uneRequete);
    friend istream & operator>>(istream & flux, Requete & uneRequete);


//-------------------------------------------- Constructeurs - destructeur
    Requete(const Requete & uneRequete);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Requete();
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Requete();
    // Mode d'emploi :
    //
    // Contrat :
    //
};

//-------------------------------- Autres définitions dépendantes de <Requete>

istream & operator>>(istream & flux, Requete & uneRequete);
// Mode d'emploi :
//
// Contrat :
//

#endif // Requete_H

