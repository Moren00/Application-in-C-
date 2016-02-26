#include<iostream>
#include<cmath>
using namespace std;
/* Programma in grado di convertire le forme dei numeri comlessi 
 Algebrica e trigonometrica sfruttando le loro relazioni matematiche 
Scrivendole in un programma*/

int main() {
	int scelta; // variabile per la scelta dell'operazione che verrà eseguita
	cout<<"\t Questo programma e in grado di convertire un numero complesso \n";
	cout<<"\t Dalla forma Algebrica a quella Trigonometrica e viceversa \n";
	cout<<"\t N.B. GLI ANGOLI IN RADIANTI !\n";
	cout<<"Premi un tasto indicato a seconda della tua scelta: \n";
	cout<<"1\t Algebrica --> Trigonometrica\n";
	cout<<"2\t Trigonometrica --> Algebrica\n";
	cout<<"Altro\t Esci\n\n";
	cin>> scelta;
	
	if (scelta == 1){
		double re,im,arg,modulo;
        cout<<"\t Inserisci la parte reale: \n";
        cin>>re;
        cout<<"\t Inserisci la parte immaginaria (senza i o j): \n";
        cin>>im;
        arg = im/re;
        modulo=sqrt(re*re + im*im);
        cout<<"\t"<<modulo<<"(cos"<<arg<<"+ jsen"<<arg<<") \n";          
	}
	else if (scelta == 2) {
	    double re,im,arg,modulo;
	    cout<<"\t Inserisci il modulo: \n";
	    cin>> modulo;
	    cout<<"\t Inserisci l'argomento: \n";
	    cin>> arg;
	    re = modulo*(cos(arg));
	    im = modulo*(sin(arg));
	    cout<<"\t"<<re<<" + j"<<"("<<im<<") \n\n";
	}
	else {
		exit(scelta);
	}
	
	return main();
}





















