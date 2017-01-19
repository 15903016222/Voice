#include "wedge.h"

namespace DplProbe {

struct WedgeData
{
    char    res0;
    qint8   type;           /* 1 是L 2 是 S */
    char    res1;
    char    model[20];      /* 共用 楔块名字 */
    char    serial[20];     /* 共用 楔块名字 */
    quint16 angle;          /* 共用 角度单位0.1度 */
    quint16 res2;
    quint16 probeDelay;     /* UT ns为单位 */
    char    res3;
    char	res4;           /* UT 1 SW 0 LW*/
    int	Ref_point;          /* UT 使用 */
    char    res5;
    qint32	Height;			/* 单位微米 */
    unsigned int	Velocity_UT;
    unsigned int	A8;
    unsigned int	Velocity_PA;	/* 速度 mm/s */
    char	Orientation;	/* 1 Normal 0 reversal*/
    char	A4[3];
    int	Primary_offset;	/* 微米 */
    unsigned int	Secondary_offset;	/* 微米 */
    unsigned int    length;
    int	A6[106];
};

Wedge::Wedge(QObject *parent) :
    QObject(parent)
{
    m_delay     = 0;

    m_waveType = Longitudinal;
    m_orientation = Normal;
    m_velocity  = 0;
    m_primaryOffset = 0.0;
    m_secondaryOffset = 0.0;
    m_height    = 0.0;
    m_length    = 0.0;
    m_refPoint  = 0.0;
}

Wedge::~Wedge()
{

}

bool Wedge::load(const QString &fileName)
{
    return true;
}

}
