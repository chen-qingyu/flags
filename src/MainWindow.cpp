#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "CircleItem.h"
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
        std::pair{new QPushButton("日本国旗"), &MainWindow::drawJapanFlag},
        std::pair{new QPushButton("俄罗斯国旗"), &MainWindow::drawRussiaFlag},
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
    const QList<QPointF> C = {
        {-10, -5}, // 主星中心点
        {-5, -8},  // 纵向第一个小五角星中心点
        {-3, -6},  // 纵向第二个小五角星中心点
        {-3, -3},  // 纵向第三个小五角星中心点
        {-5, -1},  // 纵向第四个小五角星中心点
    };

    // 五角星外接圆半径 (Radius)
    const QList R = {3, 1, 1, 1, 1};

    // 五角星上顶点过该五角星中心到主星中心的连线与y轴负方向的顺时针夹角弧度 (Angle)
    const QList A = {
        0.0,
        M_PI_2 + qAtan2(3.0, -5.0),
        M_PI_2 + qAtan2(1.0, -7.0),
        M_PI_2 + qAtan2(-2.0, -7.0),
        M_PI_2 + qAtan2(-4.0, -5.0),
    };

    // 颜色 https://www.schemecolor.com/peoples-republic-of-china-flag-colors.php
    const QMap<QString, QString> COLOR = {{"Maximum Red", "#DE2910"}, {"Golden Yellow", "#FFDE00"}};

    RectItem* rect = new RectItem(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, COLOR["Maximum Red"], "红色旗面象征革命");
    connect(rect, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
    connect(rect, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
    scene->addItem(rect);

    const QList descs = {
        "大五角星象征中国共产党",
        "第一颗小五角星象征工人阶级",
        "第二颗小五角星象征农民阶级",
        "第三颗小五角星象征城市小资产阶级",
        "第四颗小五角星象征民族资产阶级",
    };
    for (int i = 0; i < C.size(); i++)
    {
        StarItem* star = new StarItem(C[i], R[i], COLOR["Golden Yellow"], A[i], descs[i]);
        connect(star, &StarItem::mouseEntered, this, &MainWindow::updateDesc);
        connect(star, &StarItem::mouseLeft, this, &MainWindow::clearDesc);
        scene->addItem(star);
    }

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

// 依据 https://en.wikipedia.org/wiki/Flag_of_the_United_States 绘制美国国旗。
void MainWindow::drawAmericaFlag()
{
    scene->clear();
    name->setText("美利坚合众国国旗");

    // 以标准国旗尺寸纵向38/横向20等分方格边长为一个单位
    const int WIDTH = 38;  // 旗面宽度
    const int HEIGHT = 20; // 旗面高度

    // 条纹 (Stripe) 高度 (Height)
    const qreal S_H = HEIGHT / 13.0;

    // 蓝色横幅 (Banner) 部分
    const qreal B_W = WIDTH * (2.0 / 5.0);   // 宽度 (Width)
    const qreal B_H = HEIGHT * (7.0 / 13.0); // 高度 (Height)
    const qreal B_V = B_W / 12.0;            // 纵向 (Vertical) 等分线
    const qreal B_T = B_H / 10.0;            // 横向 (Transverse) 等分线

    // 横纵等分线交点 (Intersection)
    QList<QPointF> B_I;
    int cnt = 0;
    for (qreal y = B_T; y < B_H; y += B_T)
    {
        for (qreal x = B_V; x < B_W; x += B_V)
        {
            if (++cnt % 2 == 1)
            {
                B_I.append(QPointF(-WIDTH / 2 + x, -HEIGHT / 2 + y));
            }
        }
    }

    // 五角星外接圆半径 (Radius)
    const qreal R = 0.0616 * HEIGHT / 2;

    // 颜色 https://www.schemecolor.com/united-states-of-america-flag-colors.php
    const QMap<QString, QString> COLOR = {{"American Blue", "#3C3B6E"}, {"White", "#FFFFFF"}, {"American Red", "#B22234"}};

    for (int i = 0; i < 13; i++)
    {
        RectItem* rect = new RectItem(-WIDTH / 2, -HEIGHT / 2 + S_H * i, WIDTH, S_H, COLOR[i % 2 ? "White" : "American Red"], (i % 2 ? "白色代表纯洁和天真" : "红色代表坚韧和勇敢"));
        connect(rect, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
        connect(rect, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
        scene->addItem(rect);
    }

    RectItem* banner = new RectItem(-WIDTH / 2, -HEIGHT / 2, B_W, B_H, COLOR["American Blue"], "蓝色代表警惕、毅力和正义");
    connect(banner, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
    connect(banner, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
    scene->addItem(banner);

    for (auto c : B_I)
    {
        StarItem* star = new StarItem(c, R, COLOR["White"], 0, "50颗白星象征50个州");
        connect(star, &StarItem::mouseEntered, this, &MainWindow::updateDesc);
        connect(star, &StarItem::mouseLeft, this, &MainWindow::clearDesc);
        scene->addItem(star);
    }

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

// 依据 https://en.wikipedia.org/wiki/Flag_of_Japan 绘制日本国旗。
void MainWindow::drawJapanFlag()
{
    scene->clear();
    name->setText("日章旗");

    const int WIDTH = 30;  // 旗面宽度
    const int HEIGHT = 20; // 旗面高度

    // 中心圆半径 (Radius)
    const qreal R = HEIGHT * (3.0 / 5.0) / 2.0;

    // 颜色 https://www.schemecolor.com/japan-flag-colors.php
    const QMap<QString, QString> COLOR = {{"White", "#FFFFFF"}, {"Crimson Glory", "#BC002D"}};

    RectItem* rect = new RectItem(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, COLOR["White"], "白色衬底象征着纯洁");
    connect(rect, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
    connect(rect, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
    scene->addItem(rect);

    CircleItem* circle = new CircleItem(QPointF(0, 0), R, COLOR["Crimson Glory"], "红日居中象征着忠诚");
    connect(circle, &CircleItem::mouseEntered, this, &MainWindow::updateDesc);
    connect(circle, &CircleItem::mouseLeft, this, &MainWindow::clearDesc);
    scene->addItem(circle);

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

// 依据 https://en.wikipedia.org/wiki/Flag_of_Russia 绘制俄罗斯国旗。
void MainWindow::drawRussiaFlag()
{
    scene->clear();
    name->setText("俄罗斯联邦国旗");

    const int WIDTH = 30;  // 旗面宽度
    const int HEIGHT = 20; // 旗面高度

    // 颜色 https://www.schemecolor.com/russia-flag-colors.php
    const QList<QPair<QString, QString>> COLOR = {{"White", "#FFFFFF"}, {"Dark Powder Blue", "#0033A0"}, {"Maximum Red", "#DA291C"}};

    const QList descs = {
        "白色代表寒带，一年四季白雪飘飘，象征着无限的自由",
        "蓝色代表亚寒带，象征着俄罗斯丰富的自然资源",
        "红色代表温带，象征着俄罗斯对整个人类文明的贡献",
    };
    for (int i = 0; i < 3; i++)
    {
        RectItem* rect = new RectItem(-WIDTH / 2.0, -HEIGHT / 2.0 + i * HEIGHT / 3.0, WIDTH, HEIGHT / 3.0, COLOR[i].second, descs[i]);
        connect(rect, &RectItem::mouseEntered, this, &MainWindow::updateDesc);
        connect(rect, &RectItem::mouseLeft, this, &MainWindow::clearDesc);
        scene->addItem(rect);
    }

    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::updateDesc(const QString& text)
{
    desc->setText(text);
}

void MainWindow::clearDesc()
{
    desc->clear();
}
