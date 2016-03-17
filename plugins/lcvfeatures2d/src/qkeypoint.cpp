#include "qkeypoint.h"
#include "opencv2/features2d/features2d.hpp"

QKeyPoint::QKeyPoint(QObject *parent)
    : QObject(parent)
    , m_ptX(0)
    , m_ptY(0)
    , m_size(0)
    , m_angle(0)
    , m_response(0)
    , m_octave(0)
    , m_classId(0)
{
}

QKeyPoint::QKeyPoint(const cv::KeyPoint &keypoint, QObject *parent)
    : QObject(parent)
    , m_ptX(keypoint.pt.x)
    , m_ptY(keypoint.pt.y)
    , m_size(keypoint.size)
    , m_angle(keypoint.angle)
    , m_response(keypoint.response)
    , m_octave(keypoint.octave)
    , m_classId(keypoint.class_id)
{
}

QKeyPoint::~QKeyPoint(){
}

void QKeyPoint::toKeyPoint(cv::KeyPoint &kp){
    kp.pt       = cv::Point2f(m_ptX, m_ptY);
    kp.size     = m_size;
    kp.angle    = m_angle;
    kp.response = m_response;
    kp.octave   = m_octave;
    kp.class_id = m_classId;
}

