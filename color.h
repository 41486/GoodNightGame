#ifndef COLOR_H
#define COLOR_H

/*!
 * \file color.h
 * \brief Enumération contenant les différentes couleurs possibles d'une étoile
 * \author G41486
 */

#include <QString>

enum class Color {
    PURPLE, BLACK, RED, GREEN, BLUE, NONE
};

QString getQStrColor(Color color);

#endif // COLOR

