// test.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>

// Google C++ Style Guide
// https://google.github.io/styleguide/cppguide.html

//#define TEST_DLL
#define TEST_OPENCV

#ifdef TEST_DLL
#include "test_dll.h"
#endif

#ifdef TEST_OPENCV
//#pragma warning(disable : 4996)	// use unsafe function.

#include <opencv2/opencv.hpp>

#include <fstream>
#include <algorithm>

#define TEST_OPENCV_MATRIX
#define TEST_OPENCV_MATRIX_GDIPLUS
//#define TEST_OPENCV_VIDEO
//#define TEST_OPENCV_VIDEO_OUTPUT_FRAME
//#define TEST_OPENCV_VIDEO_OUTPUT_VIDEO
//#define TEST_OPENCV_VIDEO_OUTPUT_VIDEO_FRAME_CONVERSION

#ifdef TEST_OPENCV_MATRIX_GDIPLUS
#include <windows.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")
#endif
#endif

int main(int argc, char* argv[])
{
#if defined TEST_DLL
    test::DllClass test;
    auto v = test.Test();
    std::cout << "Test value is " << v << std::endl;
#elif defined TEST_OPENCV
    std::cout << "OpenCV " << CV_VERSION << std::endl;

    std::ofstream ofs("BuildInformation.txt");
    if (!ofs.bad())
        ofs << cv::getBuildInformation() << std::endl;
    ofs.close();

#ifdef TEST_OPENCV_MATRIX
    // Create Matrix.
    {
        auto rows = 3;
        auto cols = 3;
        auto type = CV_8UC1; // 8U, C1 = bit depth: uchar, channels: 1
        // type = CV_<bit depth>C<channels>
        // <bit depth> : [ 8 | 16 | 32 | 64 ][ U | S | F ]
        // <channels>  : [ 1 | 2 | 3 | 4 | (?) ]

#if 1
        cv::Mat mat(rows, cols, type);
#else
        cv::Mat mat;
        mat.create(rows, cols, type);
#endif
        std::cout << "mat" << std::endl;
        std::cout << ".rows=" << mat.rows << std::endl;
        std::cout << ".cols=" << mat.cols << std::endl;
        std::cout << ".dims=" << mat.dims << std::endl; // >= 2
        std::cout << ".type()=" << mat.type() << std::endl;
        std::cout << ".depth()=" << mat.depth() << std::endl;
        std::cout << ".channels()=" << mat.channels() << std::endl;
        std::cout << ".size()=" << mat.size() << ", size.dims()=" << mat.size.dims() << std::endl;
        std::cout << ".total()=" << mat.total() << std::endl;

        std::cout << "mat=" << std::endl;
        std::cout << mat << std::endl;

        uchar data1[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
        };
        cv::Mat mat1(rows, cols, type, data1);  // not copy array.
        std::cout << "mat1=" << std::endl;
        std::cout << mat1 << std::endl;

        cv::Mat mat2 = (cv::Mat_<uchar>(rows, cols) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
        std::cout << "mat2=" << std::endl;
        std::cout << mat2 << std::endl;

#if 1
#if 1
        // more better.
#if 1
        cv::Mat mat3(rows, cols, type, cv::Scalar_<uchar>(5));
#else
        cv::Mat mat3(cv::Size(cols, rows), type, cv::Scalar_<uchar>(5));
#endif
#else
#if 0
        cv::Mat mat3(rows, cols, type, 5);
#else
        // expected constructor is not called.
        cv::Mat mat3(cv::Size(cols, rows), type, 5);
#endif
#endif
#else
        cv::Mat mat3(rows, cols, type);
        mat3 = 5;
#endif
        std::cout << "mat3=" << std::endl;
        std::cout << mat3 << std::endl;

#if 1
        cv::Mat mat4(rows, cols, CV_8UC3, cv::Scalar(0, 0, 255));
#else
        cv::Mat mat4(rows, cols, CV_8UC3);
        mat4 = cv::Scalar(0, 0, 255);
#endif
        std::cout << "mat4=" << std::endl;
        std::cout << mat4 << std::endl;

#if 0
        cv::Mat mat5({ 3, 3, }, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
#else
        cv::Mat mat5({ 3, 3, }, std::initializer_list<uchar>{ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
        // error...
        //cv::Mat mat5 = cv::Mat::Mat<uchar>({ 3, 3, }, { 1, 2, 3, 4, 5, 6, 7, 8, 9 });
#endif
        std::cout << "mat5=" << std::endl;
        std::cout << mat5 << std::endl;

        std::array<uchar, 9> data6 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        cv::Mat mat6(data6, false); // select copy array or not.
        // 9 x 1
        std::cout << "mat6=" << std::endl;
        std::cout << mat6 << std::endl;

        cv::Mat mat7(mat2); // not copy array.
        std::cout << "mat7=" << std::endl;
        std::cout << mat7 << std::endl;

        cv::Mat mat8;
        mat2.assignTo(mat8);    // not copy array.
        std::cout << "mat8=" << std::endl;
        std::cout << mat8 << std::endl;

        cv::Mat mat9(mat.size(), CV_MAKETYPE(mat.depth(), 2));  // 2 channels.
        std::cout << "mat9=" << std::endl;
        std::cout << ".rows=" << mat9.rows << std::endl;
        std::cout << ".cols=" << mat9.cols << std::endl;
        std::cout << ".type()=" << mat9.type() << std::endl;
        std::cout << ".depth()=" << mat9.depth() << std::endl;
        std::cout << ".channels()=" << mat9.channels() << std::endl;

        cv::Mat mat10;
        mat2.copyTo(mat10);    // copy array.
        std::cout << "mat10=" << std::endl;
        std::cout << mat10 << std::endl;

        cv::Mat mat11 = mat2.clone();    // copy array.
        std::cout << "mat11=" << std::endl;
        std::cout << mat11 << std::endl;

        // Zero matrix
        cv::Mat zeros = cv::Mat::zeros(3, 3, CV_8UC1);  // return cv::MatExpr
        std::cout << "zeros=" << std::endl;
        std::cout << zeros << std::endl;

        // Identity matrix
#if 1
        cv::Mat eye = cv::Mat::eye(3, 3, CV_8UC1);      // return cv::MatExpr
#else
        cv::Mat eye(3, 3, CV_8UC1);
        cv::setIdentity(eye);
#endif
        std::cout << "eye=" << std::endl;
        std::cout << eye << std::endl;

        // All ones matrix
        cv::Mat ones = cv::Mat::ones(3, 3, CV_8UC1);    // return cv::MatExpr
        std::cout << "ones=" << std::endl;
        std::cout << ones << std::endl;

        // Diagonal matrix
        cv::Mat diag = cv::Mat::diag(cv::Mat(5, 1, CV_8UC1, 5));
        std::cout << "diag=" << std::endl;
        std::cout << diag << std::endl;
    }
    {
        // 3 x 3 x 3 (3 dimensions)
        auto dims = 3;
        const int sizes[] = { 3, 3, 3 };
        auto type = CV_8UC1; // 8U, C1 = bit depth: uchar, channels: 1

#if 1
        cv::Mat mat(dims, sizes, type, 5);
#else
        cv::Mat mat(dims, sizes, type);
        mat = 5;
#endif

        std::cout << "mat" << std::endl;
        std::cout << ".rows=" << mat.rows << std::endl; // -1
        std::cout << ".cols=" << mat.cols << std::endl; // -1
        std::cout << ".dims=" << mat.dims << std::endl;
        std::cout << ".type()=" << mat.type() << std::endl;
        std::cout << ".depth()=" << mat.depth() << std::endl;
        std::cout << ".channels()=" << mat.channels() << std::endl;
#if 0
        // use only 2 dimensions...
        std::cout << ".size()=" << mat.size() << ", size.dims()=" << mat.size.dims() << std::endl;
#endif
        std::cout << ".total()=" << mat.total() << std::endl;
    }
    // Operate Matrix.
    {
        uchar a_data[] = {
            1, 2, 3,
            4, 5, 6,
            7, 8, 9,
        };
        cv::Mat a(3, 3, CV_8UC1, a_data);

        uchar b_data[] = {
            1, 4, 7,
            2, 5, 8,
            3, 6, 9,
        };
        cv::Mat b(3, 3, CV_8UC1, b_data);

        {
            std::cout << "a=" << std::endl;
            std::cout << a << std::endl;

#if 1
            auto x0 = a + 5;    // x0 is cv::MatExpr.
#else
            cv::MatExpr x0_expression = a + 5;
            cv::Mat x0 = x0_expression; // cv::MatExpr to cv::Mat.
#endif
            std::cout << "a + 5=" << std::endl;
            std::cout << x0 << std::endl;

            auto x1 = a - 2;
            std::cout << "a - 2=" << std::endl;
            std::cout << x1 << std::endl;

            auto x2 = a * 6;
            std::cout << "a * 6=" << std::endl;
            std::cout << x2 << std::endl;

            auto x3 = a / 2;
            std::cout << "a / 2=" << std::endl;
            std::cout << x3 << std::endl;

            auto x4 = 2 / a;
            std::cout << "2 / a=" << std::endl;
            std::cout << x4 << std::endl;
        }
        {
            std::cout << "a=" << std::endl;
            std::cout << a << std::endl;
            std::cout << "b=" << std::endl;
            std::cout << b << std::endl;

            auto x0 = a + b;
            std::cout << "a + b=" << std::endl;
            std::cout << x0 << std::endl;

            auto x1 = a - b;
            std::cout << "a - b=" << std::endl;
            std::cout << x1 << std::endl;

            cv::Mat a2;
            a.convertTo(a2, CV_32F);
            cv::Mat b2;
            b.convertTo(b2, CV_32F);
            auto x2 = a2 * b2;
            std::cout << "a * b=" << std::endl;
            std::cout << x2 << std::endl;

            auto x3 = a.mul(b); // per elements.
            std::cout << "a.mul(b)=" << std::endl;
            std::cout << x3 << std::endl;

            cv::Mat a4;
            a.convertTo(a4, CV_32F);
            auto x4 = a4.inv();
            std::cout << "inv()=" << std::endl;
            std::cout << x4 << std::endl;

            cv::Mat a5;
            a.convertTo(a5, CV_32F);
            auto x5 = cv::determinant(a5);
            std::cout << "determinant()=" << std::endl;
            std::cout << x5 << std::endl;

            auto x6 = a.t();
            std::cout << "t()=" << std::endl;
            std::cout << x6 << std::endl;
        }
        {
            cv::Mat a0;
            a.convertTo(a0, CV_32F);
            cv::Vec3f v0(3, 4, 5);
            auto x0 = a0 * v0;
            std::cout << "a * v=" << std::endl;
            std::cout << x0 << std::endl;
        }
        {
            auto x0 = a.dot(b);
            std::cout << "dot()=" << std::endl;
            std::cout << x0 << std::endl;

            uchar a1_data[] = {
                1, 2, 3,
            };
            uchar b1_data[] = {
                9, 9, 9,
            };
            cv::Mat a1(1, 3, CV_8UC1, a1_data);
            cv::Mat b1(1, 3, CV_8UC1, b1_data);
            auto x1 = a1.cross(b1);
            std::cout << "cross()=" << std::endl;
            std::cout << x1 << std::endl;
        }
        {
            cv::Mat a0 = a.clone();
            cv::randu(a0, 0, 255);  // single uniformly-distributed random number
            std::cout << "randu()=" << std::endl;
            std::cout << a0 << std::endl;

            cv::Mat a1 = a.clone();
            cv::randn(a1, 0.0, 1.0);    // normally distributed random numbers
            std::cout << "randn()=" << std::endl;
            std::cout << a1 << std::endl;

            cv::Mat a2 = a.clone();
            cv::randShuffle(a2);    // shuffle
            std::cout << "randShuffle()=" << std::endl;
            std::cout << a2 << std::endl;
        }
        {
            uchar a1_data[] = {
                1, 2, 3,
                4, 5, 6,
                7, 8, 9,
            };
            cv::Mat a1(3, 3, CV_8UC1, a1_data);
            std::cout << "type()=" << a1.type() << ", depth()=" << a1.depth() << ", channels()=" << a1.channels() << std::endl;

            cv::Mat a2;
            const int new_type = CV_32FC3;  // not change channels.
#if 1
            a1.convertTo(a2, new_type); // re-assign and copy array.
#else
            // if type is set, assignTo is equivalent to convertTo.
            a1.assignTo(a2, new_type);  // copy array.
#endif
            std::cout << "type()=" << a2.type() << ", depth()=" << a2.depth() << ", channels()=" << a2.channels() << std::endl;
        }
        {
            cv::Mat a0 = a.clone();

            auto mask = a0 < 5;
            std::cout << "mask=" << std::endl;
            std::cout << mask << std::endl;

            a0.setTo(81, mask);
            std::cout << "a0=" << std::endl;
            std::cout << a0 << std::endl;
        }
        {
            if (a.dims == 2)
            {
                // 2D matrix only.
                cv::Mat a0 = a.clone();

                // 9 x 1 matrix.
                cv::Mat a1 = a0.reshape(0, 9);  // not copy.
                std::cout << "a1=" << std::endl;
                std::cout << a1 << std::endl;
                // 3 channels.
                cv::Mat a2 = a0.reshape(3); // not copy.
                std::cout << "a2=" << std::endl;
                std::cout << ".rows=" << a2.rows << std::endl;
                std::cout << ".cols=" << a2.cols << std::endl;
                std::cout << ".channels()=" << a2.channels() << std::endl;

                std::cout << "a0=" << std::endl;
                std::cout << ".rows=" << a0.rows << std::endl;
                std::cout << ".cols=" << a0.cols << std::endl;
                std::cout << ".channels()=" << a0.channels() << std::endl;
                std::cout << a0 << std::endl;
            }
        }
        {
            cv::Mat a0 = a.clone();
            a0.resize(a0.rows + 1);
            std::cout << "a0=" << std::endl;
            std::cout << ".rows=" << a0.rows << std::endl;
            std::cout << ".cols=" << a0.cols << std::endl;
            std::cout << a0 << std::endl;
        }
        {
            float a1_data[] = {
                 1.f,  2.f,  3.f,  4.f,
                 5.f,  6.f,  7.f,  8.f,
                 9.f, 10.f, 11.f, 12.f,
                13.f, 14.f, 15.f, 16.f,
            };
            cv::Mat a1(4, 4, CV_32FC1, a1_data);

            // Submatrix
            cv::Mat sub = a1(cv::Rect(1, 1, 3, 3));
            std::cout << std::boolalpha << "isSubmatrix()=" << sub.isSubmatrix() << std::endl;
            std::cout << "sub=" << std::endl;
            std::cout << sub << std::endl;

#if 0
            a.convertTo(sub, a1.type());
#else
            a.assignTo(sub, a1.type());
#endif
            std::cout << "sub=" << std::endl;
            std::cout << sub << std::endl;
            std::cout << "a1=" << std::endl;
            std::cout << a1 << std::endl;
        }
        {
            ushort data[] = {
                1,  2,  3,  4,
                5,  6,  7,  8,
                9, 10, 11, 12,
            };
            cv::Mat mat(3, 4, CV_16UC1, data);

            for (auto y = 0; y < mat.rows; ++y)
                for (auto x = 0; x < mat.cols; ++x)
                    mat.at<ushort>(y, x) = x * y;

            for (auto y = 0; y < mat.rows; ++y)
                std::cout << "[" << y << "]=" << mat.row(y) << std::endl;

            for (auto x = 0; x < mat.cols; ++x)
                std::cout << "[" << x << "]=" << mat.col(x) << std::endl;

            std::cout << "mat=" << std::endl;
            std::cout << mat << std::endl;
        }
        {
            uchar data[] = {
                1, 2, 3,
                4, 5, 6,
                7, 8, 9,
            };
            cv::Mat mat(3, 3, CV_8UC1, data);

#if 1
            mat.forEach<uchar>([](uchar& element, const int* position) -> void {
                auto row = position[0]; // y
                auto col = position[1]; // x
                std::cout << "[" << row << "][" << col << "]=" << static_cast<uint>(element) << std::endl;
            });
#else
            struct Operator
            {
                void operator ()(uchar& element, const int* index)
                {
                    // index is row.
                    element += *index;
                }
            };
            mat.forEach<uchar>(Operator());
#endif
            std::cout << "mat=" << std::endl;
            std::cout << mat << std::endl;
        }
        {
            cv::Mat a0 = a.clone();
            cv::Mat a1;
#if 1
            a0.convertTo(a1, CV_32FC1, 2.5f);
#else
            a0.convertTo(a1, CV_32FC1);
            a1 *= 2.5f;
#endif
            std::cout << "a1=" << std::endl;
            std::cout << a1 << std::endl;
        }
        {
            cv::Mat a0 = a.clone();
            std::cout << ".empty()=" << a0.empty() << std::endl;
            a0.release();
            std::cout << ".empty()=" << a0.empty() << std::endl;
            a0.create(4, 3, CV_16FC2);
            std::cout << ".empty()=" << a0.empty() << std::endl;
            a0.release();
            std::cout << ".empty()=" << a0.empty() << std::endl;
        }
        {
            cv::Mat a0 = a.clone();
            std::cout << "a0=" << std::endl;
            std::cout << a0 << std::endl;

            auto nx = 3;    // x 3
            auto ny = 3;    // x 3
            auto a1 = cv::repeat(a0, ny, nx);
            std::cout << "a1=" << std::endl;
            std::cout << a1 << std::endl;

            cv::Mat vertical(9, 1, a1.type(), 88);
            cv::Mat rect = a1(cv::Rect(3, 0, 4, 9));
            cv::repeat(vertical, 1, 4, rect);
            std::cout << "a1=" << std::endl;
            std::cout << a1 << std::endl;
        }
    }
    // Image processing
    {
        // BGR
        cv::Mat image(4, 4, CV_8UC3, cv::Scalar(63, 127, 255));

        {
            cv::Mat channels[3];

            // split per channels.
            cv::split(image, channels);
            cv::Mat& blue = channels[0];
            cv::Mat& green = channels[1];
            cv::Mat& red = channels[2];

            // merge channels.
            cv::Mat merged;
            cv::merge(channels, 3, merged);
        }
        {
            cv::Mat imageRGB;
            cv::cvtColor(image, imageRGB, cv::COLOR_BGR2RGB);
        }

        // cv::imread
        // cv::imwrite
        // cv::resize
        // cv::remap

#ifdef TEST_OPENCV_MATRIX_GDIPLUS
        {
            Gdiplus::GdiplusStartupInput startup_input;
            ULONG_PTR token;
            Gdiplus::GdiplusStartup(&token, &startup_input, nullptr);
            {
                cv::Mat src_mat = image.clone();
                const auto src_size = src_mat.size();

                const auto dst_size = cv::Size(4, 4);
                cv::Mat dst_mat(dst_size, src_mat.type());

                // cv::Mat -> Gdiplus::Bitmap
                Gdiplus::Bitmap src_bitmap(src_size.width, src_size.height, static_cast<int>(src_mat.step1()), PixelFormat24bppRGB, src_mat.data);
                Gdiplus::Bitmap dst_bitmap(dst_size.width, dst_size.height);

                auto graphics = Gdiplus::Graphics::FromImage(&dst_bitmap);
                graphics->SetCompositingQuality(Gdiplus::CompositingQuality::CompositingQualityHighQuality);
                graphics->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeBilinear);
                graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
                graphics->DrawImage(&src_bitmap, 0, 0, dst_bitmap.GetWidth(), dst_bitmap.GetHeight());
                graphics->Flush();
                delete graphics;

                // Gdiplus::Bitmap -> cv::Mat
                Gdiplus::Rect rect(0, 0, dst_bitmap.GetWidth(), dst_bitmap.GetHeight());
                Gdiplus::BitmapData data;

                if (dst_bitmap.LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &data) == Gdiplus::Ok)
                {
                    cv::Mat(rect.Height, rect.Width, CV_8UC3, data.Scan0, data.Stride).copyTo(dst_mat);
                }
                dst_bitmap.UnlockBits(&data);
            }
            Gdiplus::GdiplusShutdown(token);
        }
#endif
    }
#endif
#ifdef TEST_OPENCV_VIDEO
    // input_file_path output_path
    if (argc >= 3)
    {
        auto input = argv[1];
        auto output = argv[2];

        if (std::ifstream(input).is_open())	// file exists ?
        {
#if 0
            cv::VideoCapture inputVideo(input);
            if (inputVideo.isOpened())
#else
            cv::VideoCapture inputVideo;
            if (inputVideo.open(input))
#endif
            {
                std::cout << "[cv::VideoCapture]" << std::endl;
                std::cout << "getBackendName()=" << inputVideo.getBackendName() << std::endl;
                std::cout << "getExceptionMode()=" << inputVideo.getExceptionMode() << std::endl;

                // output video props.
                std::cout << "cv::CAP_PROP_POS_MSEC=" << inputVideo.get(cv::CAP_PROP_POS_MSEC) << "[ms]" << std::endl;
                std::cout << "cv::CAP_PROP_POS_FRAMES=" << inputVideo.get(cv::CAP_PROP_POS_FRAMES) << "[frame]" << std::endl;
                std::cout << "cv::CAP_PROP_FRAME_WIDTH=" << inputVideo.get(cv::CAP_PROP_FRAME_WIDTH) << "[pixel]" << std::endl;
                std::cout << "cv::CAP_PROP_FRAME_HEIGHT=" << inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT) << "[pixel]" << std::endl;
                {
                    auto fourcc = static_cast<int>(inputVideo.get(cv::CAP_PROP_FOURCC));
                    auto cc = reinterpret_cast<char*>(&fourcc);
                    std::cout << "cv::CAP_PROP_FOURCC=" << cc[0] << cc[1] << cc[2] << cc[3] << std::endl;
                }
                std::cout << "cv::CAP_PROP_FPS=" << inputVideo.get(cv::CAP_PROP_FPS) << "[fps]" << std::endl;
                std::cout << "cv::CAP_PROP_FRAME_COUNT=" << inputVideo.get(cv::CAP_PROP_FRAME_COUNT) << "[frame]" << std::endl;

#ifdef TEST_OPENCV_VIDEO_OUTPUT_VIDEO
                cv::String outputVideoFilePath(output);
                if (outputVideoFilePath.back() != '\\')
                    outputVideoFilePath += '\\';
                outputVideoFilePath += "video.mp4";

                auto fourcc = static_cast<int>(inputVideo.get(cv::CAP_PROP_FOURCC));
                auto cc = reinterpret_cast<char*>(&fourcc);
                fourcc = cv::VideoWriter::fourcc(cc[0], cc[1], cc[2], cc[3]);
                auto fps = inputVideo.get(cv::CAP_PROP_FPS);
                cv::Size frameSize(static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int>(inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT)));
#if 0
                cv::VideoWriter outputVideo(outputVideoFilePath, fourcc, fps, frameSize);
                if (!outputVideo.isOpened())
                    throw std::exception("cv::VideoWriter is not opened.");
#else
                cv::VideoWriter outputVideo;
                if (!outputVideo.open(outputVideoFilePath, fourcc, fps, frameSize))
                    throw std::exception("cv::VideoWriter is not opened.");
#endif
                std::cout << "[cv::VideoWriter]" << std::endl;
                std::cout << "getBackendName()=" << outputVideo.getBackendName() << std::endl;
#endif

                // output frames.
                cv::Mat frame;
                const auto frameCount = inputVideo.get(cv::CAP_PROP_FRAME_COUNT);
                for (auto i = 0; i < frameCount; ++i)
                {
                    inputVideo >> frame;

#ifdef TEST_OPENCV_VIDEO_OUTPUT_FRAME
                    cv::String outputFrameFilePath(output);
                    if (outputFrameFilePath.back() != '\\')
                        outputFrameFilePath += '\\';
#if 0
                    outputFrameFilePath += "frame.";
                    outputFrameFilePath += std::to_string(i);
                    outputFrameFilePath += ".png";	// if OpenCV 3.x output only "bmp".
#else
                    std::ostringstream oss;
                    oss << "frame." << std::setfill('0') << std::setw(4) << i << ".png";
                    outputFrameFilePath += oss.str();
#endif
                    cv::imwrite(outputFrameFilePath, frame);
#endif
#ifdef TEST_OPENCV_VIDEO_OUTPUT_VIDEO
#ifdef TEST_OPENCV_VIDEO_OUTPUT_VIDEO_FRAME_CONVERSION
                    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
#endif
                    outputVideo << frame;
#endif

                    // next
                    std::cout << inputVideo.get(cv::CAP_PROP_POS_MSEC) << "[ms], " << inputVideo.get(cv::CAP_PROP_POS_FRAMES) << " / " << frameCount << std::endl;
                }
#ifdef TEST_OPENCV_VIDEO_OUTPUT_VIDEO
                outputVideo.release();
#endif
        }
            inputVideo.release();
    }
}
#endif
#else
    std::cout << "Hello World!\n"; 
#endif
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
