//
// Created by rcourbier on 01/03/19.
//

#include "CreateMozaique.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2)
    {
        printf("Usage: Image\n");
        exit (1) ;
    }

    OCTET *ImgIn,*ImgOut;
    int nH,nW;
    char name[256],nameOut[256];
    sscanf(argv[1],"%s",name);
    sscanf("moza",argv[1],"%s%s",nameOut);
    lire_nb_lignes_colonnes_image_pgm(name, &nH, &nW);
    allocation_tableau(ImgIn, OCTET, nH*nW);
    int nbBlocsH = (int)nH/TAILLE_BLOC;
    int nbBlocsW = (int)nW/TAILLE_BLOC;
    int taille= 512*512*nbBlocsH*nbBlocsW;

    allocation_tableau(ImgOut, OCTET, taille);
    lire_image_pgm(name, ImgIn, nH * nW);

    //taille bloc 16
    vector<string> vect = vector<string>();

    //parcours de imageIN
    for(int y=0;y<nH;y+=TAILLE_BLOC){
        for(int x=0;x<nW;x+=TAILLE_BLOC){
            //calculer moyenne
            double moyenne = Librairie::valeurMoyenne(ImgIn,nH,nW,y,x,TAILLE_BLOC);

            //Trouver image avec meilleur moyenne
            vect.push_back(Librairie::getBestImg(moyenne));
            
        }
    }

    //remplissage de ImageOut
    for(int i=0;i<vect.size();i++){
        OCTET* ImgLu;
        allocation_tableau(ImgLu,OCTET,512*512);
        char nom[vect[i].size()+1];
        strcpy(nom, vect[i].c_str());
        lire_image_pgm(nom,ImgLu,512*512);
        int offset = nbBlocsW*512*512;
        for(int index=0;index<512*512;index++){
            int yImg = (int)(i/nbBlocsW)*offset+512*nbBlocsW*(int)(index/512);
            int xImg = 512*(i%nbBlocsW) + ( index % 512 );
            ImgOut[yImg+xImg] = ImgLu[index];
        }
    }

    ecrire_image_pgm("Test.pgm",ImgOut,512*nbBlocsH,512*nbBlocsW);

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

string Librairie::getBestImg(double val){
    ifstream fichier("data.dat", ios::in);

    if(fichier){
        double bestDif=255,currentVal;
        string name,bestName;
        int nh,nw;

        for(int i = 0; i < 10000; i++)
        {
            fichier >> currentVal>>name>>nh>>nw;

            if(abs((long)(currentVal-val))<bestDif){
                bestDif=abs((long)(currentVal-val));
                bestName=name;
            }

            //cout << "test : "<<name<<" : "<<currentVal<<std::endl;
        }

        return bestName;
        

    }else{
        cout << "Erreur d'ouverture du fichier data"<<endl;
        exit(1);
    }
}