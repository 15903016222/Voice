#ifndef __GLOBAL_H__
#define __GLOBAL_H__

namespace Dpl {

#define US_TO_NS    (1000)
#define S_TO_US     (1000000)
#define S_TO_NS     (1000000000)

#define M_TO_MM     (1000)
#define MM_TO_UM    (1000)

template <typename T>
/**
 * @brief us_to_ns  微秒换算成纳秒
 * @param us        微秒
 * @return          纳秒值
 */
static inline T us_to_ns(T val) { return val * US_TO_NS; }

template <typename T>
/**
 * @brief ns_to_us  纳秒换算成微秒
 * @param val       纳秒
 * @return          微秒
 */
static inline T ns_to_us(T val) { return val/US_TO_NS; }


template <typename T>
/**
 * @brief s_to_us   秒换算成微秒
 * @param s         秒值
 * @return          微秒值
 */
static inline T s_to_us(T val) { return val * S_TO_US; }

template <typename T>
/**
 * @brief s_to_ns   秒换算成纳秒
 * @param val       秒值
 * @return          纳秒值
 */
static inline T s_to_ns(T val) { return val * S_TO_NS; }

template <typename T>
/**
 * @brief us_to_s   微秒换算成秒
 * @param val       微秒值
 * @return          秒值
 */
static inline T us_to_s(T val) { return val/S_TO_US; }

template <typename T>
/**
 * @brief ns_to_s   纳秒换算成秒
 * @param val       纳秒值
 * @return          秒值
 */
static inline T ns_to_s(T val) { return val/S_TO_NS; }

template <typename T>
/**
 * @brief mm_to_m   毫米换算成米
 * @param val       毫米值
 * @return          米值
 */
static inline T mm_to_m(T val) { return val/M_TO_MM; }

template <typename T>
/**
 * @brief m_to_mm   米换算成毫米
 * @param val       米值
 * @return          毫米值
 */
static inline T m_to_mm(T val) { return val * M_TO_MM; }

template <typename T>
/**
 * @brief um_to_mm  微米换算成毫米
 * @param val       微米值
 * @return          毫米值
 */
static inline T um_to_mm(T val) { return val / MM_TO_UM; }

template <typename T>
/**
 * @brief mm_to_um  毫米换算成微米
 * @param val       毫米值
 * @return          微米值
 */
static inline T mm_to_um(T val) { return val * MM_TO_UM; }
}

#endif /* end of __GLOBAL_H__ */
