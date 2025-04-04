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


class Sprite : public QObject { // Rendre mon objet un QPixMapItem.
public:
    Sprite(QString image, QString jsonfile);
    void setpos(int x, int y);
    void setsize(float size);
    void start(int vitesse);
    void startreverse(int vitesse);
    void stop();
    void setframe(int index);
    ~Sprite();
    QGraphicsPixmapItem* pixmapItem;
    QPixmap spritesheet;
    
private:
    
    QStringList frameCle;
    void previousframe();
    void nextframe();
    int x = 0;
    int y = 0;
    QJsonObject json;
    QTimer* spritetimer;
    QTimer* previousspritetimer;
    int updatetime = 0;
    int currentframeindex = 0;
    bool running = false;
};

#endif
