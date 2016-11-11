#include "tcg.h"

#include "fpga_spi.h"

const int Tcg::MAX_POINTS = 16;

static int BEAM_REGS_NUM = 48;
static int TCG_REGS_NUM = 32;

struct TcgPoint
{
    /* TCG (0) */
     quint32 position :20;      /* bit:0-19     当前点位置,单位10ns */
     quint32 res1     :1;       /* bit:20       保留 */
     quint32 pregain  :10;      /* bit:21-30    */
     quint32 res2     :1;       /* bit:31       保留 */
     /* TCG (1) */
     quint32 slope    :22;      /* bit:0-21     */
     quint32 res3     :9;       /* bit:22-30 */
     quint32 flag     :1;       /* bit:31 */
};

struct TcgData
{
    /* reg (-1) */
    quint32 offset      :16;    /* bit:0-15  地址的偏移 */
    quint32 res         :12;    /* bit:16-27 保留*/
    quint32 chip        :4;     /* bit:28-31 片选取值0b0001 */

    TcgPoint tcgPoint[Tcg::MAX_POINTS];
};

Tcg::Tcg(const int index)
    :m_index(index), d(new TcgData())
{
    d->chip = 0b0001;
    d->offset = BEAM_REGS_NUM + (BEAM_REGS_NUM+TCG_REGS_NUM)*index;
}

Tcg::~Tcg()
{
    delete d;
}

quint32 Tcg::tcg_position(quint32 point) const
{
    if (point >= MAX_POINTS) {
        return 0;
    }

    return d->tcgPoint[point].position;
}

bool Tcg::set_tcg_position(quint32 point, quint32 val)
{
    if (point >= MAX_POINTS) {
        return false;
    }
    d->tcgPoint[point].position = val;
    return true;
}

quint32 Tcg::tcg_slope(quint32 point) const
{
    if (point >= MAX_POINTS) {
        return 0;
    }
    return d->tcgPoint[point].slope;
}

bool Tcg::set_tcg_slope(quint32 point, quint32 val)
{
    if (point >= MAX_POINTS) {
        return false;
    }
    d->tcgPoint[point].slope = val;
    return true;
}

bool Tcg::tcg_flag(quint32 point) const
{
    if (point >= MAX_POINTS) {
        return false;
    }
    return d->tcgPoint[point].flag;
}

bool Tcg::set_tcg_flag(quint32 point, bool flag)
{
    if (point >= MAX_POINTS) {
        return false;
    }
    d->tcgPoint[point].flag = flag;
    return true;
}

bool Tcg::reflesh() const
{
    return FpgaSpi::get_spi()->send((char *)d, sizeof(TcgData));
}
