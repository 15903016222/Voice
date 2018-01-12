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
    delete ui;
}


void StaticWeldWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(rect(), QPixmap(m_picPath));
}


void StaticWeldWidget::slot_weld_type_changed(const QString &path)
{
    if(!path.isEmpty()) {
        m_picPath = path;
        update();
    }
}

