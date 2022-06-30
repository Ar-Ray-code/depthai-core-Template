#include "examples/stereo_hconcat.hpp"

StereoCat::StereoCat()
{
    setup_pipe();
}

void StereoCat::setup_pipe()
{
    monoLeft = pipeline.create<dai::node::MonoCamera>();
    monoRight = pipeline.create<dai::node::MonoCamera>();
    xoutLeft = pipeline.create<dai::node::XLinkOut>();
    xoutRight = pipeline.create<dai::node::XLinkOut>();

    xoutLeft->setStreamName("left");
    xoutRight->setStreamName("right");

    // Properties
    monoLeft->setBoardSocket(dai::CameraBoardSocket::LEFT);
    monoLeft->setResolution(dai::MonoCameraProperties::SensorResolution::THE_720_P);
    monoRight->setBoardSocket(dai::CameraBoardSocket::RIGHT);
    monoRight->setResolution(dai::MonoCameraProperties::SensorResolution::THE_720_P);

    // Linking
    monoRight->out.link(xoutRight->input);
    monoLeft->out.link(xoutLeft->input);

    device = std::make_shared<dai::Device>(pipeline);

    qLeft = device->getOutputQueue("left", 4, false);
    qRight = device->getOutputQueue("right", 4, false);
}

cv::Mat StereoCat::get_image()
{
    inLeft = qLeft->tryGet<dai::ImgFrame>();
    inRight = qRight->tryGet<dai::ImgFrame>();

    if (inLeft && inRight)
    {
        imgLeft = inLeft->getCvFrame();
        imgRight = inRight->getCvFrame();

        cv::hconcat(imgLeft, imgRight, imgCat);
    }

    return imgCat;
}

int main(void)
{
    StereoCat scat;
    cv::Mat cat_img;
    while (true)
    {
        cat_img = scat.get_image();
        // if size
        if (cat_img.cols > 0 && cat_img.rows > 0)
        {
            cv::imshow("StereoCat", cat_img);
        }
        cv::waitKey(1);
    }

    return 0;
}
