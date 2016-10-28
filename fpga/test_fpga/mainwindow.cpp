#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

#define show_warning() { QMessageBox::warning(this, "Global Setting", __func__); }
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_fpga = Fpga::get_fpga();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxPaLawQty_editingFinished()
{
    if ( ! m_fpga->set_pa_law_qty(ui->spinBoxPaLawQty->value(), true) ) {
        show_warning();
    }
}

void MainWindow::on_spinBoxUtLawQty_editingFinished()
{
    if ( ! m_fpga->set_ut_law_qty(ui->spinBoxUtLawQty->value(), true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderXPolarity_currentIndexChanged(int index)
{
    bool ret = false;
    if (index == 1) {
        ret = m_fpga->set_encoder_x(m_fpga->encoder_x_mode(), Fpga::INVERSE, true);
    } else {
        ret = m_fpga->set_encoder_x(m_fpga->encoder_x_mode(), Fpga::NORMAL, true);
    }
    if (! ret) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderXMode_currentIndexChanged(int index)
{
    if (! m_fpga->set_encoder_x((Fpga::EncoderMode)index, m_fpga->encoder_x_polarity(), true) ) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderYPolarity_currentIndexChanged(int index)
{
    bool ret = false;
    if (index == 1) {
        ret = m_fpga->set_encoder_y(m_fpga->encoder_y_mode(), Fpga::INVERSE, true);
    } else {
        ret = m_fpga->set_encoder_y(m_fpga->encoder_y_mode(), Fpga::NORMAL, true);
    }
    if (! ret) {
        show_warning();
    }
}

void MainWindow::on_comboBoxEncoderYMode_currentIndexChanged(int index)
{
    if (! m_fpga->set_encoder_y((Fpga::EncoderMode)index, m_fpga->encoder_y_polarity(), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1Twin_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut1_twin((!index), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2Twin_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut2_twin((!index), true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1TxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut1_tx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt1RxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut1_rx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2TxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut2_tx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUt2RxDamping_currentIndexChanged(int index)
{
    if (!m_fpga->set_ut2_rx_damping((Fpga::DampingType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxUtVoltage_currentIndexChanged(int index)
{
    if (! m_fpga->set_ut_voltage((Fpga::VoltageType)index, true)) {
        show_warning();
    }
}

void MainWindow::on_comboBoxPaVoltage_currentIndexChanged(int index)
{
    if (! m_fpga->set_pa_voltage((Fpga::VoltageType)index, true)) {
        show_warning();
    }
}

