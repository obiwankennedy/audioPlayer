#include "fakenetworkreceiver.h"

FakeNetworkReceiver::FakeNetworkReceiver(std::function<void(int)>& pf, QObject* parent)
    : QObject { parent }
    , m_pf(pf)
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        static int i = 0;
        if (m_pf == nullptr)
            return;
        m_pf(i++);
    });

    m_timer.start();
}

FakeNetworkReceiver::FakeNetworkReceiver(PtrFunct pf, QObject* parent)
    : QObject { parent }
    , m_fp(pf)
{
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, this, [this]() {
        static int i = 0;
        if (m_fp == nullptr)
            return;
        (*m_fp)(i++);
    });

    m_timer.start();
}
