/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Solutions Commercial License Agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** Please note Third Party Software included with Qt Solutions may impose
** additional restrictions and it is the user's responsibility to ensure
** that they have met the licensing requirements of the GPL, LGPL, or Qt
** Solutions Commercial license and the relevant license of the Third
** Party Software they are using.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QDebug>
#include <QCoreApplication>
#include "buzzer.h"

Buzzer::Buzzer() : m_oceaning(false)
{
    // First: Define a generic "rumble" custom effect.
    // we start with an intensity of zero (nothing).
    m_rumble.setAttackIntensity(0.0);
    // over 250 msec, it ramps up to the peak intensity.
    m_rumble.setAttackTime(250);
    // it has a peak intensity of one (maximum).
    m_rumble.setIntensity(1.0);
    // and stays at peak intensity for 100 msec.
    m_rumble.setDuration(100);
    // over 250 msec, it ramps back down to the fade intensity.
    m_rumble.setFadeTime(250);
    // it has a fade intensity of zero (nothing).
    m_rumble.setFadeIntensity(0.0);

    // Second: Define a generic, periodic "ocean waves" effect.
    // we start with an intensity of zero (nothing).
    m_ocean.setAttackIntensity(0.0);
    // over 450 msec, it ramps up to the peak intensity.
    m_ocean.setAttackTime(450);
    // it has a peak intensity of 0.80 (close to maximum)
    m_ocean.setIntensity(0.8);
    // and it stays at peak intensity for 150 msec
    m_ocean.setDuration(150);
    // over 900 milliseconds, it ramps down to the fade intensity.
    m_ocean.setFadeTime(900);
    // it has a fade intensity of 0.05 (slight)
    m_ocean.setFadeIntensity(0.05);
    // it is a periodic effect, with a period of 1.5 seconds
    m_ocean.setPeriod(1500);
}

void Buzzer::rumble()
{
    m_rumble.start();
}

void Buzzer::setOceaning(bool on)
{
    if (on != m_oceaning) {
        if (on)
            m_ocean.start();
        else
            m_ocean.stop();
        m_oceaning = on;
        emit oceaningChanged();
    }
}

bool Buzzer::oceaning() const
{
    return m_oceaning;
}

void Buzzer::click()
{
    QFeedbackEffect::playThemeEffect(QFeedbackEffect::ThemeBasicButton);
}

void Buzzer::oops()
{
    QFeedbackEffect::playThemeEffect(QFeedbackEffect::ThemeNegativeTacticon);
}

void Buzzer::quit()
{
    QCoreApplication::quit();
}