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
#ifndef QFEEDBACK_SYMBIAN_H
#define QFEEDBACK_SYMBIA_H

#include <qmobilityglobal.h>

#include <qfeedbackplugininterfaces.h>

#include "../../../src/multimedia/effects/qsoundeffect_p.h"

QT_BEGIN_HEADER
QTM_USE_NAMESPACE

class QFeedbackMediaObject;

class QFeedbackMMK : public QObject, public QFeedbackFileInterface
{
    Q_OBJECT
    Q_INTERFACES(QTM_NAMESPACE::QFeedbackFileInterface)
public:
    QFeedbackMMK();
    virtual ~QFeedbackMMK();

    virtual void setLoaded(QFeedbackFileEffect*, bool);
    virtual void setEffectState(QFeedbackFileEffect *, QFeedbackEffect::State);
    virtual QFeedbackEffect::State effectState(const QFeedbackFileEffect *);
    virtual int effectDuration(const QFeedbackFileEffect*);
    virtual QStringList supportedMimeTypes();
private Q_SLOTS:
    void soundEffectStatusChanged();
    void soundEffectPlayingChanged();

private:
    struct FeedbackInfo {
        FeedbackInfo() : soundEffect(0), loaded(false), playing(false) {}
        QSoundEffect* soundEffect;
        bool loaded;
        bool playing;
    };

    QHash<const QFeedbackFileEffect*, FeedbackInfo> mEffects;
    QHash<const QSoundEffect*, QFeedbackFileEffect*> mEffectMap;
};

QT_END_HEADER

#endif
