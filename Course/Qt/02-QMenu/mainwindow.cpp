#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(600, 400);


    // 状态栏
    auto stBar = statusBar();
    setStatusBar(stBar);

    auto labelLeft = new QLabel("提示");
    stBar->addWidget(labelLeft);

    auto labelRight = new QLabel("右侧提示");
    stBar->addPermanentWidget(labelRight);

    // 菜单栏
    auto bar = menuBar();
    setMenuBar(bar);

    auto fileMenu = bar->addMenu("文件");
    auto editMenu = bar->addMenu("编辑");

    auto createAction = fileMenu->addAction("新建");
    connect(createAction, &QAction::triggered, [=](){
        labelLeft->setText("点击新建按钮");
    });
    fileMenu->addSeparator();
    auto openAction = fileMenu->addAction("打开");

    auto toolBar = new QToolBar();
    addToolBar(Qt::LeftToolBarArea, toolBar);
    toolBar->setFloatable(false);
    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    toolBar->addAction(createAction);
    toolBar->addAction(openAction);

    // 浮动窗口，可以有多个
    QDockWidget * floatWidget = new QDockWidget("浮动窗口1", this);
    addDockWidget(Qt::LeftDockWidgetArea, floatWidget);
    floatWidget->setAllowedAreas(Qt::LeftDockWidgetArea);

    QTextEdit * text = new QTextEdit(this);
    setCentralWidget(text);
}

MainWindow::~MainWindow()
{
}

