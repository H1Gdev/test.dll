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

#define TEST_OPENCV_VIDEO
#define TEST_OPENCV_VIDEO_OUTPUT_FRAME
#define TEST_OPENCV_VIDEO_OUTPUT_VIDEO
//#define TEST_OPENCV_VIDEO_OUTPUT_VIDEO_FRAME_CONVERSION
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
                    auto fourcc = (int)inputVideo.get(cv::CAP_PROP_FOURCC);
                    auto cc = (char*)&fourcc;
                    std::cout << "cv::CAP_PROP_FOURCC=" << cc[0] << cc[1] << cc[2] << cc[3] << std::endl;
                }
                std::cout << "cv::CAP_PROP_FPS=" << inputVideo.get(cv::CAP_PROP_FPS) << "[fps]" << std::endl;
                std::cout << "cv::CAP_PROP_FRAME_COUNT=" << inputVideo.get(cv::CAP_PROP_FRAME_COUNT) << "[frame]" << std::endl;

#ifdef TEST_OPENCV_VIDEO_OUTPUT_VIDEO
                cv::String outputVideoFilePath(output);
                if (outputVideoFilePath.back() != '\\')
                    outputVideoFilePath += '\\';
                outputVideoFilePath += "video.mp4";

                auto fourcc = (int)inputVideo.get(cv::CAP_PROP_FOURCC);
                auto cc = (char*)&fourcc;
                fourcc = cv::VideoWriter::fourcc(cc[0], cc[1], cc[2], cc[3]);
                auto fps = inputVideo.get(cv::CAP_PROP_FPS);
                cv::Size frameSize((int)inputVideo.get(cv::CAP_PROP_FRAME_WIDTH), (int)inputVideo.get(cv::CAP_PROP_FRAME_HEIGHT));
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
