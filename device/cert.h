/**
 * @file cert.h
 * @brief certification
 * @author JakeYang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-06-06
 */

#ifndef __CERT_H__
#define __CERT_H__

#include <openssl/evp.h>

#include <QObject>
#include <QString>
#include <QDateTime>

class CertPrivate;

class Cert : QObject
{
public:
    enum AuthMode{
        INVALID,        /* 无效 */
        ALWAYS_VALID,   /* 无需认证 */
        RUN_COUNT,      /* 计数模式 */
        RUN_TIME,       /* 运行时间模式 */
        RUN_DATE        /* 有效期模式 */
    };

    Cert();
    ~Cert();

    bool load(const QString &certFile, const QString &pubPemFile);

    const QString &get_serial_number() const;
    AuthMode get_auth_mode() const;
    const QString &get_auth_mode_string() const;
    int get_expire() const;

private:
    CertPrivate *d;
};

#endif // CERT_H
