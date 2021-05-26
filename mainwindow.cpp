#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStandardItemModel"
#include "QStandardItem"
#include "string"

#include <QMessageBox>
#include <QList>
#include <iostream>

#include "ClassSyntax.h"
#include "BlockSyntax.h"
#include "CyclesSyntax.h"
#include "NameSyntax.h"


#define MAX_METRICS_CLASS 6
#define MAX_METRICS_BLOCK 6
#define MAX_METRICS_CYCLE 4
#define MAX_METRICS_NAME 4

// считываем файл
std::string* ReadFile(QString filename)
{
    std::string* text;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    if (file.isOpen() == false)
        return nullptr;


    text = new std::string(file.readAll());

    //std::cout << text;
    return text;

}


// считываем файл
QList<int> GetMetrics(std::string filename)
{
    QList<int> results;

    ClassSyntax Class(filename);
    BlockSyntax Block(filename);
    CyclesSyntax Cycle(filename);
    NameSyntax Name(filename);

    int* results_class = Class.Prog();
    int* results_block = Block.Prog();
    int* results_cycle = Cycle.Prog();
    int* results_name = Name.Prog();

    if (results_class != nullptr)
        for (int i = 0; i < MAX_METRICS_CLASS; i++)
            results.append(results_class[i]);

    if (results_class != nullptr)
        for (int i = 0; i < MAX_METRICS_BLOCK; i++)
            results.append(results_block[i]);

    if (results_class != nullptr)
        for (int i = 0; i < MAX_METRICS_CYCLE; i++)
            results.append(results_cycle[i]);

    if (results_class != nullptr)
        for (int i = 0; i < MAX_METRICS_NAME; i++)
            results.append(results_name[i]);

    return results;
}




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel;

    //Заголовки столбцов
    QStringList horizontalheader;
    horizontalheader.append("Файл 1");
    horizontalheader.append("Файл 2");

    // Заголовки строк
    QStringList verticalheader;
    verticalheader.append("Классы");
    verticalheader.append("Количество классов");
    verticalheader.append("Количество вложенных классов");
    verticalheader.append("Макс. уровень вложенности классов");
    verticalheader.append("Общая длина классов");
    verticalheader.append("Общее число методов классов");
    verticalheader.append("Общее число классов-потомков (наследников)");

    verticalheader.append("Циклы");
    verticalheader.append("Количество циклов");
    verticalheader.append("Количество вложенных циклов");
    verticalheader.append("Макс. уровень вложенности циклов");
    verticalheader.append("Общая длина циклов");
    verticalheader.append("Общее операторов continue");
    verticalheader.append("Общее операторов break/return");

    verticalheader.append("Блоки");
    verticalheader.append("Количество блоков");
    verticalheader.append("Количество вложенных блоков");
    verticalheader.append("Макс. уровень вложенности блоков");
    verticalheader.append("Общая длина блоков");

    verticalheader.append("Имена");
    verticalheader.append("Количество объявленных переменных");
    verticalheader.append("Количество используемых переменных");
    verticalheader.append("Количество неиспользуемых переменных");
    verticalheader.append("Общее число использований переменных");


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

void MainWindow::on_Button_Start_clicked()
{
    std::string* text_1 = ReadFile(ui->lineEdit_File_1->text());
    std::string* text_2 = ReadFile(ui->lineEdit_File_2->text());


    if (text_1 == nullptr || text_2 == nullptr)
    {
        QString error_message = "";
        if (text_1 == nullptr)
            error_message += "Файл 1 не был открыт!";
        if (text_2 == nullptr)
            error_message += "\nФайл 2 не был открыт!";

        QMessageBox error("Ошибка открытия файла!", error_message, QMessageBox::Icon::Critical, QMessageBox::Button::Ok, 0, 0);
        error.exec();
        return;
    }


    QList<int> metrics_1 = GetMetrics(*text_1);
    QList<int> metrics_2 = GetMetrics(*text_2);



}
