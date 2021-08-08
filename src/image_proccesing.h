#ifndef IMAGE_PROCCESING_H
#define IMAGE_PROCCESING_H

#include <QWidget>
#include <QFileDialog>
#include <filesystem>
#include <map>
#include <tuple>
#include "qcustomplot.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <chrono>
#include <mutex>


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
    void parallel_process(std::vector<std::string> &fnames, std::multimap<std::string, std::tuple<double, double>> &data_summary, unsigned int start, unsigned int end);

private slots:
    void on_browse_btn_clicked();

    void on_crop_btn_clicked();

    void on_process_images_btn_clicked();

   // void on_qwtPlot_itemAttached(QwtPlotItem *plotItem, bool on);

private:
    Ui::Image_Proccesing *ui;

};
#endif // IMAGE_PROCCESING_H
