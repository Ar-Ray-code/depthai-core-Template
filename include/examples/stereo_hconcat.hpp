#pragma once

#include "depthai/depthai.hpp"

class StereoCat
{
public:
    StereoCat();

    void setup_pipe();
    cv::Mat get_image();

private:
    dai::Pipeline pipeline;
    std::shared_ptr<dai::Device> device;

    cv::Mat imgLeft, imgRight, imgCat;

    std::shared_ptr<dai::DataOutputQueue> qLeft, qRight;

    std::shared_ptr<dai::ImgFrame> inLeft, inRight;

    std::shared_ptr<dai::node::MonoCamera> monoLeft, monoRight;
    std::shared_ptr<dai::node::XLinkOut> xoutLeft, xoutRight;
};
