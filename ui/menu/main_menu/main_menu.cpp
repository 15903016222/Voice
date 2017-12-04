/**
 * @file main_menu.cpp
 * @brief main menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "main_menu.h"
#include "main_menu_p.h"

#include <QVBoxLayout>
#include <QKeyEvent>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent),
    d(new MainMenuPrivate(this))
{
    setFocusPolicy(Qt::WheelFocus);

    setMinimumHeight(d->m_mainMenu->height());
    setMaximumHeight(d->m_mainMenu->height());
    setMinimumWidth(260);

    QHBoxLayout *topLayout = new QHBoxLayout(this);
    QVBoxLayout *subLayout = new QVBoxLayout();

    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);
    d->m_mainMenu->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    topLayout->addWidget(d->m_mainMenu,2);
    topLayout->addLayout(subLayout, 1);

    subLayout->setContentsMargins(0, 0, 0, 0);
    subLayout->setSpacing(0);
    subLayout->addSpacerItem(d->m_topSpaceItem);
    subLayout->addWidget(d->m_utSettingMenu);
    subLayout->addWidget(d->m_gateCurvesMenu);
    subLayout->addWidget(d->m_displayMenu);
    subLayout->addWidget(d->m_probePartMenu);
    subLayout->addWidget(d->m_focallawMenu);
    subLayout->addWidget(d->m_scanMenu);
    subLayout->addWidget(d->m_measureMenu);
    subLayout->addWidget(d->m_fileReportMenu);
    subLayout->addWidget(d->m_preferenceMenu);
    subLayout->addSpacerItem(d->m_bottomSpaceItem);
//    setSpacing(0);
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->setContentsMargins(0, 0, 0, 0);

//    connect(this, SIGNAL(currentRowChanged(int)),
    //            this, SLOT(do_currentRowChanged(int)));
}

void MainMenu::show()
{
    QWidget::show();
    d->m_mainMenu->setFocus();

}

void MainMenu::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if (d->m_mainMenu->hasFocus()) {
            d->m_curSubMenu->setCurrentRow(0);
            d->m_curSubMenu->setFocus();
        } else if (d->m_curSubMenu->hasFocus()) {
            d->do_subMenu_itemClicked();
        }
        return;
    } else if(e->key() == Qt::Key_Back || e->key() == Qt::Key_Escape) {
        if(d->m_curSubMenu->hasFocus()) {
            d->m_curSubMenu->setCurrentRow(-1);
            d->m_mainMenu->setFocus();
        } else if(d->m_mainMenu->hasFocus()) {
            hide();
        }
        return;
    }
    QWidget::keyPressEvent(e);
}

