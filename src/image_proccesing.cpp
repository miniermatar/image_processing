#include "image_proccesing.h"
#include "image_adjustments.h"
#include "./ui_image_proccesing.h"


Image_Proccesing::Image_Proccesing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Image_Proccesing)
{
    ui->setupUi(this);

}

Image_Proccesing::~Image_Proccesing()
{
    delete ui;
}

void Image_Proccesing::save_file(std::multimap<std::string, std::tuple<double, double>> data) {
    std::ofstream intensityfile;
    intensityfile.open (ui->path->text().toUtf8() + "/intensity.csv");
    intensityfile<< "File Name,time_sec,intensity,\n";
    for (std::multimap<std::string, std::tuple<double, double>>::iterator it = data.begin(); it != data.end(); it++) {
        intensityfile<< it->first <<","<< std::get<0>(it->second)<<","<<std::get<1>(it->second)<< "\n";
    }
    intensityfile.close();

}

std::vector<std::string> Image_Proccesing::path_list (QString directory)
{

    std::vector<std::string> fnames;
    if (!directory.isEmpty()) {
        std::string path = directory.toUtf8().constData();
        for (const auto & entry : std::filesystem::directory_iterator(path)) {
            fnames.emplace_back(entry.path());
        }
        std::sort(fnames.begin(), fnames.end());

    }
    return fnames;
}

void Image_Proccesing::on_browse_btn_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Folder"),
    "/home/",
    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        ui->path->setText(directory);
    }
    std::vector<std::string> fnames=path_list(ui->path->text());
    QPixmap pix(fnames.at(0).c_str());
    ui->image_preview->setPixmap(pix);
    int w = ui->image_preview->width();
    int h = ui->image_preview->height();
    ui->image_preview->setPixmap (pix.scaled (w,h,Qt::KeepAspectRatio));
    ui->width_start->setMaximum(pix.width());
    ui->width_start->setValue(0);
    ui->width_end->setMaximum(pix.width());
    ui->width_end->setValue(pix.width());
    ui->height_start->setMaximum(pix.height());
    ui->height_start->setValue(0);
    ui->height_end->setMaximum(pix.height());
    ui->height_end->setValue(pix.height());
}

void Image_Proccesing::on_crop_btn_clicked()
{
    std::vector<std::string> fnames=path_list(ui->path->text());
//    QString path = ;
//    std::string path_text = path.toUtf8().constData();
    image_adjustments data(fnames.at(0).c_str());
    QPixmap pix=data.crop_preview (ui->width_start->value(),ui->height_start->value(),ui->width_end->value()-ui->width_start->value(),ui->height_end->value()-ui->height_start->value());
    ui->image_preview->setPixmap(pix);
    int w = ui->image_preview->width();
    int h = ui->image_preview->height();
    ui->image_preview->setPixmap (pix.scaled (w,h,Qt::KeepAspectRatio));

}

void Image_Proccesing::on_process_images_btn_clicked()
{
    std::vector<std::string> fnames=path_list(ui->path->text());
    std::multimap<std::string, std::tuple<double, double>> summary;
<<<<<<< HEAD
    auto start = std::chrono::system_clock::now();
=======
>>>>>>> 01054b30b5aa3bea332b60a3566693b887901e1e
    for (auto i = fnames.begin(); i != fnames.end(); ++i)
    {
        std::filesystem::path p(*i);
            if (p.extension()==".jpeg" || p.extension()==".jpg" || p.extension()==".png" || p.extension()==".tiff") {

            std::cout<<"Processing image: "<<*i<<std::endl;
            image_adjustments data(*i);
            data.crop_bw (ui->width_start->value(),ui->height_start->value(),ui->width_end->value()-ui->width_start->value(),ui->height_end->value()-ui->height_start->value(),ui->save_crop->isChecked());

            double intensity=data.intensity();
            double time_s=data.time_s();

            summary.insert(make_pair(*i, std::make_tuple(time_s, intensity)));
        }
    }
<<<<<<< HEAD
    std::chrono::duration<double> dur= std::chrono::system_clock::now() - start;
    std::cout << "Time for processing " << dur.count() << " seconds" << std::endl;
    //std::cout<<std::to_string(intensity)<<"\n";
    //std::cout<<std::to_string(time_s)<<"\n";

    QVector<double> x,y;
    int i=0;
    for (std::multimap<std::string, std::tuple<double, double>>::iterator it = summary.begin(); it != summary.end(); it++) {
        //std::cout << it->first << " :: " << std::get<0>(it->second) << " :: " << std::get<1>(it->second) << std::endl;
        x.push_back((std::get<0>(it->second))/(60));
        y.push_back(std::get<1>(it->second));
    }
    if (ui->save_data->isChecked()) {
        save_file(summary);
        std::cout<<"Data file saved as: "<<ui->path->text().toStdString()<< "/intensity.csv"<< std::endl;

    }

=======
    //std::cout<<std::to_string(intensity)<<"\n";
    //std::cout<<std::to_string(time_s)<<"\n";
    QVector<double> x,y;
    int i=0;
    for (std::multimap<std::string, std::tuple<double, double>>::iterator it = summary.begin(); it != summary.end(); it++) {
        std::cout << it->first << " :: " << std::get<0>(it->second) << " :: " << std::get<1>(it->second) << std::endl;
        x.push_back((std::get<0>(it->second))/(60));
        y.push_back(std::get<1>(it->second));
    }
>>>>>>> 01054b30b5aa3bea332b60a3566693b887901e1e
    double x_max = *std::max_element(x.constBegin(), x.constEnd());
    double y_max = *std::max_element(y.constBegin(), y.constEnd());
    double x_min = *std::min_element(x.constBegin(), x.constEnd());
    double y_min = *std::min_element(y.constBegin(), y.constEnd());

    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Time, min");
    ui->customPlot->yAxis->setLabel("Intensity");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, x_max*1.1);
    ui->customPlot->yAxis->setRange(y_min*0.9, y_max*1.1);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->customPlot->replot();
}
