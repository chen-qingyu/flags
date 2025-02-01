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

    static const MainWindow* instance();

public slots:
    void updateDesc(const QString& text);
    void clearDesc();

private slots:
    void drawChinaFlag();
    void drawAmericaFlag();
    void drawJapanFlag();
    void drawRussiaFlag();
    void drawUkraineFlag();

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    QLabel* name;
    QLabel* desc;

    static MainWindow* window;
};

#endif // MAINWINDOW_H
