#ifndef __COLOR_BAR_H__
#define __COLOR_BAR_H__

#include <QWidget>

typedef QSharedPointer<QColor> QColorPointer;

class QXmlStreamReader;
class ColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBar(QWidget *parent = 0);

    void load_file(const QString &path);

    QColorPointer color(quint8 index) const;

protected:
    void read_special_colors(QXmlStreamReader &xml);

    void read_main_colors(QXmlStreamReader &xml);

    void paintEvent(QPaintEvent *e);

signals:

public slots:

private:
    QVector<QColorPointer> m_colorVector;
};

inline QColorPointer ColorBar::color(quint8 index) const
{
    if (index <  m_colorVector.size()) {
        return m_colorVector[index];
    }
    return QColorPointer(new QColor(Qt::black));
}

#endif // __COLOR_BAR_H__
