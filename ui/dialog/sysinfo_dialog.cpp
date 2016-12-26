#include "sysinfo_dialog.h"
#include "device.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>

using namespace Ui::Dialog;

SysInfoDialog::SysInfoDialog(QWidget *parent) :
    QDialog(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);

    setWindowTitle(tr("System Infomation"));
    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint | Qt::Dialog);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    DplDevice::Device *dev = DplDevice::Device::get_instance();
    const QString info = tr(
                "<html><head><title>System Infomation</title>"
                "<style>"
                "body {background-color: #CCCCCC;}"
                "table, th, td {"
                "padding:5px;"
                "border: 1px solid black;"
                "border-collapse: collapse;"
                "}"
                "table {"
                "margin:5px;"
                "}"
                "th {"
                "text-align:left;"
                "background:#CCCCFF;"
                "}"
                "td {"
                "text-align:left;"
                "}"
                "h3 {"
                "text-align:center;"
                "}"
                "</style>"
                "</head>"
                "<body>"
                "<table border=1 cellspacing=1 cellpadding=0 >"
                "<tr><th>Serial Number</th><td>%1</td></tr>"
                "<tr><th>Device Type</th><td>%2</td></tr>"
                "<tr><th>Device Version</th><td>%3</td></tr>"
                "<tr><th>Hardware Version</th><td></td></tr>"
                "<tr><th>Software Version</th><td></td></tr>"
                "<tr><th>Software Commit</th><td></td></tr>"
                "<tr><th>Cert Info</th><td>%4</td></tr>"
//                "<tr><th>Run Count</th><td>%5</td></tr>"
//                "<tr><th>Run Time(s)</th><td>%6</td></tr>"
                "</table>"
                "</body>"
                "</html>")
            .arg(dev->serial_number())
            .arg(dev->type_string())
            .arg(dev->version())
            .arg(dev->get_cert().info());
//            .arg(QString::number((double)(dev->run_count()), 'f', 0))
//            .arg(QString::number((double)(dev->run_time()), 'f', 0));

    QLabel *infoTitleLabel = new QLabel(QString("<h3>%1</3>").arg(tr("System Infomation")));
    QLabel *infoLabel = new QLabel(info);
    infoLabel->setAlignment(Qt::AlignLeft);
    infoLabel->setWordWrap(true);
    infoLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
//    QTC_CHECK(closeButton);
    buttonBox->addButton(closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole | QDialogButtonBox::AcceptRole));
    connect(buttonBox , SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget(infoTitleLabel, 0, Qt::AlignCenter);
    layout->addWidget(infoLabel);
    layout->addWidget(buttonBox, 0, Qt::AlignRight);
}
