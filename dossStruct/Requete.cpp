/*************************************************************************
                           Requete  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Requete> (fichier Requete.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
//------------------------------------------------------ Include personnel
#include "Requete.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Requete::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
string Requete::GetURLSrc()const{
  return URLSrc;
}
string Requete::GetURLCible()const{
  return URLCible;
}




//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


Requete::Requete ( const string& uneURLSrc, const string& uneURLCible):URLSrc(uneURLSrc),URLCible(uneURLCible)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Requete>" << endl;
#endif
} //----- Fin de Requete


Requete::~Requete ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Requete>" << endl;
#endif
} //----- Fin de ~Requete



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//autres
Requete getFromLine(const string& ligne)
{
  string::size_type pos;
  string urlGet;
  string urlSource;
  //Requete req;//je sais  c'est pas efficace
  pos=ligne.find('"');
  pos=ligne.find('/',pos);
  //pos=pos+2;
  urlGet=ligne.substr(pos,ligne.find(' ',pos)-pos);
  pos=ligne.find('"',pos);
  pos=ligne.find('"',pos);
  
  pos=ligne.find('/',pos)+2;
  pos=ligne.find('/',pos);
  urlSource=ligne.substr(pos,ligne.find('"',pos)-pos);
  
  return Requete(urlSource,urlGet);
} 
  
ostream& operator<<(ostream& os, const Requete& req)
{
  os<<"URL source: "<<req.URLSrc<<"\tURL cible: "<<req.URLCible<<endl;
  return os;
}
