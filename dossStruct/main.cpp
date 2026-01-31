#include <iostream>
#include <fstream>
#include "Requete.h"
#include "Structures.h"
using namespace std;
void testFinal()
{
  string nomFich;
  ifstream flux;
  AssociationURLHits dicoAsso;
  string req;
  cout<<"veuillez entrer un nom de fichier:";
  cin>>nomFich;
  flux.open(nomFich);
  if (flux.is_open())
  {
    getline(flux,req,'\n');
    while(flux.good())
  	{
	    AjouterDansAssociation(getFromLine(req),dicoAsso);
	    getline(flux,req,'\n');
	  }
      
    AfficherTop10(dicoAsso);
    flux.close();
  }
  else
    {
      cerr<<"erreur à l'ouverture du fichier"<<endl;
    }
   
}
void testRequete1()
{
  string nomFich;
  ifstream flux;
  Requete requete;
  string req;
  cout<<"veuillez entrer un nom de fichier:";
  cin>>nomFich;
  flux.open(nomFich);
  if (flux.is_open())
    {
      getline(flux,req,'\n');
      while(flux.good())
	    {
	      requete=getFromLine(req);
	      cout<<requete;
	      getline(flux,req,'\n');
	    }
      flux.close();
    }
  else
    {
      cerr<<"erreur à l'ouverture du fichier"<<endl;
    }
 
  
}

int main()
{
  testFinal();
  return 0;
}
      
  
