//
// Created by rcourbier on 01/03/19.
//

#include "GenData.h"

using namespace std;


//<summary>Génère un fichier de donneés selon un algo de Librairie.cpp
// <params>Nom de la fonction de Librairie.cpp</params>
// </summary>
int main(int argc, char **argv) {

    if (argc != 2)
    {
        printf("Usage: nomAlgo\n");
        exit (1) ;
    }

    string nomAlgo;
    nomAlgo = argv[1];

    cout << "Nom de l algo : "<<nomAlgo<<endl;

    //FILE* monF = fopen("data.dat","w");

    ofstream fichier("data.dat", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier
    cout << "Nom de l algo : "<<nomAlgo<<endl;


    if (fichier){
        cout << "Nom de l algo : "<<nomAlgo<<endl;
        //vector<double,string> vect = vector<double,string>();//pour 
        for (int i = 0; i < 10000; ++i) {
            //le nom du fichier est donc i.pgm
            OCTET *ImgIn;
            int nH,nW;
            char name[256];
            sprintf(name,"../Images/%d.pgm",i);
            cout<<"nom :"<<name<<endl;
            lire_nb_lignes_colonnes_image_pgm(name, &nH, &nW);
            allocation_tableau(ImgIn, OCTET, nH*nW);
            lire_image_pgm(name, ImgIn, nH * nW);

            //TODO au lieu  de Librairie::valeur moyenne il faut utiliser Librairie::nomAlgo
            //TODO tri par insertion

            double val = Librairie::valeurMoyenne(ImgIn,nH,nW,0,0,nH);

            //vect.insert(50,val,"test");

            fichier <<val << " "<<name<<" "<<nH<<" "<<nW<<endl;

        }
    }else{
        cout << "Erreur d'ouverture du fichier data"<<endl;
        exit(1);
    }

}

double Librairie::valeurMoyenne(OCTET *imageIn, int height, int width,int i, int j, int tailleBloc) {
    double somme =0;
    double nbPixel = 0;
    for (int k = i; k < i+tailleBloc; ++k) {
        for (int l = j; l < j+tailleBloc; ++l) {
            somme +=imageIn[k*height+l];
            nbPixel++;
        }
    }
    double val = somme/nbPixel;
    return val;
}