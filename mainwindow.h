#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qcombobox.h"
#include "qradiobutton.h"
#include "qspinbox.h"
#include <QMainWindow>
#include <QLabel>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void openImage();
    void saveImage();
    void kurlClicked();
    void sumbitClicked();
    void applyChanges();
    void clearChanges();
    void roundClicked();
    void hexagonClicked();
    void aerographClicked();
 /*   QColor currentColor;
    int currentThickness*/;


private:
    Ui::MainWindow *ui;
    QLabel *img_label;
    QImage currentImage;
    bool isDrawing = false; // Переменная для отслеживания рисования
    bool isMousePress = false;
    QPoint lastPoint;
    QRadioButton *currentRadioButton = nullptr;
    QComboBox *colorComboBox;
    QSpinBox *thicknessSpinBox;
    QColor currentColor;
    int currentThickness;
    QImage originalImage;
    QImage editedImage;
    QPixmap currentPixmap;
    QLabel *brushPreviewLabel;
    QPixmap brushPreviewPixmap;


};
#endif // MAINWINDOW_H
