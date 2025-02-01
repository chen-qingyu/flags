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
    void drawJapanFlag();
    void drawRussiaFlag();

    void updateDesc(const QString& text);
    void clearDesc();

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QLabel* name;
    QLabel* desc;
};

#endif // MAINWINDOW_H
