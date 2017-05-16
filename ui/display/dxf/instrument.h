#ifndef INSTRUMENT
#define INSTRUMENT

enum setup_PART_GEOMETRY
{
    setup_PART_GEOMETRY_FLAT = 0,
    setup_PART_GEOMETRY_OD,
    setup_PART_GEOMETRY_ID,
    setup_PART_GEOMETRY_BALL
};

enum setup_WELD_TYPE
{
    setup_WELD_I = 0,
    setup_WELD_V,
    setup_WELD_DV,
    setup_WELD_U,
    setup_WELD_DIFF_DV,
    setup_WELD_J,
    setup_WELD_VY,
    setup_WELD_NCC,
    setup_WELD_DXF,
    setup_WELD_MAX
};

enum setup_WELD_SYMMETRY_TYPE
{
    setup_WELD_SYMMETRY = 0,
    setup_WELD_LEFT,
    setup_WELD_RIGHT
};

struct MATERIAL
{
    char    strName[64];
    float   fVelocityLon;
    float   fVelocityTran;
    float   fDensity;
};

struct WELD
{
    setup_WELD_TYPE             eType;
    setup_WELD_SYMMETRY_TYPE    eSymmetry;

    float   weland_height;
    float   weland_offset;
    float   fizone_height;
    float   fizone_angle;
    float   fizone_radius;
    float   weldtype_pos;
    float   fizone_down_height;
    float   fizone_down_angle;
};

struct PART_CONFIG
{
    setup_PART_GEOMETRY eGeometry;

    float               afSize[4];
    MATERIAL            material;
    WELD                weld;
    char                strPartFile[256];
};

#endif // INSTRUMENT

