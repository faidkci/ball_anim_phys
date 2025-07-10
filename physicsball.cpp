#include "physicsball.h"
#include "qgraphicsscene.h"
#include <QDateTime>
#include <QPainter>

PhysicsBall::PhysicsBall(const QPointF& pos, QGraphicsScene* scene)
    : m_scene(scene)
{
    const int size = 20;
    setRect(0, 0, size, size);
    setPos(pos - QPointF(size/2, size/2));
    
    // Случайный цвет
    setBrush(QBrush(QColor::fromRgb(QRandomGenerator::global()->bounded(256),
                            QRandomGenerator::global()->bounded(256),
                            QRandomGenerator::global()->bounded(256))));

    // Случайная начальная скорость
    qreal speed = QRandomGenerator::global()->bounded(150.0) + 50.0; // 50-200 px/s
    qreal angle = QRandomGenerator::global()->bounded(2 * M_PI);     // Случайное направление
    
    velocity = QPointF(speed * cos(angle), speed * sin(angle));
}

void PhysicsBall::advancePhysics(qreal deltaTime) {
    if (isStopped) return;

    // Применяем гравитацию
    velocity.setY(velocity.y() + gravity * deltaTime);
    
    // Рассчитываем новую позицию
    QPointF newPos = pos() + velocity * deltaTime;
    
    // Границы сцены
    QRectF sceneRect = m_scene->sceneRect();
    qreal left = sceneRect.left();
    qreal right = sceneRect.right() - rect().width();
    qreal top = sceneRect.top();
    qreal bottom = sceneRect.bottom() - rect().height();

    // Столкновение с нижней границей
    if (newPos.y() >= bottom) {
        newPos.setY(bottom);
        velocity.setY(-velocity.y() * restitution);
        velocity.setX(velocity.x() * friction);
    } 
    // Столкновение с верхней границей
    else if (newPos.y() <= top) {
        newPos.setY(top);
        velocity.setY(-velocity.y() * restitution);
    }

    // Столкновение с боковыми границами
    if (newPos.x() <= left) {
        newPos.setX(left);
        velocity.setX(-velocity.x() * restitution);
    } else if (newPos.x() >= right) {
        newPos.setX(right);
        velocity.setX(-velocity.x() * restitution);
    }

    setPos(newPos);
    
    // Проверка на остановку
    if (velocity.manhattanLength() < minSpeed) {
        isStopped = true;
        velocity = QPointF(0, 0);
    }
}
