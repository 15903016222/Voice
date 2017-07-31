#ifndef __COLOR_BAR_H__
#define __COLOR_BAR_H__

#include <QWidget>

class QXmlStreamReader;
class ColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBar(QWidget *parent = 0);

    void load_file(const QString &path);

protected:
    void read_special_colors(QXmlStreamReader &xml);

    void read_main_colors(QXmlStreamReader &xml);

    void paintEvent(QPaintEvent *e);

signals:

public slots:
};

#endif // __COLOR_BAR_H__
