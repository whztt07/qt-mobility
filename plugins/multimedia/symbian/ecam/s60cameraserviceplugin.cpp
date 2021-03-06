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

#include <QtCore/qstring.h>

#include "s60cameraserviceplugin.h"
#ifdef QMEDIA_SYMBIAN_CAMERA
#include "s60cameraservice.h"
#endif

QStringList S60CameraServicePlugin::keys() const
{
    QStringList list;
#ifdef QMEDIA_SYMBIAN_CAMERA
    list << QLatin1String(Q_MEDIASERVICE_CAMERA);
#endif
    return list;
}

QMediaService* S60CameraServicePlugin::create(QString const& key)
{
#ifdef QMEDIA_SYMBIAN_CAMERA
    if (key == QLatin1String(Q_MEDIASERVICE_CAMERA))
        return new S60CameraService;
#endif
    return 0;
}

void S60CameraServicePlugin::release(QMediaService *service)
{
    delete service;
}

QList<QByteArray> S60CameraServicePlugin::devices(const QByteArray &service) const
{
#ifdef QMEDIA_SYMBIAN_CAMERA
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        return m_cameraDevices;
    }
#endif
    return QList<QByteArray>();
}

QString S60CameraServicePlugin::deviceDescription(const QByteArray &service, const QByteArray &device)
{
#ifdef QMEDIA_SYMBIAN_CAMERA
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        for (int i=0; i<m_cameraDevices.count(); i++)
            if (m_cameraDevices[i] == device)
                return m_cameraDescriptions[i];
    }
#endif
    return QString();
}

void S60CameraServicePlugin::updateDevices() const
{
#ifdef QMEDIA_SYMBIAN_CAMERA
    m_cameraDevices.clear();
    m_cameraDescriptions.clear();
    for (int i=0; i < S60CameraService::deviceCount(); i ++) {
        m_cameraDevices.append(S60CameraService::deviceName(i).toUtf8());
        m_cameraDescriptions.append(S60CameraService::deviceDescription(i));
    }
#endif
}

Q_EXPORT_PLUGIN2(qtmultimedia_ecamngine, S60CameraServicePlugin);

// End of file

