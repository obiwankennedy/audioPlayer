#ifndef FAKENETWORKRECEIVER_H
#define FAKENETWORKRECEIVER_H

#include <QObject>
#include <QTimer>
typedef void (*PtrFunct)(int);

class FakeNetworkReceiver : public QObject {
    Q_OBJECT
public:
    explicit FakeNetworkReceiver(std::function<void(int)>& pf, QObject* parent = nullptr);
    explicit FakeNetworkReceiver(PtrFunct pf, QObject* parent = nullptr);

private:
    std::function<void(int)> m_pf;
    PtrFunct m_fp;
    QTimer m_timer;
};

#endif // FAKENETWORKRECEIVER_H
