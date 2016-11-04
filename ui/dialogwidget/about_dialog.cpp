#include "about_dialog.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>

using namespace Ui;
using namespace Ui::Dialog;

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255, 255, 255));
    setPalette(palette);

    setWindowTitle(tr("About Device"));
    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint | Qt::Dialog);
    QGridLayout *layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    const QString description = tr(
        "<h3 style=\"text-align:center\">%1</h3>"
        "&nbsp;&nbsp;&nbsp;&nbsp;Phascan has a powerful detection capability, "
        "can achieve a variety of scanning mode and focus mode,"
        "which greatly improves the detection reliability."
        "<p style=\"font-size:14px; text-align:center;\">Copyright 2008-2016 Doppler. All rights reserved.</p>")
        .arg("Phascan");

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

bool AboutDialog::event(QEvent *event)
{
    if (event->type() == QEvent::ShortcutOverride) {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Escape && !ke->modifiers()) {
            ke->accept();
            return true;
        }
    }
    return QDialog::event(event);
}
