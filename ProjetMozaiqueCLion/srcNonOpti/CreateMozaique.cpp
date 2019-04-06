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
    //int taille= 512*512*nbBlocsH*nbBlocsW;

    allocation_tableau(ImgOut, OCTET, 512*512);
    lire_image_pgm(name, ImgIn, nH * nW);

    //taille bloc 16
    vector<string> vect = vector<string>();

    ifstream file;
    file.open("data.dat",ios::in);

    //parcours de imageIN
    for(int y=0;y<nH;y+=TAILLE_BLOC){
        for(int x=0;x<nW;x+=TAILLE_BLOC){
            //calculer moyenne
            double moyenne = Librairie::valeurMoyenne(ImgIn,nH,nW,y,x,TAILLE_BLOC);

            //Trouver image avec meilleur moyenne
            vect.push_back(Librairie::getBestImg(moyenne,file));
            
        }
    }

    file.close();

    //remplissage de ImageOut
    for(int i=0;i<vect.size();i++){
        OCTET* ImgLu;
        allocation_tableau(ImgLu,OCTET,512*512);
        char nom[vect[i].size()+1];
        strcpy(nom, vect[i].c_str());

        int tailleImageLue = 512;

        lire_image_pgm(nom,ImgLu,tailleImageLue*tailleImageLue);



        int tailleBlocImagette = tailleImageLue/TAILLE_BLOC;
        int nbBlocsImagette = tailleImageLue / tailleBlocImagette;
        vector<double> moyennesImagette;

        for(int j = 0 ; j < nbBlocsImagette*nbBlocsImagette ; j++)
        {
            int posXBloc = (j*tailleBlocImagette)%tailleImageLue;
            int posYBloc =(j / nbBlocsImagette)*tailleBlocImagette;

            double moyenneImg = Librairie::valeurMoyenne(ImgLu,tailleImageLue,tailleImageLue,posXBloc,posYBloc,tailleBlocImagette);
            moyennesImagette.push_back(moyenneImg);
        }


        int offset = nbBlocsW*TAILLE_BLOC*TAILLE_BLOC;
        int index=0;
        int baseBlock = (i/nbBlocsH)*tailleImageLue*TAILLE_BLOC+(i%nbBlocsW)*TAILLE_BLOC; 
        for(int iImg=0;iImg<TAILLE_BLOC;iImg++){
            for(int jImg=0;jImg<TAILLE_BLOC;jImg++){
                //ImgOut[(i/nbBlocsH)*tailleImageLue*TAILLE_BLOC+iImg*tailleImageLue+(i%nbBlocsW)*TAILLE_BLOC+jImg]=(int)moyennesImagette[index];
                ImgOut[baseBlock+iImg*tailleImageLue+jImg]=(int)moyennesImagette[index];
                index++;
            }   
        }


        /*//Version pour l image sans resize (check l offset)
        for(int index=0;index<moyennesImagette.size();index++){
            int yImg = (int)(i/nbBlocsW)*offset + nbBlocsW*(int)(index/TAILLE_BLOC);
            int xImg = TAILLE_BLOC*(i%nbBlocsW) + ( index % TAILLE_BLOC );
            ImgOut[yImg+xImg] = moyennesImagette[index];
        }*/



        // int offset = nbBlocsW*512*512;
        // for(int index=0;index<512*512;index++){
        //     int yImg = (int)(i/nbBlocsW)*offset+512*nbBlocsW*(int)(index/512);
        //     int xImg = 512*(i%nbBlocsW) + ( index % 512 );
        //     ImgOut[yImg+xImg] = ImgLu[index];
        // }
    }

    ecrire_image_pgm("Test.pgm",ImgOut,nH,nW);

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

string Librairie::getBestImg(double val, std::ifstream& fichier){

    if(fichier){
        double bestDif=255,currentVal,previousVal;
        string name,bestName,previousName;
        int nh,nw;

        int indexBestVal=2;
        fichier >> previousVal>>previousName>>nh>>nw;
        fichier >> currentVal>>name>>nh>>nw;
        while(indexBestVal<10000 && currentVal<val){
            previousVal=currentVal;
            previousName=name;
            fichier >> currentVal>>name>>nh>>nw;
            indexBestVal++;
        }

        if(val-previousVal<currentVal-val){
            //previous Best
            bestName=previousName;
        }else{
            //val best
            bestName=name;
        }

        fichier.clear();
        fichier.seekg(0, ios::beg);

        return bestName;
        

    }else{
        cout << "Erreur d'ouverture du fichier data"<<endl;
        exit(1);
    }
}