#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PhysicsBall; // Предварительное объявление

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void updatePhysics();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QTimer* physicsTimer;
    qint64 lastUpdateTime;
};

#endif // MAINWINDOW_H
