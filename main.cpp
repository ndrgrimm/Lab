#include <iostream>
#include <fstream>


//include from porject
#include "angoloS.h"
#include "MisuraAngolo.h"


//Include from root

#include "TGraphErrors.h"
#include "TFile.h"
#include <string>
#include <cmath>
#include <string.h>
using namespace std;




int main( int argc, char**argv ){
  
  //creo  il file per root
  string nameFileRoot 	= argv[1];
  nameFileRoot += ".root";
  string optFileroot = "RECREATE";
  TDirectory *current = gDirectory;
  TFile * fileRoot = new TFile( nameFileRoot.c_str(), optFileroot.c_str() );
  
  TGraphErrors * Plot;
  
  
  //dichiaro i puntatori per i cicli
  MisuraAngolo* thetaZero;
  MisuraAngolo* alfaZero;
  
  MisuraAngolo * thetaMisura;
  MisuraAngolo * alfaMisura;
  
  angoloS* thetaPunto;
  angoloS* dAlfaPunto;
  
  int gradi;
  int primi;
  double secondi;
  
  cout << "qual'è l'errore di lettura in gradi? (semi dispersione massima)"<<endl;
  cout << "Gradi: "<<endl;
  cin >> gradi;
  cout << "Primi: "<<endl;
  cin >> primi;
  cout << "Secondi: "<<endl;
  cin >> secondi;
  
  angoloS Errore(gradi,primi,secondi);
  
  ifstream dataIn;
  int numPoint;
  
  for (unsigned int n = 2; n < argc; ++n){
    
    //apro il file su cui lavoro
    dataIn.open( argv[ n ] );
    Plot=new TGraphErrors();
    
   
    string PlotName =argv[ n ];
    PlotName=PlotName.substr(0,PlotName.find('.'));
   
    Plot->SetNameTitle(PlotName.c_str() , PlotName.c_str() );
    thetaZero = ReadMisuraP(dataIn);
    alfaZero  = ReadMisuraP(dataIn);
    
    
    dAlfaPunto= &(*alfaZero - *thetaZero);
    numPoint=0;
    Plot->SetPoint( numPoint, 0, -dAlfaPunto->GetRad() );
    Plot->SetPointError( numPoint++, Errore.GetRad()/sqrt(3.), Errore.GetRad()*(sqrt ( 2./3.) ) );
    
    while ( ( thetaMisura=ReadMisuraP(dataIn) ) != 0 ){
      
      thetaPunto = &(*thetaMisura - *thetaZero );
      alfaMisura=ReadMisuraP(dataIn);
      dAlfaPunto= &(*alfaMisura - *thetaMisura);
      cout << numPoint << ' '<< thetaPunto << ' ' << dAlfaPunto <<endl;
      Plot->SetPoint( numPoint, thetaPunto->GetRad(), -dAlfaPunto->GetRad() );
      Plot->SetPointError( numPoint++, Errore.GetRad()/sqrt(3.), Errore.GetRad()*(sqrt ( 2./3.) ) );
      
    }
    
    Plot->Print();
    Plot->Write();
    delete Plot;
    dataIn.close();
    
  }
  fileRoot->Close();
  delete thetaMisura;
  delete alfaMisura;
  delete dAlfaPunto;
  delete thetaPunto; 
  
  delete fileRoot;
  current->cd();
  
  

  return 0;
}



