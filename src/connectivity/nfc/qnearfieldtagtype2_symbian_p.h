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

#ifndef QNEARFIELDTAGTYPE2SYMBIAN_H
#define QNEARFIELDTAGTYPE2SYMBIAN_H

#include <qnearfieldtagtype2.h>
#include "symbian/nearfieldndeftarget_symbian.h"
#include "symbian/nearfieldtag_symbian.h"
#include "symbian/nearfieldtagimpl_symbian.h"

QT_BEGIN_HEADER

QTM_BEGIN_NAMESPACE

class QNearFieldTagType2Symbian : public QNearFieldTagType2, private QNearFieldTagImpl<QNearFieldTagType2Symbian>
{
    Q_OBJECT
public:
    explicit QNearFieldTagType2Symbian(CNearFieldNdefTarget * tag, QObject *parent = 0);

    ~QNearFieldTagType2Symbian();

    QByteArray uid() const;

    RequestId readBlock(quint8 blockAddress);
    RequestId writeBlock(quint8 blockAddress, const QByteArray &data);
    RequestId selectSector(quint8 sector);

    RequestId sendCommand(const QByteArray &command);
    RequestId sendCommands(const QList<QByteArray> &commands);
    bool isProcessingCommand() const { return _isProcessingRequest(); }

    bool hasNdefMessage();
    RequestId readNdefMessages();
    RequestId writeNdefMessages(const QList<QNdefMessage> &messages);

    void setAccessMethods(const QNearFieldTarget::AccessMethods& accessMethods)
    {
        _setAccessMethods(accessMethods);
    }

    QNearFieldTarget::AccessMethods accessMethods() const
    {
        return _accessMethods();
    }

    void handleTagOperationResponse(const RequestId &id, const QByteArray &command, const QByteArray &response, bool emitRequestCompleted);
    QVariant decodeResponse(const QByteArray &command, const QByteArray &response);

    bool waitForRequestCompleted(const RequestId &id, int msecs = 5000);
    friend class QNearFieldTagImpl<QNearFieldTagType2Symbian>;

private:
    quint8 mCurrentSector;
};

QTM_END_NAMESPACE
QT_END_HEADER

#endif //QNEARFIELDTAGTYPE2SYMBIAN_H
