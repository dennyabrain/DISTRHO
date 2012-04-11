/*
 * Qt4 Demo plugin by falkTX <falktx@gmail.com>
 *
 * Released under the Public Domain
 */

#ifndef AUDIOGAIN_H
#define AUDIOGAIN_H

#include <QtGui/QDialog>

namespace Ui {
class AudioGainW;
}

class AudioGainW : public QDialog
{
    Q_OBJECT

public:
    AudioGainW(QWidget* parent = 0);
    ~AudioGainW();

    virtual float getPeakValueL() { return 0.0f; }
    virtual float getPeakValueR() { return 0.0f; }
    virtual void setProcessValueL(float) {}
    virtual void setProcessValueR(float) {}

protected:
    Ui::AudioGainW* ui;

private:
    Q_SLOT void checkPeaks();
    Q_SLOT void LeftPeakValueChanged(int value);
    Q_SLOT void RightPeakValueChanged(int value);

    int refresh;
};

#endif // AUDIOGAIN_H
