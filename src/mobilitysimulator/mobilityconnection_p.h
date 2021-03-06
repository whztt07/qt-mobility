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

#ifndef QSIMULATORMOBILITY_H
#define QSIMULATORMOBILITY_H

#include "qmobilityglobal.h"
#include "mobilitysimulatorglobal.h"
#ifdef SIMULATOR_APPLICATION
#include "qsimulatordata_p.h"
#elif defined(QT_SIMULATOR)
#include "private/qsimulatordata_p.h"
#endif

#include <QtCore/QObject>
#include <QtCore/QVector>

QT_BEGIN_HEADER

#define SIMULATOR_MOBILITY_SERVERNAME "QtSimulator_Mobility_ServerName"

inline QString qt_mobilityServerName(const QString &simulatorVersion, qint64 pid)
{
    QString share = QLatin1String(SIMULATOR_MOBILITY_SERVERNAME) + simulatorVersion;
    share += QString::number(pid);
    return share;
}

class QLocalSocket;
class QLocalServer;

QTM_BEGIN_NAMESPACE

namespace Simulator {

class Q_MOBILITYSIMULATOR_EXPORT MobilityConnection : public QObject
{
    Q_OBJECT
public:
    MobilityConnection(QObject *parent = 0);
    ~MobilityConnection();

    static MobilityConnection *instance();
    void connectToSimulator();

    void addMessageHandler(QObject *handler);
    QLocalSocket *sendSocket();
    QLocalSocket *receiveSocket();
    VersionStruct simulatorVersion() { return mSimulatorVersion; }

public slots:
    void onReadyRead();

private:
    QLocalSocket *mSendSocket;
    QLocalSocket *mReceiveSocket;
    QByteArray mReadBuffer;
    QVector<QObject *> mHandlers;

    VersionStruct mSimulatorVersion;
};

} // end Simulator namespace

QTM_END_NAMESPACE
QT_END_HEADER

#endif // QSIMULATORMOBILITY_H
