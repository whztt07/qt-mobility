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

#include "qsystemgeneralinfo.h"
#include "qsysteminfocommon_p.h"

#include <QMetaType>

QTM_BEGIN_NAMESPACE

#ifndef Q_OS_SYMBIAN
Q_GLOBAL_STATIC(QSystemInfoPrivate, infoPrivateSingleton)
#endif

#ifdef QT_SIMULATOR
QSystemInfoPrivate *getSystemInfoPrivate() { return infoPrivateSingleton(); }
#endif // QT_SIMULATOR

/*!
    \class QSystemInfo
    \ingroup systeminfo
    \inmodule QtSystemInfo
    \since 1.0
    \brief The QSystemInfo class provides access to various general information from the system.

    \reentrant

    \note All functions in this class are reentrant.

    \warning On Symbian this class does not support QObject::moveToThread().
*/

/*!
    \enum QSystemInfo::Version
    This enum describes the version component.

    \value Os                    Operating system version / platform ID.
    \value QtCore                Qt library version.
    \value Firmware              Version of (flashable) system as a whole.
    \value QtMobility            QtMobility library version. Since 1.1
*/

/*!
    \enum QSystemInfo::Feature
    This enum describes the features of the device or computer.

    \value BluetoothFeature       Bluetooth feature available.
    \value CameraFeature          Camera feature available.
    \value FmradioFeature         FM Radio feature available.
    \value IrFeature              Infrared feature available.
    \value LedFeature             LED's feature available.
    \value MemcardFeature         Memory card feature available.
    \value UsbFeature             Universal System Bus (USB) feature available.
    \value VibFeature             Vibration feature available.
    \value WlanFeature            Wireless Local Area Network (WLAN) feature available.
    \value SimFeature             Subscriber Identity Module (SIM) available.
    \value LocationFeature        Global Positioning System (GPS) and/or other location feature available.
    \value VideoOutFeature        Video out feature available.
    \value HapticsFeature         Haptics feature available.
    \value FmTransmitterFeature   FM Radio transmitter available. Since 1.2
*/

/*!
    \fn void QSystemInfo::currentLanguageChanged(const QString &lang)

    This signal is emitted whenever the current language changes, specified by \a lang,
    which is in 2 letter, ISO 639-1 specification form.

    \since 1.0
*/

/*!
    Constructs a QSystemInfo object with the given \a parent.
*/
QSystemInfo::QSystemInfo(QObject *parent)
    : QObject(parent)
{
#ifdef Q_OS_SYMBIAN
    d = new QSystemInfoPrivate();
#else
    d = infoPrivateSingleton();
#endif
    qRegisterMetaType<QSystemInfo::Version>("QSystemInfo::Version");
    qRegisterMetaType<QSystemInfo::Feature>("QSystemInfo::Feature");
}

/*!
    Destroys the QSystemInfo object
*/
QSystemInfo::~QSystemInfo()
{
#ifdef Q_OS_SYMBIAN
    delete d;
#endif
}

/*!
    \internal
*/
void QSystemInfo::connectNotify(const char *signal)
{
    if (QLatin1String(signal) == SIGNAL(currentLanguageChanged(QString))) {
        connect(d, SIGNAL(currentLanguageChanged(QString)),
                this, SIGNAL(currentLanguageChanged(QString)),
                Qt::UniqueConnection);
    }
}

/*!
    \internal
*/
void QSystemInfo::disconnectNotify(const char *signal)
{
    // disconnect only when there's no connections
    if (receivers(signal) > 0)
        return;

    if (QLatin1String(signal) == SIGNAL(currentLanguageChanged(QString))) {
        disconnect(d, SIGNAL(currentLanguageChanged(QString)),
                   this, SIGNAL(currentLanguageChanged(QString)));
    }
}

/*!
    \property QSystemInfo::currentLanguage
    \brief The current Language

    Returns the current language in 2 letter ISO 639-1 format.
   \since 1.0
 */
QString QSystemInfo::currentLanguage()
{
    return d->currentLanguage();
}
/*!
    \property QSystemInfo::availableLanguages
    \brief List of available languages.

    Returns a QStringList of available Qt language translations in 2 letter ISO 639-1 format.
    If the Qt translations cannot be found, returns the current system language.
    \since 1.0
*/
QStringList QSystemInfo::availableLanguages()
{
    return d->availableLanguages();
}

/*!
    Returns the version of QSystemInfo::Version \a type, with optional platform dependent
    \a parameter as a string.

    In case of error or not available, an empty string is returned.
    \since 1.0
*/
QString QSystemInfo::version(QSystemInfo::Version type, const QString &parameter)
{
    switch(type) {
    case QSystemInfo::QtMobility:
        return QLatin1String(QTM_VERSION_STR);
    case QSystemInfo::QtCore:
        return QString(qVersion());
    default:
        return d->version(type, parameter);
    }
}

/*!
    \property  QSystemInfo::currentCountryCode
    \brief The current locale country code.

    Returns the 2 letter ISO 3166-1 for the current country code.
    \since 1.0
*/
QString QSystemInfo::currentCountryCode()
{
    return d->currentCountryCode();
}

/*!
    Returns true if the QSystemInfo::Feature \a feature is supported, otherwise false.
    \since 1.0
*/
bool QSystemInfo::hasFeatureSupported(QSystemInfo::Feature feature)
{
    return d->hasFeatureSupported(feature);
}

#include "moc_qsystemgeneralinfo.cpp"

QTM_END_NAMESPACE
