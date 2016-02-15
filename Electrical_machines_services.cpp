/*
	Name: Service type of electrical machines
	Copyright: Moreno Laci
	Author: Moreno Laci
	Date: 06/10/15 16.06
	Description: This program could calculate the temperature of an electrical machine(transormers, generators and motors ). I insert here the services I know :
	- S1 : continuous service;
	- S2 : limited duration service;
	- S3 : intermittent periodic service;
	- S6 : continuous periodic service.
*/

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

//=================================================COSTANTI=============================================================

const double e = 2.718281828; //numero di nepero
const int S1 = 1;            //i numeri associati a ogni servizio, si poteva fare i fighi usando enum
const int S2 = 2;
const int S3 = 3;
const int S6 = 4;

//================================================PROTOTIPI=====================================================================

double riscaldamento(double Tregime, double Tambiente, double tau, double tempo);             //i prototipi termici
double raffreddamento(double Tregime, double Tambiente, double tau, double tempo);
void acquisizione(double& Tregime, double& Tamb, double& tau);                        //prototipo dell'acquisizione dei dati
void fServizio(int& tipo);                                                            //prototipo che mi dice se ï¿½ S1,S2,S3 o S6. i primi tre useranno lo stesso frammento di codice
void restart(int& decisione);                                                         //prototipo che chiede se si riscalda, raffredda a si esce dal programma
double durata(int scelta, int servizio);                                              //prototipo per chiede il tempo di raff o risc
void acquisizioneS6(double& TrAlt, double& TrBas, double& tau, double&tetaA);         //prototipo per l'acquisizione dei dati dell'S6
void sbalzoTerm(int& tipo, int servizio);                                             //prototipo per capire se si riscalda o raffredda
void Riscaldamento(double Tregime, double Tambiente, double tau, int scelta, int servizio); //prototipo che esegue l'intero blocco riscaldamento
void Raffreddamento(double Tregime, double Tambiente, double tau, int scelta, int servizio); //prototipo che esegue l'intero blocco raffreddamento
void GrfGen(int servizio, int& SiNo, double& tempo);                                  //prototipo che chiede se si vogliamo i punti del grafico
void GrfS1();                                                                         //funzioni per i grafici di ogni servizio
void GrfS2();
void GrfS3();
void GrfS6();
//================================================================MAIN============================================================================

int main() {
	double tau, tetaA;                                //le variabili, teta ï¿½ la temperatura
	int scelta = 0;                                   //ci dice se la macchina si scalda o si raffredda
	int servizio;                                     //memorizza il numero di servizio
	double intervalli;                                //questa vvariabie ci permette di avere l'intervallo di tempo che deve avere la funzione
	
	fServizio(servizio);                                             //chiamata funzione per capire il tipo di servizio
	
	if(servizio == S6) {                                                           //servizio continuativo con carico intermittente(S6)
		double regimeAlto, regimeBasso;                                           //variabili che sevono solo per questo ciclo
		
		acquisizioneS6(regimeAlto, regimeBasso, tau, tetaA);                       //chiamta funzione
		
		//=======================================================================INIZIO CICLO FOR======================================================
		
		for(;;) {
			sbalzoTerm(scelta, servizio);
			
			if(scelta == 1) {                   //Riscaldamento
				Riscaldamento(regimeAlto,tetaA,tau,scelta,servizio);
				
				restart(scelta);
	        	if(scelta != 1 ){
	    			break;
				}
			}
			else if(scelta == 2) {
				Riscaldamento(regimeBasso,tetaA,tau,scelta,servizio); //Qui la macchina lavora ancora quindi si riscalderebbe ancora solo che la temperatura scende
			
				restart(scelta);
	    		if(scelta != 1){
	    			break;
				}
			}
		}
		
		//=========================================================================FINE CICLO FOR======================================================
		
	}
	
	else if(servizio == S1 || servizio == S2 || servizio == S3) {                          //tutti gli altri servizi ugali, NEL CALCOLO!
		double tetaR;                                                                      //dichiaro le variabili che servono solo a questi servizi
		
	    acquisizione(tetaR, tetaA, tau);                                                    //chiamata funzione per acquisire i dati da tastiera
	
	    //========================INIZIO CICLO FOR======================================================================================================
	    
		for(;;) { 
	        sbalzoTerm(scelta, servizio);
	        
	        if(scelta == 1){               //RISCALDAMENTO
		        Riscaldamento(tetaR,tetaA,tau,scelta,servizio);
		        
		        restart(scelta);
	    		if(scelta != 1){
	    			break;
				}
	        }
	        
	        else if(scelta == 2) {         //RAFFREDDAMENTO
		        Raffreddamento(tetaR,tetaA,tau,scelta,servizio);
		        
		        restart(scelta);
	    		if(scelta != 1 ){
	    			break;
				}
	        }
	        
	       else{
		        return 0;
	        }
	    }
		//========================FINE CICLO FOR========================================================================================================
    }
    
    return 0;
}

//====================================================DEFINIAMO LE FUNZIONI===================================================================================================

double riscaldamento(double Tregime, double Tambiente, double tau, double tempo) { //calcolando il riscaldamento
	double risc, esponente; 							//eponente rappresenta -t/tau
	int partenza;        		//da che temperatura stai partendo?
	
	cerr<<"\nInserisci:\n"
		<<"\t1 Se stai partendo dalla temperatura ambiente;\n"
		<<"\t2 Se stai partendo da un altra temperatura.\n";//bisogna capire da dove si parte perchï¿½ il riscaldamento ï¿½ diverso
	cin>>partenza;
	
	if(partenza == 2){  //DA CHE TEMPERATURA PARTI??
		cerr<<"\nInserisci la temperatura di partenza:\n";
		cin>>Tambiente;
	}
	
	esponente = -(tempo)/tau;
	risc = Tambiente+(Tregime - Tambiente)*(1 - pow(e, esponente)); //T = Ta + (Tr-Ta)(1-e^-(t/tau))
	
	return risc;
}

double raffreddamento(double Tregime, double Tambiente, double tau, double tempo) {//Funzione per il raffreddamento, commenti simili a sopra
	double raff, esponente;
	int partenza;
	
	cerr<<"\nInserisci:\n"
		<<"\t1 Se stai partendo dalla temperatura di regime;\n"
		<<"\t2 Se stai partendo da un altra temperatura.\n";
	cin>>partenza;
	
	if(partenza == 2){  //FACCIAMOCI DIRE DA CHE TEMPERATURA STIAMO PARTENDO
		cerr<<"\nInserisci la temperatura di partenza:\n";
		cin>>Tregime;
	}
	
	esponente = -(tempo)/tau;
	raff = Tambiente+(Tregime - Tambiente)*(pow(e, esponente));
	return raff;
}

void acquisizione(double& Tregime, double& Tamb, double& tau) { //Acquisiamo i dati per S1,S2,S3
	cerr<<"\tInserisci la temperatura di regime:\n";                       //gli input
	cin>>Tregime;
	cerr<<"\tInserisci la temperatura ambiente:\n";
	cin>>Tamb;
	cerr<<"\tInserisci la costante di tempo(in secondi):\n";
	cin>>tau;
}

void fServizio(int& tipo) { //Come funziona questa macchina elettrica??
    cerr<<"\tInserisci il tipo di servizio della tua macchina elettrica:\n"
        <<"Premi 1 per S1;\n"
        <<"Premi 2 per S2;\n"
        <<"Premi 3 per S3;\n"
        <<"Premi 4 per S6.\n\n";
    cin>>tipo;
}

void restart(int& decisione) { //Chiediamo se andare avanti nel cercare temperature
	cerr<<"Inserisci:\n"
		<<"\t1 Per continuare;\n"
		<<"\t2 Per uscire.\n";  //scelta se continuare o uscire
	cin>>decisione;
	cerr<<"\n\n\n";   //vado a capo
}

double durata(int scelta, int servizio) {  //Qui ritorniamo il valore che ci dice per quanto tempo la macchina fa una determinata azione
	double tempo;   
	
	if(servizio == 1 || servizio == 2|| servizio == 3) {          //S1,S2,S3
		if(scelta == 1) { 
			cerr<<"\nPer quanto tempo lavora?(in secondi)\n";     //input tempo
			cin>>tempo;
		}
		else if(scelta == 2) {
			cerr<<"\nPer quanto tempo riposa?(in secondi)\n";     //input tempo
			cin>>tempo;
		}
	}
	
	else if(servizio == 4) {  //S6
		if(scelta == 1) { 
			cerr<<"\nPer quanto tempo funziona a pieno carico?(in secondi)\n";     //input tempo
			cin>>tempo;
		}
		else if(scelta == 2) {
			cerr<<"\nPer quanto tempo lavora a carico ridotto?(in secondi)\n";     //input tempo
			cin>>tempo;
		}
	}
	
	return tempo;
}

void acquisizioneS6(double& TrAlt, double& TrBas, double& tau, double& tetaA) { //Preleviamo le caratteristiche nominali dell'S6
	cerr<<"\tInserisci il regime alto(dove la macchina ha un carico maggiore):\n";
	cin>>TrAlt;                                                                      //Temperatura regime Alto
	
	cerr<<"\tInerisci il regime basso(dove la macchina ha un carico minore):\n";
	cin>>TrBas;																		//Temperatura regime Basso
	
	cerr<<"\tInserisci la costante di tempo(in secondi):\n";
	cin>>tau;
	
	cerr<<"\tInserisci la temperatura ambiente:\n";
	cin>>tetaA;
}

void sbalzoTerm(int& tipo, int servizio) {           //8^FUNZIONE
	
	if(servizio == 1 || servizio == 2|| servizio == 3) {  //S1, S2, S3
		cerr<<"\nInserisci:\n"
			<<"\t1 Se sta lavorando;\n"
			<<"\t2 Se e a riposo.\n"; //scelta tra risc e raff
		cin>>tipo;
    }
    else if (servizio == 4) {            //S6
    	cerr<<"\nInserisci:\n"
			<<"\t1 Se funziona a pieno carico;\n"
			<<"\t2 Se funziona a carico ridotto.\n"; //scelta tra Pieno carico, o carico ridotto
		cin>>tipo;
	}
}

void Riscaldamento(double Tregime, double Tambiente, double tau, int scelta, int servizio) {  //RISCALFDAMENTO GENERALE
		double tempo, tetafinale;
		tempo = durata(scelta,servizio);
		tetafinale = riscaldamento(Tregime, Tambiente, tau, tempo);  //chiamata della funzione, per capire a che temperatura andiamo
	    cout<<"\nLa nuova temperatura e: "
			<<setprecision(4)
			<<tetafinale
			<<" gradi centigradi\n\n\n";  //output di temperatura
}
	
void Raffreddamento(double Tregime, double Tambiente, double tau, int scelta, int servizio) { //RAFFREDDAMENTO GENERALE	
		double tempo, tetafinale;
		tempo = durata(scelta, servizio);
		tetafinale = raffreddamento(Tregime, Tambiente, tau, tempo);
		cout<<"\nLa nuova temperatura e: "
			<<setprecision(4)
			<<tetafinale
			<<" gradi centigradi\n\n\n";
	                
}
//=============================================================WORK IN PROGRESS==============================================================================

void Grafico(int servizio, int& SiNo, double& tempo) {  //Per acquisire l'intervallo di tempo per il grafio se c'Ã¨
	cout<<"Inserisci:\n"
		<<"\t1 Se voui avere i punti di un grafico;\n"
		<<"\t2 Se vuoi cercarti altri punti.";
	cin>> SiNo;
	
	if(SiNo == 1) {                //se si vuole il grafico si richiede l'intervalllo di tempo
		cout<<"Inserisci la distanza(in secondi) tra un tempo e l'altro";
		cin>>tempo;
	
	
        switch(servizio) {      //il programma sceglie il tipo di grafico
            case 1 :
                GrfS1();
                break;
            case 2 :
                GrfS2();
                break;
            case 3 :
                GrfS3();
                break;
            case 4 :
                GrfS6();
                break;
        }
        
    }
	
}
