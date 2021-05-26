#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStandardItemModel"
#include "QStandardItem"
#include "string"

#include <QMessageBox>
#include <QList>
#include <iostream>
#include <QtMath>

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

    QList<int> results_class = Class.Prog();
    QList<int> results_cycle = Cycle.Prog();
    QList<int> results_block = Block.Prog();
    QList<int> results_name = Name.Prog();

    if (results_class.size())
        for (int i = 0; i < results_class.size(); i++)
            results.append(results_class.at(i));

    if (results_cycle.size())
        for (int i = 0; i < results_cycle.size(); i++)
            results.append(results_cycle.at(i));

    if (results_block.size())
        for (int i = 0; i < results_block.size() ; i++)
            results.append(results_block.at(i));

    if (results_name.size())
        for (int i = 0; i < results_name.size(); i++)
            results.append(results_name.at(i));

    return results;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateTable(nullptr, nullptr);

}

void MainWindow::UpdateTable(QList<int>* metrics_1 = nullptr, QList<int>* metrics_2 = nullptr)
{
    QStandardItemModel *model = new QStandardItemModel;

    //Заголовки столбцов
    QStringList horizontalheader;
    horizontalheader.append("Файл 1");
    horizontalheader.append("Файл 2");

    // Заголовки строк
    QStringList verticalheader;
    verticalheader.append("Количество классов");
    verticalheader.append("Количество вложенных классов");
    verticalheader.append("Макс. уровень вложенности классов");
    verticalheader.append("Общая длина классов");
    verticalheader.append("Общее число методов классов");
    verticalheader.append("Общее число классов-потомков (наследников)");

    verticalheader.append("Количество циклов");
    verticalheader.append("Количество вложенных циклов");
    verticalheader.append("Макс. уровень вложенности циклов");
    verticalheader.append("Общая длина циклов");
    verticalheader.append("Общее операторов continue");
    verticalheader.append("Общее операторов break/return");

    verticalheader.append("Количество блоков");
    verticalheader.append("Количество вложенных блоков");
    verticalheader.append("Макс. уровень вложенности блоков");
    verticalheader.append("Общая длина блоков");


    verticalheader.append("Количество объявленных переменных");
    verticalheader.append("Количество используемых переменных");
    verticalheader.append("Количество неиспользуемых переменных");
    verticalheader.append("Общее число использований переменных");


    model->setHorizontalHeaderLabels(horizontalheader);
    model->setVerticalHeaderLabels(verticalheader);

    if (metrics_1 != nullptr && metrics_2 != nullptr)
    {
        for(int row = 0; row < metrics_1->size(); row++)
        {
            QList<QStandardItem*> lst;
            QStandardItem* item_1 = new QStandardItem(row,0);
            QStandardItem* item_2 = new QStandardItem(row,1);
            item_1->setText(QString::number(metrics_1->at(row)));
            item_2->setText(QString::number(metrics_2->at(row)));
            item_1->setTextAlignment(Qt::AlignCenter);
            item_2->setTextAlignment(Qt::AlignCenter);
            lst << item_1 << item_2;
            model->setItem(row, 0, item_1);
            model->setItem(row, 1, item_2);
        }
    }

    ui->tableView->setModel(model);
}

// максимум из двух чисел
int max_int(int a, int b)
{
    return ((a) > (b) ? (a) : (b));
}

// для округления результата
float roundTo(float inpValue, int inpCount)
{


    double outpValue;
    double tempVal;
    tempVal=inpValue*pow(10,inpCount);
    if (float(int(tempVal))+0.5==tempVal)
    {
        if (int(tempVal)%2==0)
            outpValue=float(qFloor(tempVal))/pow(10,inpCount);
        else
            outpValue=float(qCeil(tempVal))/pow(10,inpCount);
    }
    else
    {
        if (double(int(tempVal))+0.5>tempVal)
            outpValue=float(qCeil(tempVal))/pow(10,inpCount);
        else
            outpValue=float(qFloor(tempVal))/pow(10,inpCount);
    }
    return(outpValue);
}

void MainWindow::CalulateResult(QList<int> metrics_1, QList<int> metrics_2)
{
    //d(m1, m2) =  abs(m1-m2)/max(m1,m2)
    QList<float> temp;

    // вычислить коэф-ты
    for (int i = 0; i < metrics_1.size(); i++)
        if (max_int(metrics_1.at(i), metrics_2.at(i)) != 0)
            temp.append((float)abs(metrics_1.at(i)- metrics_2.at(i))/ max_int(metrics_1.at(i), metrics_2.at(i)));

    if (temp.size())
    {
        float sum = 0;
        for (float value : temp)
            sum += value;

        float result = (1 - (sum / temp.size())) * 100;

        ui->label_result->setText("Процент совпадения метрик: " + QString::number(roundTo(result, 4)) + "%");
    }
    else
       ui->label_result->setText("Все метрики равны нулю!");


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

    UpdateTable(&metrics_1, &metrics_2);
    CalulateResult(metrics_1, metrics_2);

}
