#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void drawChinaFlag();
    void drawAmericaFlag();

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QLabel* name;
    QLabel* elem;
};

#endif // MAINWINDOW_H
