#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "RectItem.h"
#include "StarItem.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);
    this->resize(1280, 800);

    QHBoxLayout* hlayout = new QHBoxLayout();
    auto buttons = QList{
        std::pair{new QPushButton("中国国旗"), &MainWindow::drawChinaFlag},
        std::pair{new QPushButton("美国国旗"), &MainWindow::drawAmericaFlag},
    };
    for (int i = 0; i < buttons.size(); i++)
    {
        hlayout->addWidget(buttons[i].first);
        connect(buttons[i].first, &QPushButton::clicked, this, buttons[i].second);
    }
    layout->addLayout(hlayout);

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setAlignment(Qt::AlignCenter);
    view->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(view);

    name = new QLabel("");
    name->setAlignment(Qt::AlignCenter);
    auto font = name->font();
    font.setBold(true);
    font.setPointSize(14);
    name->setFont(font);
    layout->addWidget(name);

    desc = new QLabel("");
    desc->setFixedHeight(16);
    layout->addWidget(desc);
}

// 依据中华人民共和国国家标准GB 12982-2004《国旗》和 https://en.wikipedia.org/wiki/Flag_of_China 绘制五星红旗。
void MainWindow::drawChinaFlag()
{
    scene->clear();
    name->setText("五星红旗");

    // 以标准国旗尺寸纵向30/横向20等分方格边长为一个单位
    const int WIDTH = 30;  // 旗面宽度
    const int HEIGHT = 20; // 旗面高度

    // 五角星中心点 (Center) 坐标 (以场景坐标轴为准：原点为中心，X轴向右，Y轴向下)
    QList<QPointF> C = {
        {-10, -5}, // 主星中心点
        {-5, -8},  // 纵向第一个小五角星中心点
        {-3, -6},  // 纵向第二个小五角星中心点
        {-3, -3},  // 纵向第三个小五角星中心点
        {-5, -1},  // 纵向第四个小五角星中心点
    };

    // 五角星外接圆半径 (Radius)
    QList R = {3, 1, 1, 1, 1};

    // 五角星上顶点过该五角星中心到主星中心的连线与y轴负方向的顺时针夹角弧度 (Angle)
    QList A = {
        0.0,
        M_PI_2 + qAtan2(3.0, -5.0),
        M_PI_2 + qAtan2(1.0, -7.0),
        M_PI_2 + qAtan2(-2.0, -7.0),
        M_PI_2 + qAtan2(-4.0, -5.0),
    };

    // 颜色 https://www.schemecolor.com/peoples-republic-of-china-flag-colors.php
    QMap<QString, QString> colors = {{"Maximum Red", "#DE2910"}, {"Golden Yellow", "#FFDE00"}};

    RectItem* rect = new RectItem(QPointF(0, 0), WIDTH, HEIGHT, colors["Maximum Red"], "红色旗面象征革命");
    connect(rect, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
    connect(rect, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
    scene->addItem(rect);

    QList desc = {
        "大五角星象征中国共产党",
        "第一颗小五角星象征工人阶级",
        "第二颗小五角星象征农民阶级",
        "第三颗小五角星象征城市小资产阶级",
        "第四颗小五角星象征民族资产阶级",
    };
    for (int i = 0; i < C.size(); i++)
    {
        StarItem* star = new StarItem(C[i], R[i], colors["Golden Yellow"], A[i], desc[i]);
        connect(star, &StarItem::mouseEntered, this, &MainWindow::updateDesc);
        connect(star, &StarItem::mouseLeft, this, &MainWindow::clearDesc);
        scene->addItem(star);
    }

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::drawAmericaFlag()
{
    scene->clear();

    name->setText("The Flag of the United States of America");
    desc->setText("red and white stripes");

    scene->update();
}

void MainWindow::updateDesc(const QString& text)
{
    desc->setText(text);
}

void MainWindow::clearDesc()
{
    desc->clear();
}
