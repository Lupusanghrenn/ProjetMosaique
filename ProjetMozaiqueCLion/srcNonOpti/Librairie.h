//
// Created by rcourbier on 01/03/19.
//
#ifndef PROJETMOSAIQUE_LIBRAIRIE_H
#define PROJETMOSAIQUE_LIBRAIRIE_H

#include "../libs/image_ppm.h"
#include <iostream>
#include <fstream>

#define TAILLE_BLOC 2


class Librairie {
public:
    static double valeurMoyenne(OCTET *imageIn, int height, int width, int i, int j, int tailleBloc);
    static std::string getBestImg(double val);
};


#endif //PROJETMOSAIQUE_LIBRAIRIE_H