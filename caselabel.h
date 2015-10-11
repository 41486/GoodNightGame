#ifndef CASELABEL_H
#define CASELABEL_H

#include <QLabel>
#include <QMouseEvent>

class CaseLabel : public QLabel
{
    Q_OBJECT
public:
    CaseLabel(int x, int y);

signals:
    void clicked(int x, int y);

protected:
    void mousePressEvent(QMouseEvent * event);

private:
    int x;
    int y;
};

#endif // CASELABEL_H
