#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QStandardItemModel"
#include "QStandardItem"
#include "string"

#include <QMessageBox>
#include <iostream>

#include "ClassSyntax.h"

// считываем файл
std::string ReadFile(QString filename)
{
    std::string text;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    if (file.isOpen() == false)
    {
        QMessageBox error("Ошибка открытия файла!", "Файл не был открыт!", QMessageBox::Icon::Critical, QMessageBox::Button::Ok, 0, 0);
        error.exec();
        return "";
    }

    text = std::string(file.readAll());

    //std::cout << text;
    return text;

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
    std::string text_1 = ReadFile(ui->lineEdit_File_1->text());
    std::string text_2 = ReadFile(ui->lineEdit_File_2->text());

    ClassSyntax syntax_1(text_1);
    int* result_syntax_1 = syntax_1.Prog();


}
