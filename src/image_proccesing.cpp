#include "image_proccesing.h"
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

}
