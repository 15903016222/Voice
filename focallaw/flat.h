/**
 * @file flat.h
 * @brief 平板工件类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-23
 */
#ifndef __FLAT_H__
#define __FLAT_H__

#include "specimen.h"

namespace DplFocallaw {

class FlatPrivate;
class FOCALLAWSHARED_EXPORT Flat : public Specimen
{
    Q_DECLARE_PRIVATE(Flat)
public:
    explicit Flat();
    ~Flat();

    Type type() const { return FLAT; }

    float length() const;

    void set_length(float val);

    float height() const;

    void set_height(float val);

    float width() const;

    void set_width(float val);

private:
    FlatPrivate *d_ptr;
    Q_DISABLE_COPY(Flat)
};

}

#endif // __FLAT_H__
