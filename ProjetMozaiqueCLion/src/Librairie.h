//
// Created by rcourbier on 01/03/19.
//

#include "../libs/ImageBase.cpp"

#ifndef PROJETMOSAIQUE_LIBRAIRIE_H
#define PROJETMOSAIQUE_LIBRAIRIE_H

#define TAILLE_BLOC 16


class Librairie {
public:
    static double valeurMoyenne(OCTET *imageIn, int height, int width, int i, int j, int tailleBloc);
};


#endif //PROJETMOSAIQUE_LIBRAIRIE_H
