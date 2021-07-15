#ifndef IMAGE_PROCCESING_H
#define IMAGE_PROCCESING_H

#include <QWidget>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Image_Proccesing; }
QT_END_NAMESPACE

class Image_Proccesing : public QWidget
{
    Q_OBJECT

public:
    Image_Proccesing(QWidget *parent = nullptr);
    ~Image_Proccesing();

private slots:
    void on_browse_btn_clicked();

    void on_crop_btn_clicked();

private:
    Ui::Image_Proccesing *ui;
};
#endif // IMAGE_PROCCESING_H
