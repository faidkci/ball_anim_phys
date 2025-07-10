#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "physicsball.h"

#include <QMouseEvent>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем сцену с границами
    scene = new QGraphicsScene(0, 0, 800, 600, this);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect(), QPen(Qt::black));

    // Таймер для физики
    physicsTimer = new QTimer(this);
    connect(physicsTimer, &QTimer::timeout, this, &MainWindow::updatePhysics);
    lastUpdateTime = QDateTime::currentMSecsSinceEpoch();
    physicsTimer->start(16); // ~60 FPS

    // Установка фильтра событий для обработки кликов
    ui->graphicsView->viewport()->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (watched == ui->graphicsView->viewport() &&
        event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            QPointF scenePos = ui->graphicsView->mapToScene(mouseEvent->pos());
            PhysicsBall* ball = new PhysicsBall(scenePos, scene);
            scene->addItem(ball);
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updatePhysics() {
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qreal deltaTime = (currentTime - lastUpdateTime) / 1000.0;
    lastUpdateTime = currentTime;

    // Обновляем физику всех мячей
    for (QGraphicsItem* item : scene->items()) {
        if (PhysicsBall* ball = dynamic_cast<PhysicsBall*>(item)) {
            ball->advancePhysics(deltaTime);
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
