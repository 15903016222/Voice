#include "encoder_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

EncoderMenu::EncoderMenu(QWidget *parent) :
    BaseMenu(parent),
    m_encoderItem(new ComboMenuItem(this, tr("Encoder"))),
    m_encoderTypeItem(new ComboMenuItem(this, tr("Type"))),
    m_resolutionItem(new SpinMenuItem(this, tr("Resolution"), tr("Step/mm"))),
    m_polarityItem(new ComboMenuItem(this, tr("Polarity"))),
    m_originItem(new SpinMenuItem(this, tr("Origin"), tr("mm"))),
    m_presetItem(new LabelMenuItem(this, tr("Preset"))),
    m_enc(DplSource::Scan::instance()->encoder_x())
{
    ui->layout0->addWidget(m_encoderItem);
    ui->layout1->addWidget(m_encoderTypeItem);
    ui->layout2->addWidget(m_resolutionItem);
    ui->layout3->addWidget(m_polarityItem);
    ui->layout4->addWidget(m_originItem);
    ui->layout5->addWidget(m_presetItem);

    /* Encoder Menu Item */
    m_encoderItem->add_item(tr("Encoder 1"));
    m_encoderItem->add_item(tr("Encoder 2"));
    connect(m_encoderItem, SIGNAL(value_changed(int)),
            this, SLOT(do_encoderItem_changed(int)));

    /* Encoder Type menu item */
    m_encoderTypeItem->add_item(tr("Down"));
    m_encoderTypeItem->add_item(tr("Up"));
    m_encoderTypeItem->add_item(tr("Quad"));
    connect(m_encoderTypeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_encoderTypeItem_changed(int)));

    /* Resolution menu item */
    m_resolutionItem->set(0.01, 10000, 2, 0.01);
    connect(m_resolutionItem, SIGNAL(value_changed(double)),
            this, SLOT(do_resolutionItem_changed(double)));

    /* Polarity Menu Item */
    m_polarityItem->add_item(tr("Normal"));
    m_polarityItem->add_item(tr("Reverse"));
    connect(m_polarityItem, SIGNAL(value_changed(int)),
            this, SLOT(do_polarityItem_changed(int)));

    /* Origin Menu Item */
    m_originItem->set(0, 1000, 2, 0.01);
    connect(m_originItem, SIGNAL(value_changed(double)),
            this, SLOT(do_originItem_changed(double)));

    do_encoderItem_changed(0);
}

EncoderMenu::~EncoderMenu()
{
}

void EncoderMenu::do_encoderItem_changed(int pos)
{
    if (pos == 0) {
        m_enc = DplSource::Scan::instance()->encoder_x();
    } else {
        m_enc = DplSource::Scan::instance()->encoder_y();
    }

    m_encoderTypeItem->set_current_index(m_enc->mode());
    m_resolutionItem->set_value(m_enc->resolution());
    m_polarityItem->set_current_index(m_enc->polarity());
    m_originItem->set_value(m_enc->origin());
}

void EncoderMenu::do_encoderTypeItem_changed(int pos)
{
    m_enc->set_mode(static_cast<DplSource::Encoder::Mode>(pos));
}

void EncoderMenu::do_resolutionItem_changed(double val)
{
    m_enc->set_resolution(val);
}

void EncoderMenu::do_polarityItem_changed(int pos)
{
    m_enc->set_polarity(static_cast<DplSource::Encoder::Polarity>(pos));
}

void EncoderMenu::do_originItem_changed(double val)
{
    m_enc->set_origin(val);
}

}
