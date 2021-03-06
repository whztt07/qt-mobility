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
#include <QtCore/qdebug.h>
#include <QtCore/QFile>

#include "dsserviceplugin.h"


#ifdef QMEDIA_DIRECTSHOW_CAMERA
#include <dshow.h>
#include "dscameraservice.h"
#endif

#ifdef QMEDIA_DIRECTSHOW_PLAYER
#include "directshowplayerservice.h"
#endif

#include <qmediaserviceprovider.h>


#ifdef QMEDIA_DIRECTSHOW_CAMERA

extern const CLSID CLSID_VideoInputDeviceCategory;


#ifndef _STRSAFE_H_INCLUDED_
#include <tchar.h>
#endif
#include <dshow.h>
#include <objbase.h>
#include <initguid.h>
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "ole32.lib")
#include <windows.h>
#include <ocidl.h>
#endif

QT_USE_NAMESPACE

QStringList DSServicePlugin::keys() const
{
    return QStringList()
#ifdef QMEDIA_DIRECTSHOW_CAMERA
            << QLatin1String(Q_MEDIASERVICE_CAMERA)
#endif
#ifdef QMEDIA_DIRECTSHOW_PLAYER
            << QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER)
#endif
            ;
}

QMediaService* DSServicePlugin::create(QString const& key)
{
#ifdef QMEDIA_DIRECTSHOW_CAMERA
    if (key == QLatin1String(Q_MEDIASERVICE_CAMERA))
        return new DSCameraService;
#endif
#ifdef QMEDIA_DIRECTSHOW_PLAYER
    if (key == QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER))
        return new DirectShowPlayerService;
#endif

    qDebug() << "unsupported key:" << key;
    return 0;
}

void DSServicePlugin::release(QMediaService *service)
{
    delete service;
}

QMediaServiceProviderHint::Features DSServicePlugin::supportedFeatures(
        const QByteArray &service) const
{
    if (service == Q_MEDIASERVICE_MEDIAPLAYER)
        return QMediaServiceProviderHint::StreamPlayback | QMediaServiceProviderHint::VideoSurface;
    else
        return QMediaServiceProviderHint::Features();
}

QList<QByteArray> DSServicePlugin::devices(const QByteArray &service) const
{
#ifdef QMEDIA_DIRECTSHOW_CAMERA
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        return m_cameraDevices;
    }
#endif

    return QList<QByteArray>();
}

QString DSServicePlugin::deviceDescription(const QByteArray &service, const QByteArray &device)
{
#ifdef QMEDIA_DIRECTSHOW_CAMERA
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

#ifdef QMEDIA_DIRECTSHOW_CAMERA

void DSServicePlugin::updateDevices() const
{
    m_cameraDevices.clear();
    m_cameraDescriptions.clear();
    BOOL bFound = TRUE;
    CoInitialize(NULL);
    ICreateDevEnum* pDevEnum = NULL;
    IEnumMoniker* pEnum = NULL;
    // Create the System device enumerator
    HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
                 CLSCTX_INPROC_SERVER, IID_ICreateDevEnum,
		 reinterpret_cast<void**>(&pDevEnum));
    if(SUCCEEDED(hr)) {
        // Create the enumerator for the video capture category
	hr = pDevEnum->CreateClassEnumerator(
	     CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (S_OK == hr) {
            pEnum->Reset();
            // go through and find all video capture devices
            IMoniker* pMoniker = NULL;
            while(pEnum->Next(1, &pMoniker, NULL) == S_OK) {
                IPropertyBag *pPropBag;
                hr = pMoniker->BindToStorage(0,0,IID_IPropertyBag,
                     (void**)(&pPropBag));
                if(FAILED(hr)) {
                    pMoniker->Release();
                    continue; // skip this one
                }
                bFound = TRUE;
                // Find the description
                WCHAR str[120];
                VARIANT varName;
                varName.vt = VT_BSTR;
                hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                if(SUCCEEDED(hr)) {
                    wcsncpy(str, varName.bstrVal, sizeof(str)/sizeof(str[0]));
                    QString temp(QString::fromUtf16((unsigned short*)str));
                    m_cameraDevices.append(QString("ds:%1").arg(temp).toLocal8Bit().constData());
                    hr = pPropBag->Read(L"Description", &varName, 0);
                    wcsncpy(str, varName.bstrVal, sizeof(str)/sizeof(str[0]));
                    QString temp2(QString::fromUtf16((unsigned short*)str));
                    m_cameraDescriptions.append(temp2);
                } else {
                    qWarning() << "No friendly name";
                }
                pPropBag->Release();
                pMoniker->Release();
            }
            pEnum->Release();
        }
        pDevEnum->Release();
    }
    CoUninitialize();
    if (!bFound) {
        qWarning() << "No camera devices found";
    }
}
#endif

Q_EXPORT_PLUGIN2(qtmedia_dsengine, DSServicePlugin);

