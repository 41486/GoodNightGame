#include "caselabel.h"

CaseLabel::CaseLabel(int x, int y)
{
    this->x = x;
    this->y = y;
}

void CaseLabel::mousePressEvent(QMouseEvent * event)
{
    emit clicked(this->x,this->y);
}
