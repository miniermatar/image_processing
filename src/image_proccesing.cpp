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
    image_adjustments data(fnames.at(0));
    data.crop_bw (ui->width_start->value(),ui->height_start->value(),ui->width_end->value()-ui->width_start->value(),ui->height_end->value()-ui->height_start->value());
    long intensity=data.intensity();
    long time_s=data.time_s();
    std::multimap<std::string, std::tuple<long, long>> summary;
    summary.insert(make_pair(fnames.at(0), std::make_tuple(time_s, intensity)));
    std::cout<<std::to_string(intensity)<<"\n";
    std::cout<<std::to_string(time_s)<<"\n";
    for (std::multimap<std::string, std::tuple<long, long>>::iterator it = summary.begin(); it != summary.end(); it++)
        std::cout << it->first << " :: " << std::get<0>(it->second) << " :: " << std::get<1>(it->second) << std::endl;

}
