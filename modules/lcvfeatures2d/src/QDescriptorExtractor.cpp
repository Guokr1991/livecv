#include "QDescriptorExtractor.hpp"
#include "QKeyPointVector.hpp"

QDescriptorExtractor::QDescriptorExtractor(QQuickItem *parent)
    : QQuickItem(parent)
    , m_extractor(0)
    , m_keypoints(0)
    , m_in(QMat::nullMat())
    , m_descriptors(new QMat)
    , m_inDirty(false)
    , m_keypointsDirty(false)
{
}

QDescriptorExtractor::QDescriptorExtractor(cv::DescriptorExtractor* extractor, QQuickItem* parent)
    : QQuickItem(parent)
    , m_extractor(extractor)
    , m_keypoints(0)
    , m_in(QMat::nullMat())
    , m_descriptors(new QMat)
    , m_inDirty(false)
    , m_keypointsDirty(false)
{
}

QDescriptorExtractor::~QDescriptorExtractor(){
    delete m_descriptors;
}

void QDescriptorExtractor::componentComplete(){
    QQuickItem::componentComplete();
    compute();
}

void QDescriptorExtractor::compute(){
    if ( m_extractor && m_keypoints && isComponentComplete() ){
        m_inDirty        = false;
        m_keypointsDirty = false;
        m_extractor->compute(m_keypoints->cvMat(), m_keypoints->keypoints(), *m_descriptors->cvMat());

        emit descriptorsChanged();
    }
}
