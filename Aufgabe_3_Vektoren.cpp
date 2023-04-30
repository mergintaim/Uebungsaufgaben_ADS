#include <iostream>
#include <vector>


#define SUCCESS 0
#define FAILURE -1

using namespace std;

vector<int> fill_vector(int vectorsize){
    vector<int> returnvector(vectorsize);
    for (int i = 0; i < returnvector.size(); i++)
    {
        cout<<"Bitte geben Sie den Wert für die "<<i+1<<"Stelle des Vektors ein:\n";
        cin >> returnvector[i];
    }
    return returnvector;
}

int print_vector(vector<int> vector){
    cout<<"Der Vektor hat folgende Werte:\n";
        for (int i = 0; i < vector.size(); i++)
        {
            cout<<"An Stelle "<<i+1<<". des Vektors ist der Wert "<<vector[i]<<" hinterlegt\n";
        }
        cout << "Der Vektor sieht so aus: ";
        for (int i = 0; i < vector.size(); i++)
        {
            cout<<vector[i]<<" ";
        }
        cout<<endl;
}
int compare_vectors(vector<int> ursprungsvektor, vector<int> vergleichsvektor){
    int matchcounter = 0;
    for (int i = 0; i < vergleichsvektor.size(); i++)
    {
        for (int j = 0; j < ursprungsvektor.size(); j++)
        {
            if (vergleichsvektor[i] == ursprungsvektor[j])
            {
                matchcounter += 1;
                cout<<"Der folgende Wert ist redundant und wurde an Stelle: "<<j+1<<" aus dem Ursprungsvektor gelöscht:"<<ursprungsvektor[j]<<endl;
                ursprungsvektor.erase(ursprungsvektor.begin()+j);
                
            }
        }
        
    }
    if (matchcounter == 0)
    {
        cout<<"Es gab keine redundanten Werte"<<endl;
    }
    cout<< "Dies ist der bereinigte Ursprungsvektor: "<<endl;
    print_vector(ursprungsvektor);
}


int main(){
    cout<<"Übungsaufgabe 3: Vektoren \n";
    int size_ursprungsvektor = 5;  
    int size_vergleichsvektor = 5;



    cout<<"Wie viele Elemente soll der Ursprungsvektor enthalten?"<<endl;
    cin >> size_ursprungsvektor;
    cout<<"Bitte geben Sie nun nacheinander die Integerwerte für den Ursprungsvektor ein\n";
    vector<int> int_ursprungsvektor = fill_vector(size_ursprungsvektor);
    //inhalt wieder ausgeben
    print_vector(int_ursprungsvektor);
    //vergleichsvektor einlesen
    cout<<"Wie viele Elemente soll der Vergleichsvektor enthalten?"<<endl;
    cin >> size_vergleichsvektor;
    cout << "Bitte geben Sie nun den Vergleichvektor ein:"<<endl;
    vector<int> int_verlgeichsvektor = fill_vector(size_vergleichsvektor);
    print_vector(int_verlgeichsvektor);
    //vergleichen
    compare_vectors(int_ursprungsvektor,int_verlgeichsvektor);
}