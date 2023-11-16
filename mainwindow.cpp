#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <QLabel>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 600);
    currentColor = Qt::red;
    currentThickness = 1;

//Менб файл
    QAction *actionOpen = new QAction("Open", this);
    connect(actionOpen, &QAction::triggered, this, &MainWindow::openImage);
    QAction *actionClose_app = new QAction("Close", this);
    connect(actionClose_app, &QAction::triggered, this, &QMainWindow::close);
    QAction *actionSave = new QAction("Save", this);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveImage);
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(actionClose_app);
     fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);


    //Вібор пензля
    QRadioButton *kurl = new QRadioButton("Крива", this);
connect(kurl, &QRadioButton::clicked, this, &MainWindow::kurlClicked);


    QRadioButton *round = new QRadioButton("Коло", this);
connect(round, &QRadioButton::clicked, this, &MainWindow::roundClicked);
    QRadioButton *hexagon = new QRadioButton("Багатокутник", this);
connect(hexagon, &QRadioButton::clicked, this, &MainWindow::hexagonClicked);
    QRadioButton *conture = new QRadioButton("Контур", this);
//    QPushButton *submitBtn = new QPushButton("Submit", this);
//    connect(submitBtn, &QPushButton::clicked, this, &MainWindow::sumbitClicked);
     // Создание горизонтального layout для размещения радиокнопок
    QRadioButton *aerograph = new QRadioButton("Аерограф", this);
 connect(aerograph, &QRadioButton::clicked, this, &MainWindow::aerographClicked);


    // Создание кнопок Apply и Clear

    QPushButton *applyBtn = new QPushButton("Apply", this);
    QPushButton *clearBtn = new QPushButton("Clear", this);

    // Соединение кнопок с соответствующими слотами
    connect(applyBtn, &QPushButton::clicked, this, &MainWindow::applyChanges);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearChanges);
    QHBoxLayout *radioLayout = new QHBoxLayout();
   radioLayout->addWidget(kurl);
    radioLayout->addWidget(round);
    radioLayout->addWidget(hexagon);
    radioLayout->addWidget(conture);
    radioLayout->addWidget(aerograph);

//    radioLayout->addWidget(submitBtn);
    radioLayout->addWidget(applyBtn);
    radioLayout->addWidget(clearBtn);
 // Создание виджета для размещения layout в док-виджете
    QWidget *radioWidget = new QWidget();
    radioWidget->setLayout(radioLayout);
    QDockWidget *dockWidget = new QDockWidget("Options", this);
    dockWidget->setWidget(radioWidget);
    dockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
   /* dockWidget->setFloating(true);*/ // Устанавливаем флаг для отображения как отдельное окно

    addDockWidget(Qt::TopDockWidgetArea, dockWidget);



     QWidget *dockWidgetContent = new QWidget();

     // Создание layout'а для размещения элементов управления
     QVBoxLayout *dockLayout = new QVBoxLayout();
     dockWidgetContent->setLayout(dockLayout);

     colorComboBox = new QComboBox();
     colorComboBox->addItem("Red");
     colorComboBox->addItem("Green");
     colorComboBox->addItem("Blue");
     colorComboBox->addItem("Black");
     dockLayout->addWidget(colorComboBox);

     // Создание QSpinBox для выбора толщины линии
     thicknessSpinBox = new QSpinBox();
     thicknessSpinBox->setMinimum(1);
     thicknessSpinBox->setMaximum(10);
     thicknessSpinBox->setValue(1);
     dockLayout->addWidget(thicknessSpinBox);

     QPushButton *submitBtn = new QPushButton("Submit", this);
     connect(submitBtn, &QPushButton::clicked, this, &MainWindow::sumbitClicked);
     dockLayout->addWidget(submitBtn);

     QPixmap brushPreviewPixmap(50, 50);
     brushPreviewLabel = new QLabel();
     brushPreviewLabel->setFixedSize(50, 50); // Розмір попереднього перегляду
     dockLayout->addWidget(brushPreviewLabel);

//     if (currentRadioButton && currentRadioButton->text() == "Багатокутник") {
//         QPainter hexagonPainter(&brushPreviewPixmap);
//         hexagonPainter.setRenderHint(QPainter::Antialiasing, true);
//         hexagonPainter.setPen(QPen(Qt::blue, 2));

//         // Опрацювання шестикутника та малювання його на pixmap
//         QPolygon hexagon;
//         const int side = 20; // Змініть розмір шестикутника за потребою
//         const float pi = 3.14159f;
//         for (int i = 0; i < 6; ++i) {
//             hexagon << QPoint(side * cos(2 * pi * i / 6), side * sin(2 * pi * i / 6));
//         }
//         hexagonPainter.drawPolygon(hexagon);
//         hexagonPainter.end();
//     }




     // Создание и настройка док-панели
     QDockWidget *seconddockWidget = new QDockWidget("Brush Options", this);
     seconddockWidget->setWidget(dockWidgetContent);
     seconddockWidget->setAllowedAreas(Qt::TopDockWidgetArea);
     addDockWidget(Qt::TopDockWidgetArea, seconddockWidget);







//     // Создание layout'а для размещения кнопок под фото
//     QHBoxLayout *bottomLayout = new QHBoxLayout();
//     bottomLayout->addWidget(applyBtn);
//     bottomLayout->addWidget(clearBtn);

//     // Создание виджета для размещения layout'а внизу окна
//     QWidget *bottomWidget = new QWidget();
//     bottomWidget->setLayout(bottomLayout);

//     // Добавление виджета с кнопками под фото

//     layout()->addWidget(bottomWidget); // Добавление нижнего виджета с кнопками




//изображение
                                             img_label = new QLabel(this);
                                             setCentralWidget(img_label);





}




void MainWindow::sumbitClicked()
{
                                             if (img_label->isVisible()) {
                                                 // Получение текущего выбранного цвета из QComboBox
                                                 QString selectedColor = colorComboBox->currentText();

                                                 // Получение текущей выбранной толщины из QSpinBox
                                                 int selectedThickness = thicknessSpinBox->value();

                                                 // Применение значений цвета и толщины к переменным класса
                                                 if (selectedColor == "Red") {
                                                     currentColor = Qt::red;
                                                 } else if (selectedColor == "Green") {
                                                     currentColor = Qt::green;
                                                 } else if (selectedColor == "Blue") {
                                                     currentColor = Qt::blue;
                                                 } else if (selectedColor == "Black") {
                                                     currentColor = Qt::black;
                                                 }

                                                 currentThickness = selectedThickness;
                                             }



                                             if (currentRadioButton && currentRadioButton->text() == "Багатокутник") {
                                                 int previewSize = 50;
                                                 QPixmap tempPixmap(previewSize, previewSize);
                                                 tempPixmap.fill(Qt::white);

                                                 QPainter painter(&tempPixmap);
                                                 painter.setRenderHint(QPainter::Antialiasing);

                                                 painter.setPen(QPen(currentColor, currentThickness));
                                                 painter.setBrush(QBrush(currentColor)); // Встановлюємо заливку такою ж, як і контур

                                                 QPolygon hexagon;
                                                 const int side = 10 * currentThickness;
                                                 const float pi = 3.14159f;
                                                 for (int i = 0; i < 6; ++i) {
                                                     hexagon << QPoint(previewSize / 2 + side * cos(2 * pi * i / 6),
                                                                       previewSize / 2 + side * sin(2 * pi * i / 6));
                                                 }

                                                 painter.drawConvexPolygon(hexagon); // Малюємо багатокутник з заливкою

                                                 painter.end();

                                                 brushPreviewLabel->setPixmap(tempPixmap);
                                             }

                                             if (currentRadioButton && currentRadioButton->text() == "Коло") {
                                                 int previewSize = 50;
                                                 QPixmap tempPixmap(previewSize, previewSize);
                                                 tempPixmap.fill(Qt::white);

                                                 QPainter painter(&tempPixmap);
                                                 painter.setRenderHint(QPainter::Antialiasing);

                                                 painter.setPen(QPen(currentColor, currentThickness));
                                                 painter.setBrush(QBrush(currentColor));

                                                 int diameter = 10 * currentThickness;
                                                 int radius = diameter / 2;
                                                 painter.drawEllipse(previewSize / 2 - radius, previewSize / 2 - radius, diameter, diameter);

                                                 painter.end();

                                                 brushPreviewLabel->setPixmap(tempPixmap);
                                             }

                                             if (currentRadioButton && currentRadioButton->text() == "Аерограф") {
                                                 int previewSize = 50;
                                                 QPixmap tempPixmap(previewSize, previewSize);
                                                 tempPixmap.fill(Qt::white);

                                                 QPainter painter(&tempPixmap);
                                                 painter.setRenderHint(QPainter::Antialiasing);

                                                 painter.setPen(QPen(currentColor, currentThickness, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                                                 painter.setBrush(QBrush(currentColor));

                                                 int diameter = 10 * currentThickness; // Залежність від поточної товщини

                                                 // Малюємо статичний патерн аерографу
                                                 int numPoints = 20; // Кількість точок аерографу
                                                 for (int i = 0; i < numPoints; ++i) {
                                                     int xOffset = QRandomGenerator::global()->bounded(-diameter / 2, diameter / 2);
                                                     int yOffset = QRandomGenerator::global()->bounded(-diameter / 2, diameter / 2);

                                                     QPoint sprayPoint(previewSize / 2 + xOffset, previewSize / 2 + yOffset);

                                                     painter.drawEllipse(sprayPoint, currentThickness, currentThickness);
                                                 }

                                                 painter.end();

                                                 brushPreviewLabel->setPixmap(tempPixmap);
                                             }





}


//QString MainWindow::colorChanged(const QString &colorName) {
//                                             // Обновление текущего цвета при выборе нового значения в QComboBox
//                                             if (colorName == "Red") {
//                                                 currentColor = Qt::red;
//                                             } else if (colorName == "Green") {
//                                                 currentColor = Qt::green;
//                                             } else if (colorName == "Blue") {
//                                                 currentColor = Qt::blue;
//                                             } else if (colorName == "Black") {
//                                                 currentColor = Qt::black;
//                                             }
//                                             return colorName;
//}



//int MainWindow::thiknessChanged(int value) {
//                                             // Обновление текущей толщины при изменении значения в QSpinBox
//                                             currentThickness = value;
//                                             return currentThickness;
//}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
                                             if (isDrawing && isMousePress && currentRadioButton && currentRadioButton->text() == "Крива") {
                                                 if (!img_label->pixmap().isNull()) {
                                                     QPixmap pixmap = img_label->pixmap().copy();
                                                     QPainter painter(&pixmap);

                                                     // Получение корректированных координат для рисования линии выше на 20 пикселей
                                                     QPoint correctedPos = img_label->mapFrom(this, event->pos());
                                                     correctedPos.setY(correctedPos.y() - 0); // Смещение вверх на 20 пикселей

                                                     // Установка цвета и толщины линии для рисования
                                                     painter.setPen(QPen(currentColor, currentThickness));
                                                     painter.drawLine(lastPoint, correctedPos);

                                                     img_label->setPixmap(pixmap);
                                                     lastPoint = correctedPos; // Сохранение новой позиции
                                                 }
                                             }
}












void MainWindow::mousePressEvent(QMouseEvent *event)
{
                                             //ПЕНЗЕЛЬ
                                             if (isDrawing && event->button() == Qt::LeftButton && currentRadioButton && currentRadioButton->text() == "Крива") {
                                                 if (!img_label->pixmap().isNull()) {
                                                     QPoint globalPos = event->globalPos();
                                                     QPoint labelPos = img_label->mapToGlobal(img_label->pos());
                                                     if (globalPos.x() >= labelPos.x() && globalPos.y() >= labelPos.y()-230) {
                                                         QPoint adjustedPos = img_label->mapFromGlobal(globalPos);
                                                         adjustedPos.setY(adjustedPos.y() - 0); // Смещение вверх на 20 пикселей
                                                         lastPoint = adjustedPos;
                                                         isMousePress = true;
                                                     }
                                                 }
                                             }

                                             //КОЛО
     if (currentRadioButton && currentRadioButton->text() == "Коло") {
        if (!img_label->pixmap().isNull()) {
            QPixmap tempPixmap = img_label->pixmap();
            QPainter painter(&tempPixmap);

            painter.setPen(QPen(currentColor, 10 * currentThickness));

            // Получение корректированных координат для рисования круга выше на 20 пикселей
            QPoint clickPos = img_label->mapFromGlobal(event->globalPos());
            clickPos.setY(clickPos.y() - 0); // Смещение вверх на 20 пикселей

            painter.drawEllipse(clickPos, 5 * currentThickness, 5 * currentThickness);

            img_label->setPixmap(tempPixmap);
        }
     }




     //ШЕСТИКУННЫК
     if (currentRadioButton && currentRadioButton->text() == "Багатокутник") {
        if (!img_label->pixmap().isNull()) {
            QPixmap tempPixmap = img_label->pixmap();
            QPainter painter(&tempPixmap);

            painter.setPen(Qt::NoPen);
            painter.setBrush(currentColor);

            QPoint clickPos = img_label->mapFromGlobal(event->globalPos());
            clickPos.setY(clickPos.y() - 0); // Зміщення на 70 пікселів вище

            const int sideLength = 10 * currentThickness;

            // Створення шестикутника
            QPolygon hexagon;
            for (int i = 0; i < 6; ++i) {
                                                         double angle = 60.0 * i + 30.0;
                                                         double radian = M_PI / 180 * (angle + 90.0); // Поворот на 90 градусів

                                                         hexagon << QPoint(clickPos.x() + sideLength * cos(radian),
                                                                           clickPos.y() + sideLength * sin(radian));
            }

            painter.drawPolygon(hexagon);

            img_label->setPixmap(tempPixmap);
        }
     }


     if (currentRadioButton && currentRadioButton->text() == "Аерограф") {
        if (!img_label->pixmap().isNull()) {
            QPixmap tempPixmap = img_label->pixmap();
            QPainter painter(&tempPixmap);

            // Отримання кольору пензля
            QColor brushColor = currentColor;

            // Встановлення кольору для аерографа
            QBrush brush(brushColor, Qt::SolidPattern);
            painter.setBrush(brush);

            // Розмір краплинки для аерографа
            int diameter = 10 * currentThickness; // Залежність від поточної товщини

            // Малюємо випадкові точки з вибраним кольором
            int numPoints = 20; // Кількість точок аерографу
            for (int i = 0; i < numPoints; ++i) {
                                                         int xOffset = QRandomGenerator::global()->bounded(-diameter / 2, diameter / 2);
                                                         int yOffset = QRandomGenerator::global()->bounded(-diameter / 2, diameter / 2);

                                                         QPoint sprayPoint = img_label->mapFromGlobal(event->globalPos());
                                                         sprayPoint.setX(sprayPoint.x() + xOffset);
                                                         sprayPoint.setY(sprayPoint.y() + yOffset-0);

                                                         painter.drawEllipse(sprayPoint, currentThickness, currentThickness);
            }

            painter.end();

            img_label->setPixmap(tempPixmap);
        }
     }



}

//void MainWindow::mouseMoveEvent(QMouseEvent *event) {
//                                             if (isDrawing && isMousePress && currentRadioButton && currentRadioButton->text() == "Крива") {
//                                                 if (!img_label->pixmap().isNull()) {
//                                                     QPixmap pixmap = img_label->pixmap().copy();
//                                                     QPainter painter(&pixmap);

//                                                     // Установка цвета и толщины линии для рисования
//                                                     painter.setPen(QPen(currentColor, currentThickness));
//                                                     painter.drawLine(lastPoint, img_label->mapFromGlobal(event->globalPos()));

//                                                     img_label->setPixmap(pixmap);
//                                                     lastPoint = img_label->mapFromGlobal(event->globalPos());
//                                                 }
//                                             }
//}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
                                             if (isDrawing && event->button() == Qt::LeftButton && currentRadioButton && currentRadioButton->text() == "Крива") {
                                                 isMousePress = false;
//                                                 editedImage = img_label->setPixmap(pixmap);
                                             }


}

void MainWindow::kurlClicked()
{
                                             currentRadioButton = qobject_cast<QRadioButton *>(sender());
                                             if (currentRadioButton) {
                                                 if (currentRadioButton->text() == "Крива")
                                                {
                                                     isDrawing = true;
                                                 }

                                                 else{isDrawing = false;}

}
}


void MainWindow::aerographClicked()
{
currentRadioButton = qobject_cast<QRadioButton *>(sender());
if (currentRadioButton) {
                                                 if (currentRadioButton->text() == "Аерограф")
                                                {
                                                     isDrawing = true;
                                                 }

                                                 else{isDrawing = false;}

}
}


void MainWindow::roundClicked()
{
currentRadioButton = qobject_cast<QRadioButton *>(sender());
if (currentRadioButton) {
                                                 if (currentRadioButton->text() == "Коло")
                                                {
                                                     isDrawing = true;
                                                 }

                                                 else{isDrawing = false;}

}
}

void MainWindow::hexagonClicked()
{
currentRadioButton = qobject_cast<QRadioButton *>(sender());
if (currentRadioButton) {
                                                 if (currentRadioButton->text() == "Багатокутник")
                                                {
                                                     isDrawing = true;
                                                 }

                                                 else{isDrawing = false;}

}
}







void MainWindow::openImage() {
                                             QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
                                             if (!filePath.isEmpty()) {
                                                 originalImage = QImage(filePath);

                                                 if (!originalImage.isNull()) {
                                                     // Максимальные размеры для отображаемого изображения
                                                     int maxWidth = 600;
                                                     int maxHeight = 450;

                                                     // Масштабирование изображения до максимальных размеров, сохраняя пропорции
                                                     originalImage = originalImage.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio);
//                                                    editedImage = originalImage;
                                                     // Отображение оригинального изображения
                                                     QPixmap pixmap = QPixmap::fromImage(originalImage);
                                                     img_label->setPixmap(pixmap);
                                                 }
                                             }
}


void MainWindow::applyChanges() {
                                             // Получение текущего QPixmap из QLabel
                                             QPixmap currentPixmap = img_label->pixmap();

                                             // Сохранение текущего изображения в editedImage (если оно существует)
                                             if (!currentPixmap.isNull()) {
                                                 originalImage = currentPixmap.toImage();

                                                 // Настройка рисования на editedImage, добавление линий, цветов и толщин в соответствии с вашей реализацией рисования
                                                 // ...

                                                 // Обновление изображения в окне
                                                 img_label->setPixmap(QPixmap::fromImage(originalImage));
                                             }
}




// Метод сброса изменений и возврата к оригиналу
void MainWindow::clearChanges() {
                                             // Восстановление копии к оригиналу
                                             editedImage = originalImage;

                                             // Обновление изображения в окне
                                             QPixmap pixmap = QPixmap::fromImage(originalImage);
                                             img_label->setPixmap(pixmap);
}



void MainWindow::saveImage()
{
                                             QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
                                             if (!filePath.isEmpty()) {
                                                 if (!originalImage.isNull()) {
                                                     bool saved = originalImage.save(filePath); // Сохраняем текущее изображение на диск
                                                     if (saved) {
                                                         qDebug() << "Изображение успешно сохранено!";
                                                     } else {
                                                         qDebug() << "Ошибка сохранения изображения!";
                                                     }
                                                 } else {
                                                     qDebug() << "Нет изображения для сохранения!";
                                                 }
                                             }
}







MainWindow::~MainWindow()
{
    delete ui;
}

