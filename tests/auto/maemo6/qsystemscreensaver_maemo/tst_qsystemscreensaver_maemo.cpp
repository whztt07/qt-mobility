/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

//TESTED_COMPONENT=src/systeminfo

#include <QtTest/QtTest>
#include <QDebug>
#include "qsysteminfo.h"

QTM_USE_NAMESPACE

class tst_QSystemScreenSaver : public QObject
{
    Q_OBJECT

public:
    tst_QSystemScreenSaver();
    virtual ~tst_QSystemScreenSaver();

private slots:
    void testScreenBlanking();

private:
    QSystemScreenSaver *m_systemScreenSaver;
};

tst_QSystemScreenSaver::tst_QSystemScreenSaver()
{
    m_systemScreenSaver = new QSystemScreenSaver(this);
}

tst_QSystemScreenSaver::~tst_QSystemScreenSaver()
{
}

/*
 * The test cases
 */
void tst_QSystemScreenSaver::testScreenBlanking()
{
    {
        QSystemScreenSaver s1;
        s1.setScreenSaverInhibit();
        QTest::qWait(2000);

        QVERIFY(s1.screenSaverInhibited());

        // Verify that another QSystemScreenSaver instance gets the correct display state
        QVERIFY(m_systemScreenSaver->screenSaverInhibited());
     }

     // Now s1 goes out of the scope and is destroyed. The screen
     // should eventually be blank again. Let's wait max 120s.
     int MAX_BLANK_TIMEOUT=120;
     int timeLeft=MAX_BLANK_TIMEOUT;
     while (timeLeft > 0) {
         if (!m_systemScreenSaver->screenSaverInhibited()) {
             // OK!
             return;
         }
         qDebug() << "Waiting max " << MAX_BLANK_TIMEOUT << "s for screen to go blank, " << timeLeft << " left.";
         QTest::qWait(10000);
         timeLeft -= 10;
     }
     // The screen didn't go blank. The screen inhibitation is still active? Or something wrong with MCE?
     QVERIFY(false);
}

QTEST_MAIN(tst_QSystemScreenSaver)
#include "tst_qsystemscreensaver_maemo.moc"
