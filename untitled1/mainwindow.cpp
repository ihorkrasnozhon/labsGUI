#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
//#include <QMessageBox>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setValue(8);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    int vvod = ui->textEdit->toPlainText().toInt();
    int comboBoxIndex = ui->comboBox->currentIndex();
    int comboBox2Index = ui->comboBox_2->currentIndex();
    QLabel *label1 = ui->label_2;
    //std::cout << 'vvod';
    //QMessageBox::information(this, "111" ,vvod); //рабботает




    //ДЛИНЫ
    if (comboBoxIndex == 0)
    {
        if(comboBox2Index == 0)
        {
            label1->setText(QString::number(vvod));
        }
        if(comboBox2Index == 1)
        {
            label1->setText(QString::number(vvod*0.621371));
        }
        if(comboBox2Index == 2)
        {
            label1->setText(QString::number(vvod*39370.1));
        }
    }
    if (comboBoxIndex == 1)
    {
        if(comboBox2Index == 1)
        {
            label1->setText(QString::number(vvod));
        }
        if(comboBox2Index == 0)
        {
            label1->setText(QString::number(vvod*1.60934));
        }
        if(comboBox2Index == 2)
        {
            label1->setText(QString::number(vvod*63360));
        }
    }
    if (comboBoxIndex == 2)
    {
        if(comboBox2Index == 2)
        {
            label1->setText(QString::number(vvod));
        }
        if(comboBox2Index == 0)
        {
            label1->setText(QString::number(vvod*0.0000254));
        }
        if(comboBox2Index == 1)
        {
            label1->setText(QString::number(vvod/63360));
        }
    }


}

//ВЕСА

void MainWindow::on_pushButton_2_clicked()
{
    QLabel *label2 = ui->label_4;
    int vvod = ui->textEdit_2->toPlainText().toInt();
    if(ui->radioButton->isChecked())
    {label2->setText(QString::number(vvod*2.20462));}
    else
    {label2->setText(QString::number(vvod*0.45359));}

}






//CLEAR

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->label_2->setText("Тут будет ответ");
    ui->label_4->setText("Тут будет ответ");

}






//INVERT

void MainWindow::on_checkBox_stateChanged(int arg1)
{

    QString comboBoxText = ui->comboBox->currentText();
    QString comboBox2Text = ui->comboBox_2->currentText();

    ui->comboBox->setCurrentText(comboBox2Text);
    ui->comboBox_2->setCurrentText(comboBoxText);


}


//РАЗМНР ТЕКСТА
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->label->setFont(QFont("Arial", arg1));
    ui->label_2->setFont(QFont("Arial", arg1));
    ui->label_3->setFont(QFont("Arial", arg1));
    ui->label_4->setFont(QFont("Arial", arg1));
}

