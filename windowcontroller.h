#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>

class WindowController : public QObject
{
    Q_OBJECT
public:
    explicit WindowController(QObject *parent = nullptr);
    ~WindowController();

Q_INVOKABLE void openMainView();

signals:

public slots:
    void onQuickWindowClosing();
private:
    QMap<QObject*, QQmlApplicationEngine*> engines;
};

#endif // WINDOWCONTROLLER_H
