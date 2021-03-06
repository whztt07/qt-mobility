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

#include "InvokableBase.h"

class IMyInterfaceImpl : public IMyInterfaceBaseImpl
{
public:
    //successful part
    Q_INVOKABLE QString invokeFct16(bool arg1, QString arg2, int arg3);
    Q_INVOKABLE void invokeFct1();
    Q_INVOKABLE QString invokeFct12(bool* arg1, QString* arg2, int* arg3);
    Q_INVOKABLE QString invokeFct3(long arg1, double arg2, QObject arg3);

    Q_INVOKABLE QString invokeFct5(const long& arg1, const double& arg2, const QObject& arg3);
    Q_INVOKABLE QString invokeFct6(const bool& arg1, const QString& arg2, const int& arg3);
    Q_INVOKABLE QString invokeFct7(const long* arg1, const double* arg2, const QObject* arg3);
    Q_INVOKABLE QString invokeFct8(const bool* arg1, const QString* arg2, const int* arg3);

    Q_INVOKABLE QString invokeFct9(long& arg1, double& arg2, QObject& arg3);
    Q_INVOKABLE QString invokeFct10(bool& arg1, QString& arg2, int& arg3);
    Q_INVOKABLE QString invokeFct11(long* arg1, double* arg2, QObject* arg3);
    Q_INVOKABLE bool invokeFct2();

    Q_INVOKABLE QString invokeFct13(long arg1, double arg2, QObject arg3);
    Q_INVOKABLE QString invokeFct14(bool arg1, QString arg2, int arg3);
    Q_INVOKABLE QString invokeFct15(long arg1, double arg2, QObject arg3);
    Q_INVOKABLE QString invokeFct4(bool arg1, QString arg2, int arg3);
    
    //unsuccessful  part
    //Q_INVOKABLE QString invokeFct17(bool arg1, QString arg2, int arg3); //missing
    Q_INVOKABLE QString diffnames1(bool arg1, QString arg2, int arg3); //missing
    Q_INVOKABLE void overloadedDiffFct(int arg1, QString arg2, int arg3);
    void notInvokable();
};
