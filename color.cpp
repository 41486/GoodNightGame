#include "color.h"

QString getQStrColor(Color color) {
    QString colorStr;
    switch (color) {
        case Color::BLACK:
            colorStr = "Noir";
        break;
        case Color::RED:
            colorStr = "Rouge";
        break;
        case Color::PURPLE:
            colorStr = "Mauve";
        break;
        case Color::BLUE:
            colorStr = "Bleu";
        break;
        case Color::GREEN:
            colorStr = "Vert";
        break;
        case Color::NONE:
            colorStr = "N/A";
        break;
    }
    return colorStr;
}
