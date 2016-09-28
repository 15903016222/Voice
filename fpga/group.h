#ifndef __GROUP_H__
#define __GROUP_H__

struct GroupData;

class Group
{
public:
    explicit Group(const int index);
    ~Group();

    int index(void) const { return m_index; }

    int freq_band(void) const;             /* 频带选择 */
    bool set_freq_band(int band);

    bool video_filter(void) const;         /* 视频滤波 */
    bool enable_video_filter(bool flag);

    enum RectifierType {
        RF,
        POSITIVE_HW,
        NEGATIVE_HW,
        FULL_WAVE
    };
    Group::RectifierType rectifier(void) const;
    bool set_rectifier(Group::RectifierType type);

    int compress_rato(void) const;
    bool set_compress_rato(int val, bool reflesh = false);

    int gain(void) const;
    bool set_gain(int gain, bool reflesh = false);

    int thickness_factor(void) const;
    bool set_thickness_factor(int factor, bool reflesh = false);

    bool ut1(void) const;
    bool enable_ut1(bool flag, bool reflesh = false);

    bool ut2(void) const;
    bool enable_ut2(bool flag, bool reflesh = false);

    bool pa(void) const;
    bool enable_pa(bool flag, bool reflesh = false);

    int sum_gain(void) const;
    bool set_sum_gain(int gain, bool reflesh = false);

    int sample_range(void) const;
    bool set_sample_range(int range, bool reflesh = false);

    int point_qty(void) const;
    bool set_point_qty(int qty, bool reflesh = false);

    int tcg_point_qty(void) const;
    bool set_tcg_point_qty(int qty, bool reflesh = false);

    bool tcg(void) const;
    bool enable_tcg(bool flag, bool reflesh = false);

    int rx_time(void) const;
    bool set_rx_time(int val, bool reflesh = false);

    int idel_time(void) const;
    bool set_idel_time(int val, bool reflesh = false);

    int gate_a_height(void) const;
    bool set_gate_a_height(int val, bool reflesh = false);

    int gate_a_logic(void) const;
    bool set_gate_a_logic(int val, bool reflesh = false);

    int gate_b_height(void) const;
    bool set_gate_b_height(int val, bool reflesh = false);

    int gate_b_logic(void) const;
    bool set_gate_b_logic(int val, bool reflesh = false);

    int gate_i_height(void) const;
    bool set_gate_i_height(int val, bool reflesh = false);

    int gate_i_logic(void) const;
    bool set_gate_i_logic(int val, bool reflesh = false);

    int thickness_min(void) const;
    bool set_thickness_min(int val, bool reflesh = false);

    int reject(void) const;
    bool set_reject(int val, bool reflesh = false);

    int sample_start(void) const;
    bool set_sample_start(int val, bool reflesh = false);

    int average(void) const;
    bool set_average(int val, bool reflesh = false);

    int thickness_max(void) const;
    bool set_thickness_max(int val, bool reflesh = false);

    int thickness_source(void) const;
    bool set_thickness_source(int val, bool reflesh = false);

    int tx_end(void) const;
    bool set_tx_end(int val, bool reflesh = false);

    int tx_start(void) const;
    bool set_tx_start(int val, bool reflesh = false);

    bool reflesh(void);
private:
    int m_index;
    GroupData *d;
};

#endif // __GROUP_H__
