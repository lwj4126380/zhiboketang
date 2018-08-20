#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>

class iLiveHelper;

class WindowController : public QObject
{
    Q_OBJECT
public:
    explicit WindowController(QObject *parent = nullptr);
    ~WindowController();

Q_INVOKABLE void openSpecificView(QString qmlPath);

signals:

public slots:
    void onQuickWindowClosing();
private:
    QMap<QObject*, QPair<QQmlApplicationEngine*, void*>> engines;
    iLiveHelper *helper;
};

#endif // WINDOWCONTROLLER_H
