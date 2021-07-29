#ifndef IMAGE_ADJUSTMENTS_H
#define IMAGE_ADJUSTMENTS_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QWidget>
#include <filesystem>

class image_adjustments
{
private:
    cv::Mat *_image;
    std::string _path;
    long _time_s;
    long _intensity;

public:
    //getter and setter
    cv::Mat *GetImageHandle() { return _image; }
    std::string GetPath() {return _path;}
    long GetTime() {return _time_s;}
    long GetIntensity() {return _intensity;}
    void SetImageHandle(cv::Mat *image) { _image=image; }
    void SetPath(std::string path) {_path=path;}
    void SetTime(long time_s) {_time_s=time_s;}
    void SetIntensity(long intensity) {_intensity=intensity;}


    image_adjustments(std::string path); //Constructor
    ~image_adjustments(); //Destructor
    image_adjustments(const image_adjustments &source); //Copy constructor
    image_adjustments &operator=(const image_adjustments &source); //copy assigment operator
    image_adjustments (image_adjustments &&source); //Move Constructor
    image_adjustments &operator=(image_adjustments &&source);// 5- Move assigment operator
    void crop_bw (int width_start, int height_start, int width_lenght, int heigh_lenght,bool save_img);
    QPixmap crop_preview (int width_start, int height_start, int width_lenght, int heigh_lenght);
    long intensity();
    long time_s();
};

#endif // IMAGE_ADJUSTMENTS_H
