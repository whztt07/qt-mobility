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

#include "qorganizercollectionchangeset.h"
#include "qorganizercollectionchangeset_p.h"
#include "qorganizermanagerengine.h"

QTM_BEGIN_NAMESPACE

/*!
   \class QOrganizerCollectionChangeSet

   \brief The QOrganizerCollectionChangeSet class provides a simple API to
   simplify the emission of state-change signals from QOrganizerManagerEngine
   implementations.
   \since 1.1

  \inmodule QtOrganizer



   This class can be utilized by backend implementations to ensure
   correct emission of the \l QOrganizerManagerEngine::dataChanged(),
   \l QOrganizerManagerEngine::itemsAdded(),
   \l QOrganizerManagerEngine::itemsChanged() and
   \l QOrganizerManagerEngine::itemsRemoved().

   \sa QOrganizerManagerEngine
 */

/*!
   Constructs a new change set
 */
QOrganizerCollectionChangeSet::QOrganizerCollectionChangeSet()
    : d(new QOrganizerCollectionChangeSetData)
{
}

/*!
   Constructs a copy of the \a other change set
   \since 1.1
 */
QOrganizerCollectionChangeSet::QOrganizerCollectionChangeSet(const QOrganizerCollectionChangeSet& other)
    : d(other.d)
{
}

/*!
   Frees the memory used by this change set
 */
QOrganizerCollectionChangeSet::~QOrganizerCollectionChangeSet()
{
}

/*!
   Assigns this change set to be equal to \a other
   \since 1.1
 */
QOrganizerCollectionChangeSet& QOrganizerCollectionChangeSet::operator=(const QOrganizerCollectionChangeSet& other)
{
    d = other.d;
    return *this;
}

/*!
   Sets the data changed flag to \a dataChanged.  If this is set to true prior to calling \l emitSignals(),
   only the \l QOrganizerManagerEngine::dataChanged() signal will be emitted; otherwise, the appropriate
   finer-grained signals will be emitted.
   \since 1.1
 */
void QOrganizerCollectionChangeSet::setDataChanged(bool dataChanged)
{
    d->m_dataChanged = dataChanged;
}

/*!
   Returns the value of the data changed flag
   \since 1.1
 */
bool QOrganizerCollectionChangeSet::dataChanged()
{
    return d->m_dataChanged;
}

/*!
   Returns the set of ids of collections which have been added to
   the database.
   \since 1.1
 */
QSet<QOrganizerCollectionId> QOrganizerCollectionChangeSet::addedCollections() const
{
    return d->m_addedCollections;
}

/*!
  Inserts the given collection id \a addedOrganizerCollectionId into the set of ids of collections
  which have been added to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertAddedCollection(const QOrganizerCollectionId& addedOrganizerCollectionId)
{
    d->m_addedCollections.insert(addedOrganizerCollectionId);
}

/*!
  Inserts each of the given collection ids \a addedOrganizerCollectionIds into
  the set of ids of collections which have been added to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertAddedCollections(const QList<QOrganizerCollectionId>& addedOrganizerCollectionIds)
{
    foreach (const QOrganizerCollectionId& id, addedOrganizerCollectionIds)
        d->m_addedCollections.insert(id);
}

/*!
  Clears the set of ids of collections which have been added to the database
  \since 1.1
 */
void QOrganizerCollectionChangeSet::clearAddedCollections()
{
    d->m_addedCollections.clear();
}

/*!
   Returns the set of ids of collections which have been changed in
   the database.
   \since 1.1
 */
QSet<QOrganizerCollectionId> QOrganizerCollectionChangeSet::changedCollections() const
{
    return d->m_changedCollections;
}

/*!
  Inserts the given collection id \a changedOrganizerCollectionId into the set of ids of collections
  which have been changed to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertChangedCollection(const QOrganizerCollectionId& changedOrganizerCollectionId)
{
    d->m_changedCollections.insert(changedOrganizerCollectionId);
}

/*!
  Inserts each of the given collection ids \a changedOrganizerCollectionIds into the set of ids of collections
  which have been changed to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertChangedCollections(const QList<QOrganizerCollectionId>& changedOrganizerCollectionIds)
{
    foreach (const QOrganizerCollectionId& id, changedOrganizerCollectionIds)
        d->m_changedCollections.insert(id);
}

/*!
  Clears the set of ids of collections which have been changed to the database
  \since 1.1
 */
void QOrganizerCollectionChangeSet::clearChangedCollections()
{
    d->m_changedCollections.clear();
}

/*!
   Returns the set of ids of collections which have been removed from
   the database.
  \since 1.1
 */
QSet<QOrganizerCollectionId> QOrganizerCollectionChangeSet::removedCollections() const
{
    return d->m_removedCollections;
}

/*!
  Inserts the given collection id \a removedOrganizerCollectionId into the set of ids of collections
  which have been removed to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertRemovedCollection(const QOrganizerCollectionId& removedOrganizerCollectionId)
{
    d->m_removedCollections.insert(removedOrganizerCollectionId);
}

/*!
  Inserts each of the given collection ids \a removedOrganizerCollectionIds into the set of ids of collections
  which have been removed to the database.
  \since 1.1
 */
void QOrganizerCollectionChangeSet::insertRemovedCollections(const QList<QOrganizerCollectionId>& removedOrganizerCollectionIds)
{
    foreach (const QOrganizerCollectionId& id, removedOrganizerCollectionIds)
        d->m_removedCollections.insert(id);
}

/*!
  Clears the set of ids of collections which have been removed to the database
  \since 1.1
 */
void QOrganizerCollectionChangeSet::clearRemovedCollections()
{
    d->m_removedCollections.clear();
}


/*!
   Clears all flags and sets of ids in this change set
  \since 1.1
 */
void QOrganizerCollectionChangeSet::clearAll()
{
    d->m_dataChanged = false;
    d->m_addedCollections.clear();
    d->m_changedCollections.clear();
    d->m_removedCollections.clear();
}

/*!
   Emits the appropriate signals from the given \a engine given the state of the change set
  \since 1.1
 */
void QOrganizerCollectionChangeSet::emitSignals(QOrganizerManagerEngine *engine)
{
    if (!engine)
        return;

    if (d->m_dataChanged) {
        emit engine->dataChanged();
    } else {
        if (!d->m_addedCollections.isEmpty())
            emit engine->collectionsAdded(d->m_addedCollections.toList());
        if (!d->m_changedCollections.isEmpty())
            emit engine->collectionsChanged(d->m_changedCollections.toList());
        if (!d->m_removedCollections.isEmpty())
            emit engine->collectionsRemoved(d->m_removedCollections.toList());
    }
}

QTM_END_NAMESPACE
