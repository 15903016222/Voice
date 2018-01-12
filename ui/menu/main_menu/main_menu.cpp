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
#include <QGraphicsOpacityEffect>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent),
    d(new MainMenuPrivate(this))
{
    setFocusPolicy(Qt::WheelFocus);

    setMinimumWidth(230);
    QHBoxLayout *topLayout = new QHBoxLayout(this);
    QVBoxLayout *subLayout = new QVBoxLayout();

    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);
    d->m_mainMenu->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    topLayout->addWidget(d->m_mainMenu,2);
    topLayout->addLayout(subLayout,1);

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

    d->set_opacity(85);
}

void MainMenu::show()
{
    d->m_mainMenu->show();
    d->m_curSubMenu->show();
    QWidget::show();
    d->m_mainMenu->setFocus();
}

void MainMenu::set_opacity(double val)
{
    d->set_opacity(val);
}

void MainMenu::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if (d->m_mainMenu->hasFocus()) {
            d->m_curSubMenu->setCurrentRow(0);
            d->m_curSubMenu->setFocus();
        } else if (d->m_curSubMenu->hasFocus()) {
            d->do_subMenu_pressed();
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

void MainMenu::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::LanguageChange) {
        d->retranslate_ui();
        return;
    }
    QWidget::changeEvent(e);
}

