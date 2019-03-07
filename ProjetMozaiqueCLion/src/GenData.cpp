//
// Created by rcourbier on 01/03/19.
//

#include "GenData.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


//<summary>Génère un fichier de donneés selon un algo de Librairie.cpp
// <params>Nom de la fonction de Librairie.cpp</params>
// </summary>
int GenData::main(int argc, char **argv) {

    if (argc != 2)
    {
        printf("Usage: nomAlgo\n");
        exit (1) ;
    }

    string nomAlgo;
    nomAlgo = argv[1];

    cout << "Nom de l algo : "<<nomAlgo<<endl;

    ofstream fichier("data_"+nomAlgo+".dat", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

    if (fichier){
        for (int i = 0; i < 10000; ++i) {
            //le nom du fichier est donc i.pgm
            OCTET *ImgIn;
            int nH,nW;
            string name = "Images/"+i;
            name += ".pgm";
            char* nom= (char *)name.c_str();
            lire_nb_lignes_colonnes_image_pgm(nom, &nH, &nW);
            allocation_tableau(ImgIn, OCTET, nH*nW);
            lire_image_pgm(nom, ImgIn, nH * nW);

            //TODO au lieu  de Librairie::valeur moyenne il faut utiliser Librairie::nomAlgo

            double val = Librairie::valeurMoyenne(ImgIn,nH,nW,0,0,nH);

            fichier <<val << " "<<nom<<" "<<nH<<" "<<nW<<endl;

        }
    }else{
        cout << "Erreur d'ouverture du fichier data"<<endl;
        exit(1);
    }

}