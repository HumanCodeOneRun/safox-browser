#include <QObject>

class Counter: public QObject
{
    Q_OBJECT
    
    public:
    int value1;
    int value2;

    public slots:
    void setvalue(int _value1, int _value2);
    signals:
    void value_change(int, int, int);
};