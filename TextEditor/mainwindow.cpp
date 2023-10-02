#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>

QString currentFilePath = "";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont defaultFont("Arial", 10);
    ui->textEdit->setFont(defaultFont);
    ui->doubleSpinBox->setValue(10.0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_2_triggered()
{
    // Открыть файл и установить currentFilePath
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть текстовый файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");

    if (!filePath.isEmpty())
    {
        currentFilePath = filePath;
        QFile file(filePath);
        QTextStream in(&file);
        QString fileContents = in.readAll();
        //file.close();
        ui->textEdit->setText(fileContents);
    }
}


void MainWindow::on_action_3_triggered()
{
     ui->textEdit->clear();
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть текстовый файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");
                                               //родитель //текст диалогового окна //дир //форматы файлов
    if (!filePath.isEmpty())
    {
        QFile file(filePath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            QString fileContents = in.readAll();
            file.close();
            ui->textEdit->setText(fileContents);
        }
        else
        {
            qDebug() << "Ошибка при открытии файла";
        }
    }
    currentFilePath = filePath;
}


void MainWindow::on_action_4_triggered()
{
    if (!currentFilePath.isEmpty())
    {
        QFile file(currentFilePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            // Получить текст из QTextEdit
            QString textToSave = ui->textEdit->toPlainText();

            // Записать текст в файл
            QTextStream out(&file);
            out << textToSave;

            file.close();
        }
    }
    else
        {
            // Обработка ошибки при открытии файла для записи
            qDebug() << "Ошибка при открытии файла для записи";
        }
}


void MainWindow::on_action_5_triggered()
{
        QString textToSave = ui->textEdit->toPlainText();

        // Запрашиваем у пользователя новое имя и расположение файла для сохранения
        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить файл как", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");

        if (!filePath.isEmpty())
        {
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
            // Записываем текст в новый файл
            QTextStream out(&file);
            out << textToSave;

            file.close();
            }
            else
            {
            // Обработка ошибки при открытии нового файла для записи
            qDebug() << "Ошибка при открытии файла для записи";
            }
        }
        currentFilePath = filePath;
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
        // Получаем текущий шрифт из QTextEdit
        QFont currentFont = ui->textEdit->font();

        // Устанавливаем размер шрифта в соответствии с новым значением из QDoubleSpinBox
        currentFont.setPointSizeF(arg1);

        // Устанавливаем новый шрифт в QTextEdit
        ui->textEdit->setFont(currentFont);
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
        int comboBoxIndex = ui->comboBox->currentIndex();
        if(comboBoxIndex==0)
        {
            ui->textEdit->setTextColor(Qt::black);
        }
        if(comboBoxIndex==1)
        {
            ui->textEdit->setTextColor(Qt::red);
        }
        if(comboBoxIndex==2)
        {
            ui->textEdit->setTextColor(Qt::green);
        }
        if(comboBoxIndex==3)
        {
            ui->textEdit->setTextColor(Qt::blue);
        }
}




void MainWindow::on_pushButton_clicked()
{
   QString text = ui->textEdit->toPlainText();
   QStringList words = text.split(' ', Qt::SkipEmptyParts);
   for (int i = 0; i < words.size(); i+=i+2)
   {
            if (!words.isEmpty())
            {
            words[i][0] = words[i][0].toUpper();
            }

   }
   QString newText = words.join(' ');
   ui->textEdit->setPlainText(newText);
}


void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    ui->textEdit->setFont(arg1);
}

