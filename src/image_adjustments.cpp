#include "image_adjustments.h"

// Constructor WITH memory allocation
image_adjustments::image_adjustments(std::string path)
{
    _path=path;
    _image =  new cv::Mat(cv::imread(_path));
    _time_s=0;
    _intensity=0;
}

//1 - Destructor
image_adjustments::~image_adjustments()
{
    if(_image != nullptr) // Attention: wxWidgets used NULL and not nullptr
    {
        delete _image;
        _image = nullptr;
    }
    _path="";
    _time_s=0;
    _intensity=0;
}
// 2- Copy Constructor
image_adjustments::image_adjustments(const image_adjustments &source)
{
    _path=source._path;
    _time_s=source._time_s;
    _intensity=source._intensity;
    _image = new cv::Mat(cv::imread(_path));
}

// 3- Copy assigment operator
image_adjustments &image_adjustments::operator=(const image_adjustments &source)
{
    if (this == &source)
        return *this;
    delete _image;
    _path=source._path;
    _time_s=source._time_s;
    _intensity=source._intensity;
    _image = new cv::Mat(cv::imread(_path));
    return *this;
}
// 4- Move Constructor
image_adjustments::image_adjustments(image_adjustments &&source)
{
    _path=source._path;
    _time_s=source._time_s;
    _intensity=source._intensity;
    _image = source._image;
    source._path="";
    source._time_s=0;
    source._intensity=0;
    source._image=nullptr;
}
// 5- Move assigment operator
image_adjustments &image_adjustments::operator=(image_adjustments &&source)
{
    if (this == &source)
        return *this;
    delete _image;
    _path=source._path;
    _time_s=source._time_s;
    _intensity=source._intensity;
    _image = source._image;
    source._path="";
    source._time_s=0;
    source._intensity=0;
    source._image=nullptr;
    return *this;
}

QPixmap image_adjustments::crop_preview (int width_start, int height_start, int width_lenght, int heigh_lenght) {
    cv::Rect crop_region(width_start, height_start, width_lenght, heigh_lenght);
    *_image=(*_image)(crop_region);
    cv::cvtColor(*_image, *_image, cv::COLOR_BGR2RGB);
    return QPixmap::fromImage(QImage((unsigned char*) _image->data, _image->cols, _image->rows, _image->step,QImage::Format_RGB888));
}

