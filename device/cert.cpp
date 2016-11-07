/**
 * @file cert.cpp
 * @brief certification
 * @author JakeYang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-06-06
 */

#include "cert.h"

#include <QFile>
#include <QTextStream>
#include <QSharedPointer>
#include <QXmlStreamReader>
#include <QDateTime>
#include <QDebug>


class CertPrivate
{
public:
    CertPrivate();

    QByteArray read_cert_file(const QString &certFile, const QString &pubPemFile);

    QString m_serialNo;
    QString m_devType;
    QString m_authMode;
    uint m_expire;

    static QMap<QString, Cert::AuthMode> s_modeMap;
};

QMap<QString, Cert::AuthMode> CertPrivate::s_modeMap;

CertPrivate::CertPrivate()
{
    m_serialNo = "00000000-00000000-00000000-00000000";
    m_devType  = "16-64-TOFD";
    m_authMode = "INVAILD";
    m_expire = 0;

    if (s_modeMap.isEmpty()) {
        s_modeMap.insert("Invalid", Cert::INVALID);
        s_modeMap.insert("Always Valid", Cert::ALWAYS_VALID);
        s_modeMap.insert("Valid Count", Cert::VALID_COUNT);
        s_modeMap.insert("Valid Time", Cert::VALID_TIME);
        s_modeMap.insert("Valid Date", Cert::VALID_DATE);
    }
}

static inline void do_close_file_later(FILE *fp)
{
    if (fp) {
        ::fclose(fp);
    }
}

QByteArray CertPrivate::read_cert_file(const QString &certFile, const QString &pubPemFile)
{
    QString cmd;
    cmd.sprintf("rsautl -verify -inkey %s -pubin -in %s", pubPemFile.toUtf8().data(), certFile.toUtf8().data());

    QSharedPointer<FILE> fp(::popen(cmd.toUtf8().data(), "r"),
                             do_close_file_later);
    if (fp.isNull()) {
        qWarning()<<"Cann't open"<<certFile;
        return NULL;
    }

    QTextStream out(fp.data());
    return out.readAll().toUtf8();
}


Cert::Cert()
    :d(new CertPrivate())
{
}

Cert::~Cert()
{
    delete d;
}

bool Cert::load(const QString &certFile, const QString &pubPemFile)
{
    if (certFile.isEmpty() || pubPemFile.isEmpty()) {
        qWarning()<<"cert file or public pem file is not specified";
        return false;
    }

    QByteArray data = d->read_cert_file(certFile, pubPemFile);
    if (data.isEmpty()) {
        return false;
    }

    QXmlStreamReader xml(data);
    while ( !xml.atEnd() || !xml.hasError()) {
        if ( ! xml.readNextStartElement() ) {
            break;
        }
        if (xml.name() == "ID") {
            d->m_serialNo = xml.readElementText();
        } else if(xml.name() == "Type") {
            d->m_devType = xml.readElementText();
        } else if (xml.name() == "AUTH") {
            d->m_authMode = xml.attributes().value("mode").toString();

            if (get_auth_mode() == Cert::VALID_DATE) {
                d->m_expire = QDateTime::fromString(xml.readElementText(), "yyyy/M/d H:m").toTime_t();
            } else {
                d->m_expire = xml.readElementText().toInt();
            }
        }
    }
    if (xml.hasError()) {
        qWarning()<<xml.errorString();
        return false;
    }
    return true;
}

const QString &Cert::get_serial_number() const
{
    return d->m_serialNo;
}

const QString &Cert::get_device_type() const
{
    return d->m_devType;
}

Cert::AuthMode Cert::get_auth_mode() const
{
    return CertPrivate::s_modeMap[d->m_authMode];
}

const QString &Cert::get_auth_mode_string() const
{
    return d->m_authMode;
}

int Cert::get_expire() const
{
    return d->m_expire;
}
