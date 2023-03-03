#ifndef UTILS_H
#define UTILS_H

#include <QThread>

#include <QMutex>
#include <QWaitCondition>

inline void custom_msleep(int milliseconds)
{
    QWaitCondition wc;
    QMutex mutex;
    QMutexLocker locker(&mutex);
    wc.wait(&mutex, milliseconds);
}

#endif // UTILS_H
