#ifndef PHYSICSBALL_H
#define PHYSICSBALL_H

#include <QGraphicsEllipseItem>
#include <QPointF>
#include <QRandomGenerator>

class PhysicsBall : public QGraphicsEllipseItem {
public:
    PhysicsBall(const QPointF& pos, QGraphicsScene* scene);
    void advancePhysics(qreal deltaTime);

private:
    QPointF velocity;          // Вектор скорости
    QGraphicsScene* m_scene;   // Ссылка на сцену
    
    // Физические параметры
    const qreal gravity = 980.0;       // Гравитация (px/s²)
    const qreal restitution = 0.8;     // Коэффициент восстановления(упругость удара)
    const qreal friction = 0.99;       // Трение о поверхность
    const qreal minSpeed = 5.0;        // Минимальная скорость для остановки
    
    bool isStopped = false;            // Флаг остановки мяча
};

#endif // PHYSICSBALL_H
