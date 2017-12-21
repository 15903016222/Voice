#include "main_weld_widget.h"
#include "ui_main_weld_widget.h"

#include <QDebug>
#include <math.h>

#include "weld_information_factory.h"
#include "weld_widget_factory.h"
#include "global_property_tag.h"
#include "base_weld_widget.h"

static double DEFAULT_THICKNESS_SIZE = 30.0;

MainWeldWidget::MainWeldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWeldWidget),
    m_pbaseWeldWidget(NULL)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    connect(ui->backBtn, SIGNAL(clicked(bool)), this, SLOT(do_btn_clicked()));
    connect(ui->finishedBtn, SIGNAL(clicked(bool)), this, SLOT(do_btn_clicked()));

    init();
}

MainWeldWidget::~MainWeldWidget()
{
    delete ui;
}

void MainWeldWidget::set_thickness(double value)
{
    m_verticalSize.defaultSize = value;
    m_verticalSize.currentSize = value;
}

QSharedPointer<DplWeld::BaseWeldInformation> MainWeldWidget::get_weld_information()
{
    return m_pbaseWeldInformation;
}

void MainWeldWidget::show_widget(int weldType, double thickness)
{
    /* 默认显示type型焊缝 */
    set_thickness(thickness);

    QMap<QString, double> valueList;

    valueList.insert(TAG_THICKNESS, thickness);

    set_default_value(weldType, valueList);

    ui->weldProperties->set_weld_info(valueList);

    do_weldProperties_weld_info_changed(weldType, valueList);

    show();
}


void MainWeldWidget::do_weldProperties_weld_info_changed(int type, const QMap<QString, double> &valueList)
{
    /*
     * get weld information
    */
    QMap<QString, double>  tmpValueList = valueList;

    /* 增加额外信息 */
    append_value(type, tmpValueList);

    if(m_pbaseWeldInformation.isNull() || (m_pbaseWeldInformation->get_type() != type)) {

        m_pbaseWeldInformation = DplWeld::WeldInformationFactory::create_weld_information(type, tmpValueList);

        if(m_pbaseWeldWidget != NULL) {
            ui->weldVerticalLayout->removeWidget((QWidget*)m_pbaseWeldWidget);
            delete m_pbaseWeldWidget;
            m_pbaseWeldWidget = NULL;
        }

        m_pbaseWeldWidget = DplWeld::WeldWidgetFactory::create_weld_widget(m_pbaseWeldInformation);

        if(m_pbaseWeldWidget == NULL) {
            return;
        }

        connect_signals(m_pbaseWeldWidget->get_weld_type());

        ui->weldVerticalLayout->addWidget((QWidget*) m_pbaseWeldWidget);

        QString picPath;
        m_pbaseWeldInformation->get_pic_path(picPath);
        ui->staticWeld->slotWeldTypeChanged(picPath);

    } else {
        m_pbaseWeldInformation = DplWeld::WeldInformationFactory::create_weld_information(type, tmpValueList);
        m_pbaseWeldWidget->update_weld_information(m_pbaseWeldInformation);
    }

    config_ruler();

}

void MainWeldWidget::do_btn_clicked()
{
    QPushButton *current = qobject_cast<QPushButton*> (sender());

    if(current->objectName() == ui->backBtn->objectName()) {
        this->hide();
    } else if(current->objectName() == ui->finishedBtn->objectName()) {
        /* 发送最新的焊缝信息信号 */
        qDebug() << "[" << __FUNCTION__ << "]" << " TODO: send signal to which use newest info about weld.";
        this->hide();
    }
}


void MainWeldWidget::config_ruler()
{
    if(m_pbaseWeldInformation->get_type() == DplWeld::TKY_Weld) {
        /* 占比为10% */
        double totalSize = m_verticalSize.currentSize / ((100 - DplWeld::TKYTopScale - DplWeld::TKYBottomScale) / 100.0);

        ui->leftRuler->set_range( -totalSize * (DplWeld::TKYTopScale) / 100.0,
                        totalSize * (100.0 - DplWeld::TKYTopScale) / 100.0);
        ui->bottomRuler->set_range(-m_horizontalSize.currentSize, m_horizontalSize.currentSize);

    } else {
        /* 厚度占左标尺的60% */
        double leftRulerSize = m_verticalSize.currentSize / (DplWeld::WeldScale / 100.0);
        ui->leftRuler->set_range(-leftRulerSize * (DplWeld::BottomScale / 100.0),
                                 leftRulerSize * ((100 - DplWeld::BottomScale) / 100.0));

        ui->bottomRuler->set_range(-m_horizontalSize.currentSize, m_horizontalSize.currentSize);
    }

    ui->leftRuler->repaint();
    ui->bottomRuler->repaint();
}


void MainWeldWidget::connect_signals(int type)
{
    switch (type)\
    {
        case DplWeld::U_Weld:
        {
            connect(m_pbaseWeldWidget, SIGNAL(max_W1(double)), ui->weldProperties, SLOT(slot_max_W1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_W2(double)), ui->weldProperties, SLOT(slot_max_W2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_H1(double)), ui->weldProperties, SLOT(slot_min_H1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_R1(double)), ui->weldProperties, SLOT(slot_min_R1(double)));
            break;
        }
        case DplWeld::UU_Weld:
        {
            connect(m_pbaseWeldWidget, SIGNAL(max_W1(double)), ui->weldProperties, SLOT(slot_max_W1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_W2(double)), ui->weldProperties, SLOT(slot_max_W2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_H1(double)), ui->weldProperties, SLOT(slot_min_H1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_R1(double)), ui->weldProperties, SLOT(slot_min_R1(double)));

            connect(m_pbaseWeldWidget, SIGNAL(max_W3(double)), ui->weldProperties, SLOT(slot_max_W3(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_H2(double)), ui->weldProperties, SLOT(slot_min_H2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_R2(double)), ui->weldProperties, SLOT(slot_min_R2(double)));

            break;
        }
        case DplWeld::UV_Weld:
        {
            connect(m_pbaseWeldWidget, SIGNAL(max_W1(double)), ui->weldProperties, SLOT(slot_max_W1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_W2(double)), ui->weldProperties, SLOT(slot_max_W2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_H1(double)), ui->weldProperties, SLOT(slot_min_H1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_R1(double)), ui->weldProperties, SLOT(slot_min_R1(double)));

            break;
        }
        case DplWeld::TKY_Weld:
        {
            connect(m_pbaseWeldWidget, SIGNAL(min_X1(double)), ui->weldProperties, SLOT(slot_min_X1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_Y1(double)), ui->weldProperties, SLOT(slot_max_Y1(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_X2(double)), ui->weldProperties, SLOT(slot_min_X2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_Y2(double)), ui->weldProperties, SLOT(slot_max_Y2(double)));
            connect(m_pbaseWeldWidget, SIGNAL(min_angle(double)), ui->weldProperties, SLOT(slot_min_angle(double)));
            connect(m_pbaseWeldWidget, SIGNAL(max_angle(double)), ui->weldProperties, SLOT(slot_max_angle(double)));

            break;
        }
        default:
        break;
    }
}

void MainWeldWidget::set_default_value(int weldType, QMap<QString, double> &valueList)
{
    switch (weldType) {
        case DplWeld::I_Weld:
        {
            valueList.insert(TAG_W1, 0.0);

            break;
        }
        case DplWeld::V_Weld:
        {
            valueList.insert(TAG_W1, 2.0);
            valueList.insert(TAG_W2, 1.0);
            valueList.insert(TAG_H1, 3.0);
            break;
        }
        case DplWeld::U_Weld:
        {
            valueList.insert(TAG_W1, 2.0);
            valueList.insert(TAG_W2, 1.0);
            valueList.insert(TAG_H1, 3.0);
            valueList.insert(TAG_R1, 2.0);
            break;
        }
        case DplWeld::VY_Weld:
        {
            valueList.insert(TAG_W1, 5.0);
            valueList.insert(TAG_W2, 2.0);
            valueList.insert(TAG_W3, 1.0);
            valueList.insert(TAG_H1, 2.0);
            valueList.insert(TAG_H2, 2.0);
            break;
        }
        case DplWeld::VV_Weld:
        {
            valueList.insert(TAG_W1, 2.0);
            valueList.insert(TAG_W2, 1.0);
            valueList.insert(TAG_W3, 2.0);
            valueList.insert(TAG_H1, 3.0);
            valueList.insert(TAG_H2, 3.0);
            break;
        }
        case DplWeld::UU_Weld:
        {
            valueList.insert(TAG_W1, 2.0);
            valueList.insert(TAG_W2, 1.0);
            valueList.insert(TAG_W3, 2.0);
            valueList.insert(TAG_H1, 3.0);
            valueList.insert(TAG_H2, 3.0);
            valueList.insert(TAG_R1, 2.0);
            valueList.insert(TAG_R2, 2.0);
            break;
        }
        case DplWeld::UV_Weld:
        {
            valueList.insert(TAG_W1, 2.0);
            valueList.insert(TAG_W2, 1.0);
            valueList.insert(TAG_W3, 2.0);
            valueList.insert(TAG_H1, 3.0);
            valueList.insert(TAG_H2, 3.0);
            valueList.insert(TAG_R1, 2.0);
            break;
        }
        case DplWeld::TKY_Weld:
        {
            valueList.insert(TAG_T1, 30.0);
            valueList.insert(TAG_T2, 20.0);
            valueList.insert(TAG_X1, 5.0);
            valueList.insert(TAG_Y1, 5.0);
            valueList.insert(TAG_X2, 5.0);
            valueList.insert(TAG_Y2, 5.0);
            valueList.insert(TAG_ANGLE, 90.0);
            break;
        }
        default:
            break;
    }

    valueList.insert(TAG_TYPE, weldType);
}


void MainWeldWidget::init()
{
    m_verticalSize.defaultSize      = DEFAULT_THICKNESS_SIZE;
    m_verticalSize.currentSize      = DEFAULT_THICKNESS_SIZE;
    m_horizontalSize.defaultSize    = DEFAULT_THICKNESS_SIZE;
    m_horizontalSize.currentSize    = DEFAULT_THICKNESS_SIZE;

    /* 厚度占左标尺的60% */
    double leftRulerSize = m_verticalSize.currentSize / (DplWeld::WeldScale / 100.0);

    ui->leftRuler->set_range(-leftRulerSize * (DplWeld::BottomScale / 100.0),
                             leftRulerSize * ((100 - DplWeld::BottomScale) / 100.0));

    ui->bottomRuler->set_range(-m_horizontalSize.currentSize, m_horizontalSize.currentSize);


    connect(ui->weldProperties, SIGNAL(weld_info_changed(int,QMap<QString,double>)), this, SLOT(do_weldProperties_weld_info_changed(int,QMap<QString,double>)));

    ui->weldProperties->set_thickness(m_verticalSize.currentSize);

    /* 默认显示I型焊缝 */
    QMap<QString, double> valueList;
    valueList.insert(TAG_W1, 0.0);
    do_weldProperties_weld_info_changed(DplWeld::I_Weld, valueList);
}


void MainWeldWidget::append_value(int type, QMap<QString, double> &valueList)
{
    if(type == DplWeld::TKY_Weld) {
        append_value_tky(type, valueList);
    } else {
        append_value_other(type, valueList);
    }
}


void MainWeldWidget::append_value_tky(int type, QMap<QString, double> &valueList)
{
    double T1 = valueList.value(TAG_T1);
    double Y1 = valueList.value(TAG_Y1);

    /* 相同type，判断是否超过显示最大值，若是，则更改thickness; 否则，初始化thickness */
    if(type == m_pbaseWeldInformation->get_type()) {
        /* 垂直标尺长度检测 */
        double Y2 = valueList.value(TAG_Y2);
        double tmpWeldHeight = T1 + MAX(Y1, Y2);

        if(tmpWeldHeight >= m_verticalSize.currentSize) {
            /* 增加垂直标尺长度 */
            m_verticalSize.currentSize += m_verticalSize.currentSize;

        } else if((tmpWeldHeight <= (m_verticalSize.currentSize / 2.0))
                   && ((m_verticalSize.currentSize / 2.0) >= m_verticalSize.defaultSize)) {
            /* 减少垂直标尺长度 */
            m_verticalSize.currentSize = m_verticalSize.currentSize / 2.0;
        }

        /* 水平标尺长度检测 */

        /* 计算X1，Y1；X2，Y2构成的三角型x坐标是否超出T1的矩形的左右边 */
        /*
         *      _____________________
         *      |                    |
         *      |                    |
         *      |____________________|
         *         \                /
         *          \              /
         */

        double X1 = valueList.value(TAG_X1);
        double X2 = valueList.value(TAG_X2);
        double Angle = valueList.value(TAG_ANGLE);
        double T2 = valueList.value(TAG_T2);

        double leftX = 0;
        double rightX = 0;

        double radianA = (M_PI / 180.0) * Angle;

        /* 中心 = m_currentHorizontalSize */

        /* 两条竖线宽度 */
        double width = (T2 / 2.0) / sin(radianA);

        /* X1,Y1 */
        /* tan(a) = Y1 / K1
         */
        double K1 = Y1 / tan(radianA);

        leftX = m_horizontalSize.currentSize - (width + (X1 - K1));

        /* X2,Y2 */
        /* tan(a) = Y2 / K2
         */
        double K2 = Y2 / tan(radianA);

        rightX = m_horizontalSize.currentSize + (width + K2 + X2);

        double minLeft  = 2 * m_horizontalSize.currentSize * DplWeld::TKYLeftScale / 100.0;
        double maxRight = 2 * m_horizontalSize.currentSize * (100.0 - DplWeld::TKYRightScale) / 100.0;

        /* 缩减后长度 */
        double targetCurrentSize = m_horizontalSize.currentSize / 2.0  - m_horizontalSize.currentSize * DplWeld::TKYRightScale / 100.0;

        if((leftX <= minLeft)
                || (rightX >= maxRight)) {

            m_horizontalSize.currentSize += m_horizontalSize.currentSize;

        } else if((width + X1 - K1) <= targetCurrentSize
                   && (width + K2 + X2) <= targetCurrentSize
                  && (m_horizontalSize.currentSize / 2.0) >= m_horizontalSize.defaultSize) {

           m_horizontalSize.currentSize = m_horizontalSize.currentSize / 2.0;

        }

    } else {

        double tmpThickness = T1 + 2 * Y1;

        m_verticalSize.defaultSize = tmpThickness;
        m_verticalSize.currentSize = tmpThickness;

        m_horizontalSize.defaultSize = DEFAULT_THICKNESS_SIZE;
        m_horizontalSize.currentSize = DEFAULT_THICKNESS_SIZE;
    }

    valueList.insert(TAG_WIDTH_SCALE,ui->bottomRuler->width() / (2 * m_horizontalSize.currentSize));
    valueList.insert(TAG_HEIGHT_SCALE,ui->leftRuler->height() / (m_verticalSize.currentSize / ((100 - DplWeld::TKYBottomScale - DplWeld::TKYTopScale) / 100.0)));
    valueList.insert(TAG_THICKNESS, m_verticalSize.currentSize);
}


void MainWeldWidget::append_value_other(int type, QMap<QString, double> &valueList)
{
    if(m_pbaseWeldInformation.isNull() || type != m_pbaseWeldInformation->get_type()) {

        m_verticalSize.defaultSize      = valueList.value(TAG_THICKNESS);;
        m_verticalSize.currentSize      = valueList.value(TAG_THICKNESS);
        m_horizontalSize.defaultSize    = DEFAULT_THICKNESS_SIZE;
        m_horizontalSize.currentSize    = DEFAULT_THICKNESS_SIZE;

    } else {

        double tmpWidth;

        if(type == DplWeld::VV_Weld) {
            tmpWidth = MAX(valueList.value(TAG_W1), valueList.value(TAG_W3));
        } else {
            tmpWidth = valueList.value(TAG_W1);
        }

        if(tmpWidth >= m_horizontalSize.currentSize) {
            m_horizontalSize.currentSize += m_horizontalSize.currentSize;
        } else if(tmpWidth <= (m_horizontalSize.currentSize / 2.0 )
                  && ((m_horizontalSize.currentSize / 2.0) >= m_horizontalSize.defaultSize)){
            m_horizontalSize.currentSize = m_horizontalSize.currentSize / 2.0;
        }
    }

    valueList.insert(TAG_WIDTH_SCALE,ui->bottomRuler->width() / (2 * m_horizontalSize.currentSize));
    valueList.insert(TAG_HEIGHT_SCALE,ui->leftRuler->height() / (m_verticalSize.currentSize / (DplWeld::WeldScale / 100.0)));
    valueList.insert(TAG_THICKNESS, m_verticalSize.currentSize);
}


bool MainWeldWidget::event(QEvent *event)
{
    if(event->type() == QEvent::Resize) {

        if(m_pbaseWeldInformation->get_type() == DplWeld::TKY_Weld) {

            m_pbaseWeldInformation->insert_value(TAG_WIDTH_SCALE,
                                                 ui->bottomRuler->width() / (2 * m_horizontalSize.currentSize));
            m_pbaseWeldInformation->insert_value(TAG_HEIGHT_SCALE,
                                                 ui->leftRuler->height() / \
                                                 (m_verticalSize.currentSize / ((100 - DplWeld::TKYBottomScale - DplWeld::TKYTopScale) / 100.0)));
        } else {

            m_pbaseWeldInformation->insert_value(TAG_WIDTH_SCALE,
                                                 ui->bottomRuler->width() / (2 * m_horizontalSize.currentSize));
            m_pbaseWeldInformation->insert_value(TAG_HEIGHT_SCALE,
                                                 ui->leftRuler->height() / (m_verticalSize.currentSize / (DplWeld::WeldScale / 100.0)));
        }
    }

    return QWidget::event(event);
}

