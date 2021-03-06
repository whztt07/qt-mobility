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

#include "qorganizeritemdetaildefinitionfetchrequest.h"
#include "qorganizeritemrequests_p.h"

QTM_BEGIN_NAMESPACE

/*!
  \class QOrganizerItemDetailDefinitionFetchRequest
  \brief The QOrganizerItemDetailDefinitionFetchRequest class allows a client to
    asynchronously request detail definitions from an organizer item store manager.
  \inmodule QtOrganizer

  For a QOrganizerItemDetailDefinitionFetchRequest, the resultsAvailable() signal will be emitted when
  either the individual item errors (which may be retrieved by calling errorMap()), or the resultant
  detail definitions (which may be retrieved by calling definitions()), are updated, as well as if
  the overall operation error (which may be retrieved by calling error()) is updated.
  \since 1.1

  \ingroup organizer-requests
 */

/*! Constructs a new detail definition fetch request whose parent is the specified \a parent
  \since 1.1
*/
QOrganizerItemDetailDefinitionFetchRequest::QOrganizerItemDetailDefinitionFetchRequest(QObject* parent)
    : QOrganizerAbstractRequest(new QOrganizerItemDetailDefinitionFetchRequestPrivate, parent)
{
}

/*! Frees memory in use by this request
  \since 1.2
*/
QOrganizerItemDetailDefinitionFetchRequest::~QOrganizerItemDetailDefinitionFetchRequest()
{
    QOrganizerAbstractRequestPrivate::notifyEngine(this);
}

/*! Sets the name of the detail definition to retrieve to \a definitionName.
    Equivalent to calling
    \code
        setDefinitionNames(QList<QOrganizerItemDetailDefinition>() << definitionName);
    \endcode
  \since 1.1
 */
void QOrganizerItemDetailDefinitionFetchRequest::setDefinitionName(const QString& definitionName)
{
    Q_D(QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_names.clear();
    d->m_names.append(definitionName);
}

/*! Sets the names of the detail definitions to retrieve to \a names
  \since 1.1
*/
void QOrganizerItemDetailDefinitionFetchRequest::setDefinitionNames(const QStringList& names)
{
    Q_D(QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_names = names;
}

/*! Returns the list of names of the detail definitions that will be retrieved
  \since 1.1
*/
QStringList QOrganizerItemDetailDefinitionFetchRequest::definitionNames() const
{
    Q_D(const QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_names;
}

/*! Sets the type of organizer item for which detail definitions should be retrieved to \a organizeritemType
  \since 1.1
*/
void QOrganizerItemDetailDefinitionFetchRequest::setItemType(const QString& organizeritemType)
{
    Q_D(QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_organizeritemType = organizeritemType;
}

/*! Returns the type of organizer item for which detail definitions will be retrieved
    \since 1.1
*/
QString QOrganizerItemDetailDefinitionFetchRequest::itemType() const
{
    Q_D(const QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_organizeritemType;
}

/*!
  Returns the map of detail definition names to detail definitions that was the result of the request
  \since 1.1
 */
QMap<QString, QOrganizerItemDetailDefinition> QOrganizerItemDetailDefinitionFetchRequest::definitions() const
{
    Q_D(const QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_definitions;
}

/*! Returns the map of input name list indices to errors which occurred
    \since 1.1
*/
QMap<int, QOrganizerManager::Error> QOrganizerItemDetailDefinitionFetchRequest::errorMap() const
{
    Q_D(const QOrganizerItemDetailDefinitionFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_errors;
}

#include "moc_qorganizeritemdetaildefinitionfetchrequest.cpp"

QTM_END_NAMESPACE
