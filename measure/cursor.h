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
    float amplitude_reference() const;

    /**
     * @brief set_amplitude_reference   设置参考光标位置的波幅值 %(r)
     * @param val                       波幅值(%)
     */
    void set_amplitude_reference(float val);

    /**
     * @brief amplitude_measurement 获取测量光标位置的波幅值 %(m)
     * @return                      波幅值(%)
     */
    float amplitude_measurement() const;

    /**
     * @brief set_amplitude_measurement 设置测量光标位置的波幅值 %(m)
     * @param val                       波幅值(%)
     */
    void set_amplitude_measurement(float val);

    /**
     * @brief ultrasound_reference  获取参考光标在超声轴上的位置 U(r)
     * @return                      位置(ns)
     */
    float ultrasound_reference() const;

    /**
     * @brief set_ultrasound_reference  设置参考光标在超声轴上的位置 U(r)
     * @param val                       位置(ns)
     */
    void set_ultrasound_reference(float val);

    /**
     * @brief ultrasound_measurement    获取测量光标在超声轴上的位置 U(m)
     * @return                          位置(ns)
     */
    float ultrasound_measurement() const;

    /**
     * @brief set_ultrasound_measurement    设置测量光标在超声轴上的位置 U(m)
     * @param val                           位置(ns)
     */
    void set_ultrasound_measurement(float val);

    /**
     * @brief scan_reference    获取扫查轴上参考光标的位置
     * @return                  位置(mm)
     */
    float scan_reference() const;

    /**
     * @brief set_scan_reference    设置扫查轴上参考光标的位置
     * @param val                   位置(mm)
     */
    void set_scan_reference(float val);

    /**
     * @brief scan_measurement  获取扫查轴上测量光标的位置
     * @return                  位置(mm)
     */
    float scan_measurement() const;

    /**
     * @brief set_scan_measurement  设置扫查轴上测量光标的位置
     * @param val                   位置(mm)
     */
    void set_scan_measurement(float val);

    /**
     * @brief index_reference   获取步进轴上参考光标的位置
     * @return                  位置(mm)
     */
    float index_reference() const;

    /**
     * @brief set_index_reference   设置步进轴参考光标的位置
     * @param val                   位置(mm)
     */
    void set_index_reference(float val);

    /**
     * @brief index_measurement 获取步进轴上测量光标的位置
     * @return                  位置(mm)
     */
    float index_measurement() const;

    /**
     * @brief set_index_measurement 设置步进轴上测量光标的益
     * @param val                   位置(mm)
     */
    void set_index_measurement(float val);

signals:
    void amplitude_reference_changed(float val);
    void amplitude_measurement_changed(float val);
    void ultrasound_reference_changed(float val);
    void ultrasound_measurement_changed(float val);
    void scan_reference_changed(float val);
    void scan_measurement_changed(float val);
    void index_reference_changed(float val);
    void index_measurement_changed(float val);

public slots:

private:
    CursorPrivate *d;
};
typedef QSharedPointer<Cursor> CursorPointer;

}

#endif // __CURSOR_H__
