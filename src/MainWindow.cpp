#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);
    this->resize(800, 600);

    QHBoxLayout* hlayout = new QHBoxLayout();
    auto buttons = std::vector{
        std::pair{new QPushButton("China"), &MainWindow::drawChinaFlag},
        std::pair{new QPushButton("America"), &MainWindow::drawAmericaFlag},
    };
    for (int i = 0; i < buttons.size(); i++)
    {
        hlayout->addWidget(buttons[i].first);
        connect(buttons[i].first, &QPushButton::clicked, this, buttons[i].second);
    }
    layout->addLayout(hlayout);

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    name = new QLabel("");
    name->setAlignment(Qt::AlignCenter);
    auto font = name->font();
    font.setBold(true);
    font.setPointSize(14);
    name->setFont(font);
    layout->addWidget(name);

    elem = new QLabel("");
    layout->addWidget(elem);
}

void MainWindow::drawChinaFlag()
{
    name->setText("The Flag of the People's Republic of China");
    elem->setText("stars");
}

void MainWindow::drawAmericaFlag()
{
    name->setText("The Flag of the United States of America");
    elem->setText("red and white stripes");
}
