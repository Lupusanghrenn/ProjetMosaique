//
// Created by rcourbier on 01/03/19.
//

#include "Librairie.h"


//<summary>Méthode pour calculer la valeur moyenne d'une image (pour bloc d'une image)
//<para>Si on defini i et j a 0 et une taille de bloc a width ou heigth, on obtient l algo pour une image entière</para>
// <params name="imageIn">Tableau contenant l'image a analysé</params>
// <params name="height">Taille du tableau height</params>
// <params name="width">Taille du tableau width</params>
// <params name="i">Index de debut du bloc (ligne)</params>
// <params name="j">Index de debut du bloc (colonne)</params>
// <returns>Retourne la valeur moyenne du bloc</returns>
// </summary>
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