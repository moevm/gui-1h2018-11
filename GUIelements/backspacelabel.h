#ifndef BACKSPACELABEL_H
#define BACKSPACELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QString>

class BackspaceLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BackspaceLabel(QWidget *parent = nullptr);

signals:
 void backspace();
public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // BACKSPACELABEL_H
