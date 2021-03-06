/*****************************************************************************
 * Settings.h: generic preferences interface
 *****************************************************************************
 * Copyright (C) 2008-2010 VideoLAN
 *
 * Authors: Clement CHAVANCE <kinder@vlmc.org>
 *          Ludovic Fauvet <etix@l0cal.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "SettingsManager.h"

#include <QDialog>
#include <QString>
#include <QList>

class QDialogButtonBox;
class QLabel;
class QHBoxLayout;
class QAbstractButton;
class QScrollArea;

class   Panel;
class   PreferenceWidget;

class   Settings : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY( Settings )

    public:
        Settings( SettingsManager::Type type, QWidget* parent = 0, Qt::WindowFlags f = 0 );
        virtual ~Settings();

        void                        addCategorie( const QString& name,
                                                    SettingsManager::Type type,
                                                    const QIcon& icon,
                                                    const QString& label );
        void                        show();

    private:
        inline QHBoxLayout*         buildLayout();

    private:
        QDialogButtonBox*           m_buttons;
        QList<PreferenceWidget*>    m_pWidgets;
        PreferenceWidget*           m_currentWidget;
        Panel*                      m_panel;
        QLabel*                     m_title;
        QScrollArea*                m_configPanel;
        SettingsManager::Type       m_type;

    public slots:
        void    switchWidget( int index );

    private slots:
        void    buttonClicked( QAbstractButton* button );

    signals:
        void    loadSettings();
};

#endif // SETTINGS_H
