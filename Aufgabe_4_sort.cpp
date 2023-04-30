#include <iostream>
#include <vector>

#define SUCCESS  0
#define FAILURE -1

using namespace std;

vector<int> bubblesort(vector<int> vector){
    int iterations = vector.size();
    bool swapped = false;
    int temp = 0;
    do{
        swapped = false;
        for (int i = 0; i < iterations-1; i++)
        {
            if (vector[i] > vector[i+1])
            {
                temp = vector[i];
                vector[i] = vector[i+1];
                vector[i+1] = temp;
                swapped = true;
            }
        }
        iterations -= 1;
    }while (swapped);
    return vector;
}


int main(){
    vector<int> Matrikelnummern(5,0); //init with 0s
    cout<<"Bitte geben sie durch Enter getrennt 5 Matrikelnummern ein:"<<endl;
    for (int i = 0; i < Matrikelnummern.size(); i++)
    {
        cout<<"Bitte geben Sie die erste Matrikelnummer ein:"<<endl;
        cin >> Matrikelnummern[i];
        cout<<"Folgende Matrikelnummer wurde eingelesen: "<<Matrikelnummern[i]<<endl;
    }
    //bubblesort
    Matrikelnummern = bubblesort(Matrikelnummern);
    cout<<"Dies sind die sortierten Matrikelnummer:"<<endl;
    for (int i = 0; i < Matrikelnummern.size(); i++)
    {
        cout<<"Matrikelnummer "<<i<<": "<<Matrikelnummern[i]<<endl;
    }
    

    return 0;
}