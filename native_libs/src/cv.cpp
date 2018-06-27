#include <cstdlib>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>

#ifdef _WIN32
#define EXPORTDLL __declspec(dllexport)
#else
#define EXPORTDLL
#endif

extern "C"
{
EXPORTDLL void *lunaCV_cv_mat(int w, int h, int cvType, void *data)
{
    cv::Mat *a = new cv::Mat(cv::Size(w,h), cvType, data);
    return static_cast<void*>(a);
}

EXPORTDLL void lunaCV_free_mat(void *mat)
{
    auto mat_new = static_cast<cv::Mat*>(mat);
    delete mat_new;
}

EXPORTDLL unsigned char *lunaCV_mat_data(void *mat)
{
    auto mat_new = static_cast<cv::Mat*>(mat);
    return mat_new->data;
}

EXPORTDLL int lunaCV_mat_rows(void *mat)
{
    auto mat_src = static_cast<cv::Mat*>(mat);
    auto s = mat_src->rows;
    return s;
}

EXPORTDLL int lunaCV_mat_cols(void *mat)
{
    auto mat_src = static_cast<cv::Mat*>(mat);
    auto s = mat_src->cols;
    return s;
}

EXPORTDLL void lunaCV_cvtColor( void *src, void *dst, int code)
{
    auto mat_src = static_cast<cv::Mat*>(src);
    auto mat_dst = static_cast<cv::Mat*>(dst);
    cv::cvtColor(*mat_src, *mat_dst, code);
}

EXPORTDLL void lunaCV_equalizeHist( void *src, void *dst)
{
    auto mat_src = static_cast<cv::Mat*>(src);
    auto mat_dst = static_cast<cv::Mat*>(dst);
    cv::equalizeHist(*mat_src, *mat_dst);
}

EXPORTDLL void lunaCV_cascade_classifier_delete(void *cascade_classifier)
 {
    auto cascade_classifier_new = static_cast<cv::CascadeClassifier*>(cascade_classifier);
    delete cascade_classifier_new;
 }

EXPORTDLL void *lunaCV_cascade_classifier_load(const char *file_name, int *ok)
{
    cv::CascadeClassifier *a = new cv::CascadeClassifier(std::string(file_name));
    if (a->empty()) {*ok = 1; delete a; return nullptr;} else {*ok = 0; return a;}
}

EXPORTDLL int *lunaCV_cascade_classifier_detect_multiscale(void *img, void *face_cascade, double scale_factor,
    int minNeighbors, int flags, int minW, int minH, int maxW, int maxH, int *faces, char **error)
{
    try
    {
        auto mat_img = static_cast<cv::Mat*>(img);
        std::vector<cv::Rect> objects;
        auto face_cascade_classifier = static_cast<cv::CascadeClassifier*>(face_cascade);
        face_cascade_classifier->detectMultiScale(*mat_img, objects, scale_factor, minNeighbors, flags, cv::Size(minW,minH), cv::Size(maxW, maxH));
        *faces = objects.size();
        int* data = new int[sizeof(cv::Rect)*objects.size()];
        std::memcpy(data, objects.data(), objects.size()*sizeof(cv::Rect));
        *error = nullptr;
        return data;
    }
    catch(const std::exception &exc)
    {
        *error = strdup(exc.what());
        return nullptr;
    }

}

EXPORTDLL void lunaCV_rectangle(void *img, int x, int y, int w, int h, double r, double g, double b, double a)
{
    auto mat_img = static_cast<cv::Mat*>(img);
    cv::rectangle(*mat_img, cv::Point(x,y), cv::Point(w,h), cv::Scalar(b,g,r,a), 3);
}

EXPORTDLL void lunaCV_imwrite(void *img, const char *file_name)
{
    auto mat_img = static_cast<cv::Mat*>(img);
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(3);
    cv::imwrite(std::string(file_name), *mat_img, compression_params);
}


}
