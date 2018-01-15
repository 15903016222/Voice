/**
 * @file cursor.h
 * @brief 测量光标
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-20
 */
#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <QSharedPointer>

namespace DplMeasure {

class CursorPrivate;
class Cursor : public QObject
{
    Q_OBJECT
public:
    explicit Cursor(QObject *parent = 0);
    ~Cursor();

    /**
     * @brief amplitude_reference   获取参考光标位置的波幅值 %(r)
     * @return                      波幅值(%)
     */
    double amplitude_reference() const;

    /**
     * @brief amplitude_measurement 获取测量光标位置的波幅值 %(m)
     * @return                      波幅值(%)
     */
    double amplitude_measurement() const;

    /**
     * @brief ultrasound_reference  获取参考光标在超声轴上的位置 U(r)
     * @return                      位置(ns)
     */
    double ultrasound_reference() const;

    /**
     * @brief ultrasound_measurement    获取测量光标在超声轴上的位置 U(m)
     * @return                          位置(ns)
     */
    double ultrasound_measurement() const;

    /**
     * @brief scan_reference    获取扫查轴上参考光标的位置
     * @return                  位置(mm或s)
     */
    double scan_reference() const;

    /**
     * @brief scan_measurement  获取扫查轴上测量光标的位置
     * @return                  位置(mm)
     */
    double scan_measurement() const;

    /**
     * @brief index_reference   获取步进轴上参考光标的位置
     * @return                  位置(mm)
     */
    double index_reference() const;

    /**
     * @brief index_measurement 获取步进轴上测量光标的位置
     * @return                  位置(mm)
     */
    double index_measurement() const;

    /**
     * @brief is_visible    获取光标显示状态
     * @return              显示返回true，否则为false
     */
    bool is_visible() const;

    /**
     * @brief set_visible   设置光标显示状态
     * @param flag          true为显示，false为不显示
     */
    void set_visible(bool flag);

public slots:
    void set_amplitude_reference(double val);
    void set_amplitude_measurement(double val);
    void set_ultrasound_reference(double val);
    void set_ultrasound_measurement(double val);
    void set_scan_reference(double val);
    void set_scan_measurement(double val);
    void set_index_reference(double val);
    void set_index_measurement(double val);

signals:
    void amplitude_reference_changed(double val);
    void amplitude_measurement_changed(double val);
    void ultrasound_reference_changed(double val);
    void ultrasound_measurement_changed(double val);
    void scan_reference_changed(double val);
    void scan_measurement_changed(double val);
    void index_reference_changed(double val);
    void index_measurement_changed(double val);
    void visible_changed(bool flag);

public slots:

private:
    CursorPrivate *d;
};
typedef QSharedPointer<Cursor> CursorPointer;

}

#endif // __CURSOR_H__
