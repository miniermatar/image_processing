#include "image_adjustments.h"

image_adjustments::image_adjustments()
{

}

QPixmap image_adjustments::crop (QString path,int width_start, int width_end, int height_start, int height_end) {
    cv::Mat image;
    std::string path_text = path.toUtf8().constData();
    image=cv::imread(path_text);
    //Input for the program
    cv::Rect crop_region(width_start, width_end, height_start, height_end);
    // specifies the region of interest in Rectangle form
    image=image(crop_region);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
   // cv::imshow("cropped image ",image);
   // cv::waitKey(0);
    return QPixmap::fromImage(QImage((unsigned char*) image.data, image.cols, image.rows, image.step,QImage::Format_RGB888));
}
