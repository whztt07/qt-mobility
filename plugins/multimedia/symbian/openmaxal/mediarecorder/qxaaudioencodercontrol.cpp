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

#include "qxaaudioencodercontrol.h"
#include "qxarecordsession.h"
#include "qxacommon.h"

QXAAudioEncoderControl::QXAAudioEncoderControl(QXARecordSession *session, QObject *parent)
:QAudioEncoderControl(parent), m_session(session)
{
}

QXAAudioEncoderControl::~QXAAudioEncoderControl()
{
    QT_TRACE_FUNCTION_ENTRY_EXIT;
}

QStringList QXAAudioEncoderControl::supportedAudioCodecs() const
{
    if (m_session)
        return m_session->supportedAudioCodecs();
    return QStringList();
}

QString QXAAudioEncoderControl::codecDescription(const QString &codecName) const
{
    if (m_session)
        return m_session->codecDescription(codecName);
    return QString();
}

QList<int> QXAAudioEncoderControl::supportedSampleRates(
            const QAudioEncoderSettings &settings,
            bool *continuous) const
{
    if (m_session)
        return m_session->supportedSampleRates(settings, continuous);
    return QList<int>();
}

QAudioEncoderSettings QXAAudioEncoderControl::audioSettings() const
{
    if (m_session)
        return m_session->audioSettings();
    return QAudioEncoderSettings();
}

void QXAAudioEncoderControl::setAudioSettings(const QAudioEncoderSettings &settings)
{
    if (m_session)
        m_session->setAudioSettings(settings);
}

QStringList QXAAudioEncoderControl::supportedEncodingOptions(const QString &codec) const
{
    if (m_session)
        return m_session->supportedEncodingOptions(codec);
    return QStringList();
}

QVariant QXAAudioEncoderControl::encodingOption(const QString &codec, const QString &name) const
{
    if (m_session)
        return m_session->encodingOption(codec, name);
    return QVariant();
}

void QXAAudioEncoderControl::setEncodingOption(
        const QString &codec, const QString &name, const QVariant &value)
{
    if (m_session)
        m_session->setEncodingOption(codec, name, value);
}
