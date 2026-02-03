/*************************************************************************
                           Requete  -  Une classe qui représente des requetes http Apache
                             -------------------
    début                : 13/01/2026
    copyright            : (C) 2026 par Juliette DUPREZ
    e-mail               : juliette.duprez@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <Requete> (fichier Requete.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Requete.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


// In Requete.cpp (or a private static helper)
string Requete::SupprimerNomDeDomaine(const URL & uneURL) const
{
    if (uneURL.empty() || uneURL == "-")
    {
        return "";
    }
    size_t posSchema = uneURL.find("://");
    if (posSchema == string::npos)
    {
        if (!uneURL.empty() && uneURL[0] == '/')
        {
            return uneURL;
        }
        size_t premierSlash = uneURL.find('/');
        if (premierSlash == string::npos)
        {
            return "";
        }
        else 
        {
            return uneURL.substr(premierSlash);
        }
    }

    size_t apresSchema = posSchema + 3;
    size_t premierSlash = uneURL.find('/', apresSchema);
    if (premierSlash == string::npos)
    {
        return "/";
    }
    return uneURL.substr(premierSlash);
}
 //----- Fin de SupprimerNomDeDomaine


bool Requete::EstOK() const{
    return CodeRetour<310;
} //----- Fin de EstOK


bool Requete::EstDansLeCreneauHoraire(unsigned short unHoraire) const{
    int index_espace = Instant.find(":");
    string heure_str = Instant.substr(index_espace+1, 2);
    unsigned short heure_short = stoi(heure_str);
    return unHoraire == heure_short;
} //----- Fin de EstDansLeCreneauHoraire


bool Requete::ExtensionDifferenteDe(vector<string> extensions) const {
    for (auto i: extensions) {
      	if (URLCible.find("." + i) != string::npos){
            return false;
        }
    }
    return true;
} //----- Fin de ExtensionDifferenteDe


//------------------------------------------------- Surcharge d'opérateurs
Requete & Requete::operator = ( const Requete & uneRequete )
// Algorithme :
//
{
    AdresseIP=uneRequete.AdresseIP;
    NomUtilisateurVisiteur=uneRequete.NomUtilisateurVisiteur;
    NomUtilisateurDonne=uneRequete.NomUtilisateurDonne;
    Instant=uneRequete.Instant;
    TypeAction=uneRequete.TypeAction;
    URLCible=uneRequete.URLCible;
    Protocole=uneRequete.Protocole;
    CodeRetour=uneRequete.CodeRetour;
    TailleReponse=uneRequete.TailleReponse;
    URLReferenceur=uneRequete.URLReferenceur;
    Navigateur=uneRequete.Navigateur;
    
    return *this;
} //----- Fin de operator =




//-------------------------------------------- Constructeurs - destructeur
Requete::Requete ( const Requete & uneRequete )
: AdresseIP(uneRequete.AdresseIP),
  NomUtilisateurVisiteur(uneRequete.NomUtilisateurVisiteur),
  NomUtilisateurDonne(uneRequete.NomUtilisateurDonne),
  Instant(uneRequete.Instant),
  TypeAction(uneRequete.TypeAction),
  URLCible(uneRequete.URLCible),
  Protocole(uneRequete.Protocole),
  CodeRetour(uneRequete.CodeRetour),
  TailleReponse(uneRequete.TailleReponse),
  URLReferenceur(uneRequete.URLReferenceur),
  Navigateur(uneRequete.Navigateur)
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Requete>" << endl;
#endif
} //----- Fin de Requete (constructeur de copie)


Requete::Requete ()
: AdresseIP(""),
  NomUtilisateurVisiteur(""),
  NomUtilisateurDonne(""),
  Instant(""),
  TypeAction(""),
  URLCible(""),
  Protocole(""),
  CodeRetour(0),
  TailleReponse(0),
  URLReferenceur(""),
  Navigateur("")
{
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete


Requete::~Requete ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Requete>" << endl;
#endif
} //----- Fin de ~Requete


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

istream & operator>>(istream & flux, Requete & uneRequete){

    char crochetOuvrant, crochetFermant;
    char guillemet;
    char espace;
    string codeRetour, tailleReponse, ligneHTML;

    flux >> uneRequete.AdresseIP;
    flux >> uneRequete.NomUtilisateurVisiteur;
    flux >> uneRequete.NomUtilisateurDonne;
    flux >> crochetOuvrant;
    getline(flux, uneRequete.Instant, ']');

    // Test de fin de fichier, apres les premieres lectures pour confirmer qu on est a la fin
    if (flux.eof())
    {
        return flux;
    }

    // Traitement de la partie entre guillemets
    flux >> guillemet;
    getline(flux, ligneHTML, '"');

    // Vider les champs avant de les remplir
    uneRequete.TypeAction = "";
    uneRequete.URLCible = "";
    uneRequete.Protocole = "";

    string::iterator it = ligneHTML.begin();
    string::iterator fin = ligneHTML.end();

    // Lire TypeAction jusqu'au premier espace
    while(it != fin && *it != ' ')
    {
        uneRequete.TypeAction += *it;
        it++;
    }

    if(it != fin && *it == ' ') // Espace
    {
        it++;
    }

    string::iterator dernierEspace = fin;
    if (fin != ligneHTML.begin())
    {
        dernierEspace = fin - 1;
        while(dernierEspace > it && *dernierEspace != ' ')
        {
            dernierEspace--;
        }
    }

    while(it < dernierEspace && it != fin)
    {
        uneRequete.URLCible += *it;
        it++;
    }

    if(it != fin && *it == ' ') // Espace
    {
        it++;
    }

    while(it != fin)
    {
        uneRequete.Protocole += *it;
        it++;
    }
    
    // Gestion du cas ou CodeRetour est un tiret :
    flux >> codeRetour;
    if (codeRetour == "-")
    {
        uneRequete.CodeRetour = 0;
    }
    else
    {
        uneRequete.CodeRetour = stoul(codeRetour);
    }
    
    // Gestion du cas ou TailleReponse est un tiret :
    flux >> tailleReponse;
    if (tailleReponse == "-")
    {
        uneRequete.TailleReponse = 0;
    }
    else
    {
        uneRequete.TailleReponse = stoul(tailleReponse);
    }

    flux >> guillemet;
    getline(flux, uneRequete.URLReferenceur, '"');
    flux >> guillemet;
    getline(flux, uneRequete.Navigateur, '"');

    return flux;
}

ostream & operator<<(ostream & flux, Requete & uneRequete)
// Algorithme :
//
{

    flux << uneRequete.AdresseIP << " ";
    flux << uneRequete.NomUtilisateurVisiteur << " ";
    flux << uneRequete.NomUtilisateurDonne << " ";
    flux << "[";
    flux << uneRequete.Instant << "]" << " ";
    flux << '"';
    flux << uneRequete.TypeAction << " ";
    flux << uneRequete.URLCible << " ";
    flux << uneRequete.Protocole;
    flux << '"' << " ";
    flux << uneRequete.CodeRetour << " ";
    flux << uneRequete.TailleReponse << " ";
    flux << '"';
    flux << uneRequete.URLReferenceur << '"' << " ";
    flux << '"';
    flux << uneRequete.Navigateur << '"';
    
    return flux;
} //----- Fin de operator <<