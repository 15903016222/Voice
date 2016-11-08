#include "sysinfo_dialog.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
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
    QGridLayout *layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    const QString description = tr(
        "<h3 style=\"text-align:center\">%1</h3>"
        "<table border=1 >"
        "<tr><th>Serial Number</th><td>%s</td></tr>"
        "<tr><th>Device Type</th><td>%s</td></tr>"
        "<tr><th>Device Version</th><td>%s</td></tr>"
        "<tr><th>Hardware Version</th><td>%d</td></tr>"
        "<tr><th>Software Version</th><td>%d.%d.%d</td></tr>"
        "<tr><th>Software Commit</th><td>%s</td></tr>"
        "<tr><th>Authentication Mode</th><td>%s</td></tr>"
        "<tr><th>Authentication Expire</th><td>%s</td></tr>"
        "<tr><th>Run Count</th><td>%d</td></tr>"
        "<tr><th>Run Time(s)</th><td>%d</td></tr>"
        "</table>")
            .arg(tr("System Infomation"));

    QLabel *copyRightLabel = new QLabel(description);
    copyRightLabel->setWordWrap(true);
    copyRightLabel->setOpenExternalLinks(true);
    copyRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
//    QTC_CHECK(closeButton);
    buttonBox->addButton(closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole | QDialogButtonBox::AcceptRole));
    connect(buttonBox , SIGNAL(rejected()), this, SLOT(reject()));

    QLabel *logoLabel = new QLabel;
    logoLabel->setPixmap(QPixmap(":/file/resources/logo.png"));

    layout->addWidget(logoLabel , 0, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(copyRightLabel, 1, 0);
    layout->addWidget(buttonBox, 2, 0, 1, 5);
}
