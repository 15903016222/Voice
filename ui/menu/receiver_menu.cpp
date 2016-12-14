#include "receiver_menu.h"

ReceiverMenu::ReceiverMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{

    m_filters.append(tr("none"));
    m_filters.append(tr("1M"));
    m_filters.append(tr("1.5M-2.5M"));
    m_filters.append(tr("3-5M"));
    m_filters.append(tr("7.5M"));
    m_filters.append(tr("more than 10M"));

    m_rectifiers.append(tr("RF"));
    m_rectifiers.append(tr("FW"));
    m_rectifiers.append(tr("HW+"));
    m_rectifiers.append(tr("HW-"));

    m_averagings.append(tr("1"));
    m_averagings.append(tr("2"));
    m_averagings.append(tr("4"));
    m_averagings.append(tr("8"));
    m_averagings.append(tr("16"));
}

void ReceiverMenu::show()
{
    receiver_item();
    filter_item();
    rectifier_item();
    video_filter_item();
    averagin_item();

    ui->subMenu_6->set_type(MenuItem::None);
}

void ReceiverMenu::hide()
{
}

void ReceiverMenu::receiver_item()
{
    ui->subMenu_1->set_label(tr("Receiver"));
}

void ReceiverMenu::filter_item()
{
    ui->subMenu_2->set_combo(tr("Filter"), m_filters);
}

void ReceiverMenu::rectifier_item()
{
    ui->subMenu_3->set_combo(tr("Rectifier"), m_rectifiers);
}

void ReceiverMenu::video_filter_item()
{
    ui->subMenu_4->set_combo(tr("Video Filter"), s_onOff);
}

void ReceiverMenu::averagin_item()
{
    ui->subMenu_5->set_combo(tr("Averaging"), m_averagings);
}


