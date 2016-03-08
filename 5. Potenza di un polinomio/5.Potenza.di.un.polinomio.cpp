//Programma che sviluppa l'elevamento a potenza di un qualsiasi binomio    (k1*a + k2*b)^n
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

class Polinomio {
	float k1,k2;     //parti numeriche
	char a,b;        //parti letterali
	int potenza;
	bool doppia_lett;   //ci dirà se ci sono due lettere o meno
	         
	public:	
		void sviluppa();   //stampa ed elaborazione del risultato
		Polinomio(Polinomio& p);   //csotruzione delle istanze
		~Polinomio();
};

int fattoriale(int n);           //per calcolare il fattoriale da rivedere !!


Polinomio::Polinomio(Polinomio& p) {      //inserimento delle lettere e dei numeri

	int let;
	
	cout<<"Inserisci il coefficiente della lettera del primo membro:"<<endl;
	cin>>p.k1;
	
	cout<<"Inserisci la lettera del primo membro:"<<endl;
	cin>>p.a;
	 
	do {                           //chiedere se ci sono due lettere o no
		cout<<"Inserisci:\n"
			<<"\t1 Se c'e la parte letterale nel secondo membro;\n"
			<<"\t2 Se non c'e.\n";
		cin>>let;
		
		if(let == 1) p.doppia_lett = true;      //assegnamo il valore all'attributo che informa della presenza o meno di parte letterale
		else p.doppia_lett = false; 
		
	}while(let != 1 && let != 2);
	
	if(p.doppia_lett == true) {         //se ci sono due lettere
		cout<<"Inserisci il coefficiente della lettera del secondo membro:"<<endl;
		cin>>p.k2;
		
		cout<<"Inserisci la lettera del secondo membro:"<<endl;
		cin>>p.b;
	}
	
	else {
		cout<<"Inserisci il numero del secondo membro:"<<endl;
		cin>>p.k2;
	}
	
	cout<<"Inserisci l'esponente del binomio:"<<endl;
	cin>>p.potenza;
	
} 


Polinomio::~Polinomio() {
	
	cout<<"\nOggetto distrutto"<<endl;
	
}


void Polinomio::sviluppa() {
		int k = 0;               //il coefficiente del secondo membro che incrementera
		int n = potenza;
		
		if(potenza == 0) {
			cout<<"Il risultato e:    1"<<endl;
		}
		
		else {
			for(int i=0; i<=potenza; i++) {
				
				int coeff = fattoriale(potenza)/(fattoriale(k)*fattoriale(potenza - k));    //calcolo del coefficiente moltiplicativo
				
				float pow_k1 = pow(static_cast<float>(k1), static_cast<float>(n));     //coefficienti originari elevati a potenza
				float pow_k2 = pow(static_cast<float>(k2), static_cast<float>(k));
				
				float result = static_cast<float>(coeff)*pow_k1*pow_k2;
				
				if(doppia_lett) {                                                 //se c'è una sola lettera
					if(k == 0) cout<<result<<a<<"^"<<n<<"  ";                 //rendendo l'output migliore se ci sono casi particolari degli esponenti
					
					else if(k == 1 && n == 1) cout<<result<<a<<b<<"  ";
	
					else if(n == 0)  cout<<result<<b<<"^"<<k<<"  ";	
					
					else if(n == 1) cout<<result<<a<<b<<"^"<<k<<"  ";	
					
					else if(k == 1) cout<<result<<a<<"^"<<n<<" "<<b<<"  ";	
										
					else            cout<<result<<a<<"^"<<n<<" "<<b<<"^"<<k<<"  ";	
				}
	
				else {
					if(n == 0) cout<<result<<setw(2);
					
					else if(n == 1) cout<<result<<a<<setw(2);
					
					else {
						cout<<result<<a<<"^"<<n<<setw(2);
					}
				}
				
				k++;
				n--;
			}
		}
}

int fattoriale(int n) {         //classico esempio di ricorsione
	
	if(n==0) {
		return 1;
	}
	else {
		return (n*fattoriale(n-1));
	}
}


int main() {
	
	Polinomio binomio(binomio);
	
	binomio.sviluppa();
	
	binomio.~Polinomio();
	
	return 0;
}



