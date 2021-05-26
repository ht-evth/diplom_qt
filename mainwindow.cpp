#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStandardItemModel"
#include "QStandardItem"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalheader;
    horizontalheader.append("Файл 1");
    horizontalheader.append("Файл 2");

    // Заголовки строк
    QStringList verticalheader;
    verticalheader.append("Количество классов");
    verticalheader.append("Количество вложенных классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество классов");

    model->setHorizontalHeaderLabels(horizontalheader);
    model->setVerticalHeaderLabels(verticalheader);

    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Button_Open_File_1_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    ui->lineEdit_File_1->setText(filename);
}

void MainWindow::on_Button_Open_File_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName();
    ui->lineEdit_File_2->setText(filename);
}
