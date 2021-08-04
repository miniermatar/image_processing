#include "image_proccesing.h"
#include "image_adjustments.h"
#include "./ui_image_proccesing.h"

std::mutex myMutex;
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
        ui->crop_btn->setEnabled(true);
        ui->process_images_btn->setEnabled(true);
        ui->save_crop->setEnabled(true);
        ui->save_data->setEnabled(true);
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->data()->clear();
        ui->customPlot->replot();
    }
    else
        std::cout << directory.toStdString() << " is empty. Select another directory";
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

    static const unsigned int NUM_THREADS = std::thread::hardware_concurrency();
    unsigned int filesperthread = fnames.size()/NUM_THREADS;
    std::thread threads[NUM_THREADS];
    auto start = std::chrono::system_clock::now();
    for(unsigned int i = 0 ; i < NUM_THREADS; ++i)
        {
            unsigned int end;
            if (i==NUM_THREADS-1)
                end = fnames.size();
            else
                end = (i+1)*filesperthread;
            threads[i] = std::thread(&Image_Proccesing::parallel_process, this, std::ref(fnames), std::ref(summary), i*filesperthread,end);
        }
    for(unsigned int i = 0 ; i < NUM_THREADS ; ++i)
    {
        threads[i].join();
    }

    std::chrono::duration<double> dur= std::chrono::system_clock::now() - start;
    std::cout << "Time for processing: " << dur.count() << " seconds" << " with "<< NUM_THREADS << " threads"<< std::endl;
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

    double x_max = *std::max_element(x.constBegin(), x.constEnd());
    double y_max = *std::max_element(y.constBegin(), y.constEnd());
    double x_min = *std::min_element(x.constBegin(), x.constEnd());
    double y_min = *std::min_element(y.constBegin(), y.constEnd());
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

void Image_Proccesing::parallel_process(std::vector<std::string> &fnames, std::multimap<std::string, std::tuple<double, double>> &data_summary, unsigned int start, unsigned int end) {

    for (int i = start; i != end; ++i)
    {
        std::filesystem::path p(fnames[i]);
            if (p.extension()==".jpeg" || p.extension()==".jpg" || p.extension()==".png" || p.extension()==".tiff") {

            std::cout<<"Processing image: "<<fnames[i]<<std::endl;
            image_adjustments data(fnames[i]);
            data.crop_bw (ui->width_start->value(),ui->height_start->value(),ui->width_end->value()-ui->width_start->value(),ui->height_end->value()-ui->height_start->value(),ui->save_crop->isChecked());

            double intensity=data.intensity();
            double time_s=data.time_s();
            std::lock_guard<std::mutex> myLock(myMutex);
            data_summary.insert(make_pair(fnames[i], std::make_tuple(time_s, intensity)));
        }
    }
}

