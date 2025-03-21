#include "Sprite.h"
// https://www.youtube.com/watch?v=lrrptFVlMu4
Sprite::Sprite(QString image, QString jsonfile, int updatetime){
    spritesheet = QPixmap("Textures\\Sprites\\" + image);
    QFile Fichier("Textures\\Sprites\\" + jsonfile);
    // Verify if the file is opened
    if (Fichier.open(QIODevice::ReadOnly)) {
        if (spritesheet.isNull()) {
            qDebug() << "Erreur ouverture dimage.";
        }
        QByteArray Bytes = Fichier.readAll();
        QJsonDocument tempdoc = QJsonDocument::fromJson(Bytes);
        json = tempdoc.object().value("frames").toObject();
        if (json.isEmpty()) {
            qDebug() << "json invalid";
        }
        Fichier.close();
    }
    else {
        qDebug() << "erreur ouverture du json";
    }
    spritetimer = new QTimer(this);
    QObject::connect(spritetimer, &QTimer::timeout, [=]() {
        qDebug() << "Timer triggered!";
        nextframe();
        });
   // spritetimer->start(100);
}

void Sprite::setpos(int inputx, int inputy) {
 
        x = inputx;
        y = inputy;
        pixmapItem.setPos(x, y);
}

void Sprite::setsize(float size) {
    
        spritesheet = spritesheet.scaled(spritesheet.width() * size, spritesheet.height() * size, Qt::KeepAspectRatio);
        pixmapItem.setPixmap(spritesheet); // Update pixmapItem to the resized spritesheet
  
}

void Sprite::stop() {
    if (spritetimer) {
        spritetimer->stop();
    }
}

void Sprite::nextframe() {
    //List de cle du json.
    QStringList frameCle = json.keys();

    if (frameCle.isEmpty()) {
        qDebug() << "Json pas trouver";
        return;
    }

    QString currentFrame = frameCle[currentframeindex];

    //stocker le data du current frame
    QJsonObject frameData = json.value(currentFrame).toObject();
    QJsonObject frameRect = frameData.value("frame").toObject();

    int x = frameRect.value("x").toInt();
    int y = frameRect.value("y").toInt();
    int width = frameRect.value("w").toInt();
    int height = frameRect.value("h").toInt();

    QPixmap frame = spritesheet.copy(x, y, width, height);

    pixmapItem.setPixmap(frame); //Mettre a jour le nouveau frame
    qDebug() << "switchingframes";

    currentframeindex = (currentframeindex + 1) % frameCle.size();
}

void Sprite::start(int vitesse) {
    spritetimer->start(vitesse);
}

Sprite::~Sprite() {
    if (spritetimer) {
        delete spritetimer;
    }
}


void Sprite::setframe(int index) {
    //List de cle du json.
    QStringList frameCle = json.keys();
    if (index < 0)
    {
        qDebug() << "ton index est trop petit";
        return;
    }
    if (index > frameCle.size())
    {
        qDebug() << "Le nombre de frame est" + frameCle.size() << "Ton index est trop grand" ;
        return;
    }

    if (frameCle.isEmpty()) {
        qDebug() << "Json pas trouver";
        return;
    }
    currentframeindex = index;
    QString currentFrame = frameCle[currentframeindex];


    //stocker le data du current frame
    QJsonObject frameData = json.value(currentFrame).toObject(); //chercher info for ton numero de frame
    QJsonObject frameRect = frameData.value("frame").toObject(); //stocker information de ton frame.

    int x = frameRect.value("x").toInt();
    int y = frameRect.value("y").toInt();
    int width = frameRect.value("w").toInt();
    int height = frameRect.value("h").toInt();

    QPixmap frame = spritesheet.copy(x, y, width, height);

    pixmapItem.setPixmap(frame); //Mettre a jour le nouveau frame
    qDebug() << "switchingframes";
}