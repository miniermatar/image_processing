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


void Image_Proccesing::on_browse_btn_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Folder"),
    "/home",
    QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        ui->path->setText(directory);
        QPixmap pix(directory+"/0001776.jpeg");
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
}

void Image_Proccesing::on_crop_btn_clicked()
{
    QString path = ui->path->text() + "/0001776.jpeg";
    std::string path_text = path.toUtf8().constData();
    image_adjustments data(path_text);
    QPixmap pix=data.crop_preview (ui->width_start->value(),ui->height_start->value(),ui->width_end->value()-ui->width_start->value(),ui->height_end->value()-ui->height_start->value());
    ui->image_preview->setPixmap(pix);
    int w = ui->image_preview->width();
    int h = ui->image_preview->height();
    ui->image_preview->setPixmap (pix.scaled (w,h,Qt::KeepAspectRatio));

}

void Image_Proccesing::on_process_images_btn_clicked()
{
    std::string path = ui->path->text().toUtf8().constData();
    std::vector<std::string> fnames;
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        fnames.emplace_back(entry.path());
    }
    std::sort(fnames.begin(), fnames.end());




}
