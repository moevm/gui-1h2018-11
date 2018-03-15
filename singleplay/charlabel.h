#ifndef CHARLABEL_H
#define CHARLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QString>

class charlabel : public QLabel
{

    Q_OBJECT
public:
    explicit charlabel(QWidget *parent = nullptr,QString str = "A");

    bool getAllowed() const;
    void setAllowed(bool value);

    void setActived(bool value);

signals:

    click(QString q);

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    bool allowed;
    bool actived;
};

#endif // CHARLABEL_H
