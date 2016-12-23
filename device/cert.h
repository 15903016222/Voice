/**
 * @file cert.h
 * @brief certification
 * @author JakeYang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-06-06
 */

#ifndef __CERT_H__
#define __CERT_H__

#include <QString>

namespace DplDevice {

class CertPrivate;

class Cert
{
public:
    enum AuthMode{
        INVALID,        /* 无效 */
        ALWAYS_VALID,   /* 无需认证 */
        VALID_COUNT,    /* 计数模式 */
        VALID_TIME,     /* 运行时间模式 */
        VALID_DATE      /* 有效期模式 */
    };

    Cert();
    ~Cert();

    bool load(const QString &certFile, const QString &pubPemFile);

    const QString &get_serial_number() const;

    const QString &get_device_type() const;

    AuthMode get_auth_mode() const;
    const QString &get_auth_mode_string() const;

    int get_expire() const;

    QString info() const;

private:
    CertPrivate *d;
};

}
#endif // __ERT_H__
