#ifndef QFEATUREDETECTOR_H
#define QFEATUREDETECTOR_H

#include "qmatdisplay.h"
#include "qlcvfeatures2dglobal.h"

namespace cv{
class FeatureDetector;
}

class QKeyPointVector;
class Q_LCVFEATURES2D_EXPORT QFeatureDetector : public QQuickItem{

    Q_OBJECT
    Q_PROPERTY(QMat* input                READ inputMat  WRITE setInputMat  NOTIFY inputChanged)
    Q_PROPERTY(QMat* output               READ output    NOTIFY outputChanged)
    Q_PROPERTY(QMat* mask                 READ mask      WRITE setMask      NOTIFY maskChanged)
    Q_PROPERTY(QKeyPointVector* keypoints READ keypoints WRITE setKeypoints NOTIFY keypointsChanged)

public:
    explicit QFeatureDetector(QQuickItem *parent = 0);
    QFeatureDetector(cv::FeatureDetector* detector, QQuickItem* parent = 0);
    virtual ~QFeatureDetector();

public:
    QMat* inputMat();
    void setInputMat(QMat* mat);

    QMat* output();

    QMat* mask();
    void setMask(QMat* mat);

    QKeyPointVector* keypoints();
    void setKeypoints(QKeyPointVector* keypoints);

protected:
    cv::FeatureDetector* detector();
    void initializeDetector(cv::FeatureDetector* detector);
    void detect();

public:
    virtual void componentComplete();
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *);

signals:
    void inputChanged();
    void maskChanged();
    void keypointsChanged();
    void outputChanged();

private:
    void drawKeypoints();

    cv::FeatureDetector* m_detector;
    QKeyPointVector*     m_keypoints;

    QMat* m_in;
    QMat* m_output;
    QMat* m_mask;

    bool  m_outputDirty;
};

inline QMat *QFeatureDetector::inputMat(){
    return m_in;
}

inline void QFeatureDetector::setInputMat(QMat *mat){
    if ( mat == 0 )
        return;

    cv::Mat* matData = mat->cvMat();
    if ( implicitWidth() != matData->cols || implicitHeight() != matData->rows ){
        setImplicitWidth(matData->cols);
        setImplicitHeight(matData->rows);
    }
    m_in = mat;
    emit inputChanged();
    detect();
}

inline QMat*QFeatureDetector::output(){
    if ( m_outputDirty )
        drawKeypoints();
    return m_output;
}

inline QMat* QFeatureDetector::mask(){
    return m_mask;
}

inline void QFeatureDetector::setMask(QMat* mat){
    if ( mat == 0 )
        return;

    m_mask = mat;
    emit maskChanged();
    detect();
}

inline QKeyPointVector* QFeatureDetector::keypoints(){
    return m_keypoints;
}

inline void QFeatureDetector::setKeypoints(QKeyPointVector* keypoints){
    m_keypoints = keypoints;
    emit keypointsChanged();
}

#endif // QFEATUREDETECTOR_H
