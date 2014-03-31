#include <iostream>
#include <fstream>


//include from porject
#include "angoloS.h"
#include "MisuraAngolo.h"


//Include from root

#include "TGraphErrors.h"
#include "TFile.h"
#include <TF1.h>
#include <string>
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
  TF1 * Line_prot=new TF1("prot","pol2");
  TF1 * Line;
  
  
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
  
  for (unsigned int n=2; n<argc; ++n){
   
    //apro il file su cui lavoro
    dataIn.open( argv[ n ] );
    cout << "Inizio Analisi del file " << argv [ n ] << '.' << endl;
    
    //Preparo gli oggetti che mi servono
    Plot=new TGraphErrors();
    numPoint=0;
    
    //Do il nome alle cose
    //plot
    string PlotName=argv[ n ];
    PlotName.substr( 0, PlotName.find('.') );
    Plot->SetNameTitle(PlotName.c_str(), PlotName.c_str() );
    Plot->SetPointError( numPoint++, Errore.GetRad()/sqrt(3.), Errore.GetRad()*(sqrt ( 2./3.) ) );
    //Curva
    string LineName="pol_";
    LineName=LineName+PlotName;
    Line=new TF1(LineName.c_str(), "pol2");
   
    
    //Leggo il primo dato
    thetaZero = ReadMisuraP(dataIn);
    alfaZero  = ReadMisuraP(dataIn);
    
    
    // analizzo il primo dato
    dAlfaPunto= &(*alfaZero - *thetaZero);
    
    // Lo inseriso nel TGraphErrors
    Plot->SetPoint( numPoint++, 0, -( dAlfaPunto->GetRad() ) );

    //analizzo gli altri considerando la prima misura come zero
    while ( ( thetaMisura=ReadMisuraP(dataIn) ) != 0 ){
      
      thetaPunto = &(*thetaMisura - *thetaZero );
      alfaMisura=ReadMisuraP(dataIn);
      dAlfaPunto= &(*alfaMisura - *thetaMisura);

      Plot->SetPoint( numPoint++, thetaPunto->GetRad(), -dAlfaPunto->GetRad() );
    }
   
   
    Plot->Fit(Line);
    
    //Salvo le cose root in argv[ 1 ].root
    Line->Write();
    Plot->Write();

   cout << "Fine dell'analisi.\n\n"<<endl;
   //pulizia di ciclo
   dataIn.close();
   delete Plot;
   delete Line;
  }
 
  //pulizia finale
  delete thetaMisura;
  delete alfaMisura;
  delete dAlfaPunto;
  delete thetaPunto;
  delete Plot;
  fileRoot->Close();
  delete fileRoot;
  current->cd();
  dataIn.close();

  return 0;
}



