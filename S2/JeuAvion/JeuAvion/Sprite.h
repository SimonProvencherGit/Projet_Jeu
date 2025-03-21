#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QJsonObject>
#include <QTimer>
#include <QFile>
#include <QJsonDocument>
#include <QStringList>


class Sprite : public QObject, public QGraphicsPixmapItem { // Rendre mon objet un QPixMapItem.
public:
    Sprite(QString image, QString jsonfile, int updatetime);
    void setpos(int x, int y);
    void setsize(float size);
    void start(int vitesse);
    void stop();
    ~Sprite();
    QGraphicsPixmapItem pixmapItem;
private:
    void nextframe();
    int x = 0;
    int y = 0;
    QPixmap spritesheet;
    QJsonObject json;
    QTimer* spritetimer;
    int updatetime = 0;
    int currentframe = 0;
    bool running = false;
};

#endif
