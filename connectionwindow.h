#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H



#include <QSerialPortInfo>
#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QTimer>
/*test*/
#include <QMetaMethod>
/******/
#include "canconnectionmodel.h"
#include "canframemodel.h"


class CANConnectionModel;

namespace Ui {
class ConnectionWindow;
}


class ConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionWindow(CANFrameModel *canModel, QWidget *parent = 0);
    ~ConnectionWindow();
    void showEvent(QShowEvent *);
    int getSpeed();
    QString getPortName(); //name of port to connect to
    CANCon::type getConnectionType();
    bool getSWMode();
    void callback(CANCon::cbtype pType);

signals:
    void updateBusSettings(CANBus *bus);
    void updatePortName(QString port);

public slots:
    void setSpeed(int speed0);
    void setSWMode(bool mode);
    void sendFrame(const CANFrame *);
    void sendFrameBatch(const QList<CANFrame> *);
    void setSuspendAll(bool);


private slots:
    void handleOKButton();
    void handleConnTypeChanged();
    void handleConnSelectionChanged();
    void handleRemoveConn();
    void handleEnableAll();
    void handleDisableAll();
    void handleRevert();
    void handleNewConn();
    void receiveBusStatus(int bus, int speed, int status);
    void connectionStatus(CANCon::status);

    void refreshCanList();

private:
    Ui::ConnectionWindow *ui;
    QList<QSerialPortInfo> ports;
    QSettings *settings;
    CANConnectionModel *connModel;
    CANFrameModel *canModel;
    QTimer mTicker;

    QAtomicInt mRefreshReqOngoing;

    /*test*/
    QMetaMethod mRefreshM;


    void selectSerial();
    void selectKvaser();
    void selectSocketCan();
    bool isSocketCanAvailable();
    void setActiveAll(bool pActive);
};

#endif // CONNECTIONWINDOW_H
