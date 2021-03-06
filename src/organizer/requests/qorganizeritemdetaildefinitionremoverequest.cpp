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

#include "qorganizeritemdetaildefinitionremoverequest.h"
#include "qorganizeritemrequests_p.h"

QTM_BEGIN_NAMESPACE

/*!
  \class QOrganizerItemDetailDefinitionRemoveRequest
  \brief The QOrganizerItemDetailDefinitionRemoveRequest class allows a client to
  asynchronously request that certain detail definitions be removed from
  an organizer item manager.
  \inmodule QtOrganizer
  \since 1.1

  For a QOrganizerItemDetailDefinitionRemoveRequest, the resultsUpdated() signal will be emitted when
  the individual item errors (which may be retrieved by calling errorMap()) are updated, or if the overall
  operation error (which may be retrieved by calling error()) is updated.

  \ingroup organizer-requests
 */

/*! Constructs a new detail definition remove request whose parent is the specified \a parent
  \since 1.1
*/
QOrganizerItemDetailDefinitionRemoveRequest::QOrganizerItemDetailDefinitionRemoveRequest(QObject* parent)
    : QOrganizerAbstractRequest(new QOrganizerItemDetailDefinitionRemoveRequestPrivate, parent)
{
}

/*! Frees memory in use by this request
    \since 1.2
*/
QOrganizerItemDetailDefinitionRemoveRequest::~QOrganizerItemDetailDefinitionRemoveRequest()
{
    QOrganizerAbstractRequestPrivate::notifyEngine(this);
}

/*!
  Sets the name of the detail definition to remove from the manager to \a definitionName.
  Managers may store different definitions which are valid for different organizer item types, and so attempting to remove definitions with certain names may fail if no such
  definitions exist for organizer items of the given organizer item type, specified via setItemType().
  Equivalent to calling:
  \code
      setDefinitionNames(QStringList(definitionName));
  \endcode

  \sa setItemType()
  \since 1.1
 */
void QOrganizerItemDetailDefinitionRemoveRequest::setDefinitionName(const QString& definitionName)
{
    Q_D(QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_names.clear();
    d->m_names.append(definitionName);
}

/*!
  Sets the names of the detail definitions to remove from the manager to \a names.
  Managers may store different definitions which are valid for different organizer item types, and so attempting to remove definitions with certain names may fail if no such
  definitions exist for organizer items of the given organizer item type, specified via setItemType().
  \sa setItemType()
  \since 1.1
 */
void QOrganizerItemDetailDefinitionRemoveRequest::setDefinitionNames(const QStringList& names)
{
    Q_D(QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_names = names;
}

/*! Returns the list of names of the detail definitions that will be removed from the manager
    \since 1.1
*/
QStringList QOrganizerItemDetailDefinitionRemoveRequest::definitionNames() const
{
    Q_D(const QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_names;
}

/*!
  Sets the type of organizer item for which detail definitions should be removed to \a organizeritemType
  \since 1.1
 */
void QOrganizerItemDetailDefinitionRemoveRequest::setItemType(const QString& organizeritemType)
{
    Q_D(QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_organizeritemType = organizeritemType;
}

/*! Returns the type of organizer item for which detail definitions will be removed
    \since 1.1
*/
QString QOrganizerItemDetailDefinitionRemoveRequest::itemType() const
{
    Q_D(const QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_organizeritemType;
}

/*! Returns the map of input name list indices to errors which occurred
  \since 1.1
*/
QMap<int, QOrganizerManager::Error> QOrganizerItemDetailDefinitionRemoveRequest::errorMap() const
{
    Q_D(const QOrganizerItemDetailDefinitionRemoveRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_errors;
}

#include "moc_qorganizeritemdetaildefinitionremoverequest.cpp"

QTM_END_NAMESPACE
