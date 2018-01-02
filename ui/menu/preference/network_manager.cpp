#include "network_manager.h"

#include <QDebug>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QtNetwork/QNetworkInterface>
#else
#include <QNetworkInterface>
#endif
#include <QFile>
#include <QStringList>
#include <QRegExp>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace DplPreferenceMenu {

static const QString s_cardName        = "usb0";
static const QString s_interfaces      = "/etc/network/interfaces";
static const QString s_ip_address_tag  = "address ";
static const QString s_subnet_mask_tag = "netmask ";

NetworkManager::NetworkManager()
{

}

QString NetworkManager::ip_str()
{
    QList<QHostAddress> addressList = QNetworkInterface::allAddresses();

    foreach (QHostAddress address, addressList) {
        if(address != QHostAddress::Null
                && address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress::LocalHost) {

            if(address.toString().contains("127.0")) {
                continue;
            }
            return address.toString();
        }
    }

    return "";
}


bool NetworkManager::set_ip(const QString &newIp)
{
    if(newIp.isEmpty()) {
        return false;
    }

    struct sockaddr_in  sockaddrIn;
    struct ifreq        ifr;
    int fd;

    ::bzero(&ifr, sizeof(struct ifreq));
    fd = ::socket(AF_INET, SOCK_DGRAM, 0);

    if(fd < 0) {
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " init socket failed!";
        return false;
    }

    ::strncpy(ifr.ifr_name, s_cardName.toStdString().data(), IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    ::memset(&sockaddrIn, 0, sizeof(sockaddrIn));

    sockaddrIn.sin_family = AF_INET;
    sockaddrIn.sin_addr.s_addr = ::inet_addr(newIp.toStdString().data());

    ::memcpy(&ifr.ifr_addr, &sockaddrIn, sizeof(sockaddrIn));

    if(ioctl(fd, SIOCSIFADDR, &ifr) < 0) {
        set_config_file_by_tag(s_ip_address_tag, newIp);
        ::close(fd);
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " ioctl failed!";
        return false;
    }

    ::close(fd);
    return true;
}


QString NetworkManager::mask_str()
{
    int fd = -1;
    char netMask[50] = {0};

    fd = ::socket(PF_INET, SOCK_STREAM, 0);

    if(fd < 0) {
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " init socket failed!";
        return "";
    }

    struct ifreq ifreqMask;

    ::memset(&ifreqMask, 0, sizeof(struct ifreq));
    ::strncpy(ifreqMask.ifr_name, s_cardName.toStdString().data(),sizeof(ifreqMask.ifr_name));

    if (::ioctl(fd, SIOCGIFNETMASK, &ifreqMask) < 0 ) {
        close(fd);
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " ioctl failed!";
        return "";
    }

    ::strcpy((char*)netMask, inet_ntoa(((struct sockaddr_in*)&(ifreqMask.ifr_netmask))->sin_addr));

    ::close(fd);

    return QString(netMask);
}


bool NetworkManager::set_mask(const QString &mask)
{
    if(mask.isEmpty()) {
        return false;
    }

    int fd;
    struct ifreq        ifreqMask;
    struct sockaddr_in  *sockaddIn;
    fd = socket(PF_INET, SOCK_STREAM, 0);

    if(fd < 0) {
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " init socket failed!";
        return false;
    }

    ::memset(&ifreqMask, 0, sizeof(struct ifreq));
    ::strncpy(ifreqMask.ifr_name, s_cardName.toStdString().data(), sizeof(ifreqMask.ifr_name));

    sockaddIn = (struct sockaddr_in*)& ifreqMask.ifr_addr;
    sockaddIn->sin_family = AF_INET;

    ::inet_pton(AF_INET, mask.toStdString().data(), &sockaddIn->sin_addr);

    if(::ioctl(fd, SIOCSIFNETMASK, &ifreqMask) < 0) {
        ::close(fd);
        qDebug() << "[" << __FUNCTION__ << "]"
                 << " ioctl failed!";
        return false;
    }

    ::close(fd);

    return set_config_file_by_tag(s_subnet_mask_tag, mask);
}


bool NetworkManager::set_config_file_by_tag(const QString &tag, const QString &info)
{
    QFile configFile(s_interfaces);

    if(!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream stream(&configFile);
    QStringList stringList = stream.readAll().split('\n');
    configFile.close();

    if(!configFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    QTextStream textStream(&configFile);
    QString line;
    bool ret = false;
    for(int i = 0; i < stringList.size(); ++i) {

        line = stringList.at(i);

        if(line.contains(tag)) {
            line.replace(QRegExp(QString(tag) + ".*"),
                         QString(tag) + info);
            ret = true;
        }

        if((i + 1) == stringList.size()) {
            textStream << line;
        } else {
            textStream << line << '\n';
        }
    }

    configFile.close();
    return ret;
}

}

