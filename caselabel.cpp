#include "caselabel.h"

CaseLabel::CaseLabel(int x, int y)
{
    this->x = x;
    this->y = y;
}

void CaseLabel::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton) {
        emit clicked(this->x,this->y);
    }
}
