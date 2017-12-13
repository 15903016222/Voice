#include "static_weld_widget.h"
#include "ui_static_weld_widget.h"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

StaticWeldWidget::StaticWeldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticWeldWidget)
{
    ui->setupUi(this);
}

StaticWeldWidget::~StaticWeldWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}


void StaticWeldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(rect(), QPixmap(m_picPath));
}


void StaticWeldWidget::slotWeldTypeChanged(const QString &path)
{
    if(!path.isEmpty()) {
        m_picPath = path;
        /* TODO:判读路径是否正确及文件是否正确 */
        repaint();
    }
}

