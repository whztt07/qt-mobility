/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef CNTSYMBIANSORTERDBMS_H
#define CNTSYMBIANSORTERDBMS_H

#include "cntabstractcontactsorter.h"
#include <e32cmn.h>

class CContactDatabase;
class CContactIdArray;
class CntTransformContact;

QTM_USE_NAMESPACE
class CntSymbianSorterDbms : public CntAbstractContactSorter
{
public:
    CntSymbianSorterDbms(CContactDatabase& contactDatabase, CntTransformContact& m_transformContact);
    ~CntSymbianSorterDbms();

    /* from CntAbstractContactFilter */
    QList<QContactLocalId> contacts(
            const QList<QContactSortOrder>& sortOrders,
            QContactManager::Error* error);
    QList<QContactLocalId> sort(
        QList<QContactLocalId> contactIds,
        const QList<QContactSortOrder>& sortOrders,
        QContactManager::Error* error);
    bool sortOrderSupported(const QList<QContactSortOrder>& sortOrders);

private:
    QList<QContactLocalId> contactsL(const QList<QContactSortOrder>& sortOrders) const;
    QList<QContactLocalId> sortL(const QList<QContactLocalId>& contactIds, const QList<QContactSortOrder>& sortOrders) const;
    CContactIdArray* sortL(const CContactIdArray* contactIds, const QList<QContactSortOrder>& sortOrders) const;

private:
    CContactDatabase& m_contactDatabase;
    CntTransformContact& m_transformContact;
};

#endif /* QCONTACTSYMBIANSORTERDBMS_H */
