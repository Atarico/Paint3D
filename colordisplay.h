#ifndef COLORDISPLAY_H
#define COLORDISPLAY_H

#include <QWidget>

class colorDisplay : public QWidget
{
    Q_OBJECT

private:
    int r = 255, g = 255, b = 255, a = 255;

public:
    explicit colorDisplay(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void changeColor(int r, int g, int b, int a);

signals:

public slots:
};

#endif // COLORDISPLAY_H
