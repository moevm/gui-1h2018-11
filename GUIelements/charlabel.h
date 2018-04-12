#ifndef CHARLABEL_H
#define CHARLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QString>

class Charlabel : public QLabel
{

    Q_OBJECT
public:
    explicit Charlabel(QWidget *parent = nullptr,QString str = "A",bool actived=false);
    bool getAllowed() const;
    void setAllowed(bool value);

    void setActived(bool value);

signals:

    void click(QString q);

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    bool allowed;
    bool actived;
};

#endif // CHARLABEL_H
