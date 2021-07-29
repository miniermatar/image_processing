#ifndef IMAGE_PROCCESING_H
#define IMAGE_PROCCESING_H

#include <QWidget>
#include <QFileDialog>
#include <filesystem>
#include <map>
#include <tuple>
#include <qcustomplot.h>
#include <algorithm>
<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include <chrono>
=======
>>>>>>> 01054b30b5aa3bea332b60a3566693b887901e1e


QT_BEGIN_NAMESPACE
namespace Ui { class Image_Proccesing; }
QT_END_NAMESPACE

class Image_Proccesing : public QWidget
{
    Q_OBJECT

public:
    Image_Proccesing(QWidget *parent = nullptr);
    ~Image_Proccesing();
    std::vector<std::string> path_list (QString directory);
    void save_file(std::multimap<std::string, std::tuple<double, double>> data);

private slots:
    void on_browse_btn_clicked();

    void on_crop_btn_clicked();

    void on_process_images_btn_clicked();

   // void on_qwtPlot_itemAttached(QwtPlotItem *plotItem, bool on);

private:
    Ui::Image_Proccesing *ui;

};
#endif // IMAGE_PROCCESING_H
