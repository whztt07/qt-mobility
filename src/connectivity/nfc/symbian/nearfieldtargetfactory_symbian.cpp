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

#include "nearfieldtargetfactory_symbian.h"
#include <nfcserver.h>
#include <nfctag.h>
#include <nfctype1connection.h>
#include <nfctype2connection.h>
#include <nfctype3connection.h>
#include <iso14443connection.h>
#include <mifareclassicconnection.h>
#include "qnearfieldtagtype1_symbian_p.h"
#include "qnearfieldtagtype2_symbian_p.h"
#include "qnearfieldtagtype3_symbian_p.h"
#include "qnearfieldtagtype4_symbian_p.h"
#include "qnearfieldtagmifare_symbian_p.h"
#include "qnearfieldllcpdevice_symbian_p.h"
/*
    \class TNearFieldTargetFactory
    \brief The TNearFieldTargetFactory class creates detected target instance according
           to the input tag information

    \ingroup connectivity-nfc
    \inmodule QtConnectivity
    \since 1.2
*/

/*
    Create tag type instance according to the tag information in \a aNfcTag and assign
    the \a aParent as target's parent.
*/
template <typename CTAGCONNECTION, typename QTAGTYPE>
QNearFieldTarget * TNearFieldTargetFactory::CreateTagTypeL(MNfcTag * aNfcTag, RNfcServer& aNfcServer, QObject * aParent)
{
    BEGIN
    // ownership of aNfcTag transferred.
    CTAGCONNECTION * connection = CTAGCONNECTION::NewLC(aNfcServer);
    CNearFieldTag * tagType = CNearFieldTag::NewLC(aNfcTag, aNfcServer);
    tagType->SetConnection(connection);
    QTAGTYPE * tag= new(ELeave)QTAGTYPE(WrapNdefAccessL(aNfcTag, aNfcServer, tagType), aParent);
    // walk around, symbian discovery API can't know if tag has Ndef Connection mode when detected
    tag->setAccessMethods(ConnectionMode2AccessMethods(aNfcTag)|QNearFieldTarget::NdefAccess);
    CleanupStack::Pop(tagType);
    CleanupStack::Pop(connection);
    END
    return tag;
}

/*
    Create target instance according to the tag information in \a aNfcTag and assign
    the \a aParent as target's parent.
*/

QNearFieldTarget * TNearFieldTargetFactory::CreateTargetL(MNfcTag * aNfcTag, RNfcServer& aNfcServer, QObject * aParent)
    {
    BEGIN
    QNearFieldTarget * target = 0;
    if (!aNfcTag)
        {
        LOG("llcp device created");
        target = new (ELeave)QNearFieldLlcpDeviceSymbian(aNfcServer, aParent);
        }
    else if(aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfcType1))
        {
        LOG("tag type 1 created");
        target = CreateTagTypeL<CNfcType1Connection, QNearFieldTagType1Symbian>(aNfcTag, aNfcServer, aParent);
        }
    else if (aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfcType2))
        {
        LOG("tag type 2 created");
        target = CreateTagTypeL<CNfcType2Connection, QNearFieldTagType2Symbian>(aNfcTag, aNfcServer, aParent);
        }
    else if (aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfcType3))
        {
        LOG("tag type 3 created");
        target = CreateTagTypeL<CNfcType3Connection, QNearFieldTagType3Symbian>(aNfcTag, aNfcServer, aParent);
        }
    else if (aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfc14443P4))
        {
        LOG("tag type 4 created");
        target = CreateTagTypeL<CIso14443Connection, QNearFieldTagType4Symbian>(aNfcTag, aNfcServer, aParent);
        }
    else if (aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfcMifareStd))
        {
        LOG("tag type mifare created");
        target = CreateTagTypeL<CMifareClassicConnection, QNearFieldTagMifareSymbian>(aNfcTag, aNfcServer, aParent);
        }
    END
    return target;
    }

CNearFieldNdefTarget * TNearFieldTargetFactory::WrapNdefAccessL(MNfcTag * aNfcTag, RNfcServer& aNfcServer, CNearFieldTag * aTarget)
    {
    BEGIN
    // walk around, symbian discovery API can't know if tag has Ndef Connection mode when detected

    LOG("Wrap NDEF Access to the tag");

    CNearFieldNdefTarget * ndefTarget = CNearFieldNdefTarget::NewLC(aNfcTag, aNfcServer);
    ndefTarget->SetRealTarget(aTarget);
    CleanupStack::Pop(ndefTarget);
    END
    return ndefTarget;
    }

QNearFieldTarget::AccessMethods TNearFieldTargetFactory::ConnectionMode2AccessMethods(MNfcTag * aNfcTag)
    {
    BEGIN
    QNearFieldTarget::AccessMethods accessMethod;
    if (aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENdefConnection))
        {
        LOG("the tag has NDefConnection");
        accessMethod |= QNearFieldTarget::NdefAccess;
        }
    if (!aNfcTag->HasConnectionMode(TNfcConnectionInfo::ENfcUnknownConnectionMode))
        {
        LOG("the tag has tag specified access");
        accessMethod |= QNearFieldTarget::TagTypeSpecificAccess;
        }
    END
    return accessMethod;
    }
