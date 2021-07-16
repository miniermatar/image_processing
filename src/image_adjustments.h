#ifndef IMAGE_ADJUSTMENTS_H
#define IMAGE_ADJUSTMENTS_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QWidget>

class image_adjustments
{
public:
    image_adjustments();
    QPixmap crop (QString path, int width_start, int width_end, int height_start, int height_end);
};

#endif // IMAGE_ADJUSTMENTS_H
