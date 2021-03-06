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

#include "qorganizeritemdetaildefinition.h"
#include "qorganizeritemdetaildefinition_p.h"

#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>
#endif

QTM_BEGIN_NAMESPACE

/*!
  \class QOrganizerItemDetailDefinition
  \brief The QOrganizerItemDetailDefinition class provides the specification for fields in a detail.
  \inmodule QtOrganizer
  \since 1.1

  The QOrganizerItemDetailDefinition class provides the specification for
  a detail that can be included in any particular QOrganizerItem.
  The definition does not include any data, but defines
  the semantics of the representation and use of data
  details that are stored in a QOrganizerItem.
 */

/*!
  \fn QOrganizerItemDetailDefinition::operator!=(const QOrganizerItemDetailDefinition& other) const
  Returns true if this detail definition has different allowable field types or uniqueness to the \a other definition
  \since 1.1
 */

/*! Construct a new, invalid QOrganizerItemDetailDefinition */
QOrganizerItemDetailDefinition::QOrganizerItemDetailDefinition()
    : d(new QOrganizerItemDetailDefinitionData)
{
}

/*! Constructs a new QOrganizerItemDetailDefinition from \a other
  \since 1.1
*/
QOrganizerItemDetailDefinition::QOrganizerItemDetailDefinition(const QOrganizerItemDetailDefinition& other)
    : d(other.d)
{
}

/*! Assigns this QOrganizerItemDetailDefinition to \a other
  \since 1.1
*/
QOrganizerItemDetailDefinition& QOrganizerItemDetailDefinition::operator=(const QOrganizerItemDetailDefinition& other)
{
    d = other.d;
    return *this;
}

/*! Frees the memory used by this QOrganizerItemDetailDefinition */
QOrganizerItemDetailDefinition::~QOrganizerItemDetailDefinition()
{
}

/*! Returns true if the definition has the same type, uniqueness and allowable value datatypes as \a other
  \since 1.1
*/
bool QOrganizerItemDetailDefinition::operator==(const QOrganizerItemDetailDefinition& other) const
{
    if (d->m_name != other.d->m_name)
        return false;
    if (d->m_unique != other.d->m_unique)
        return false;
    if (d->m_fields != other.d->m_fields)
        return false;
    return true;
}

/*! Returns true if the id and fields of this definition are empty
    \since 1.1
*/
bool QOrganizerItemDetailDefinition::isEmpty() const
{
    if (!d->m_name.isEmpty())
        return false;
    if (!d->m_fields.isEmpty())
        return false;
    return true;
}

#ifndef QT_NO_DATASTREAM
/*!
 * Writes \a definition to the stream \a out.
  \since 1.1
 */
QDataStream& operator<<(QDataStream& out, const QOrganizerItemDetailDefinition& definition)
{
    quint8 formatVersion = 1; // Version of QDataStream format for QOrganizerItemDetailDefinition
    return out << formatVersion
               << definition.name()
               << definition.isUnique()
               << definition.fields();
}

/*!
 * Reads a detail definition from stream \a in into \a definition.
  \since 1.1
 */
QDataStream& operator>>(QDataStream& in, QOrganizerItemDetailDefinition& definition)
{
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        QString name;
        bool unique;
        QMap<QString, QOrganizerItemDetailFieldDefinition> fields;
        in >> name >> unique >> fields;
        definition.setName(name);
        definition.setUnique(unique);
        definition.setFields(fields);
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
#endif

#ifndef QT_NO_DEBUG_STREAM
/*!
  Outputs \a definition to the debug stream \a dbg
 */
QDebug operator<<(QDebug dbg, const QOrganizerItemDetailDefinition& definition)
{
    dbg.nospace() << "QOrganizerItemDetailDefinition(";
    dbg.nospace() << "name=";
    dbg.nospace() << definition.name();
    dbg.nospace() << ",";
    dbg.nospace() << "isUnique=";
    dbg.nospace() << definition.isUnique();
    dbg.nospace() << ",";
    dbg.nospace() << "isEmpty=";
    dbg.nospace() << definition.isEmpty();
    dbg.nospace() << ",";
    dbg.nospace() << "fields=";
    dbg.nospace() << definition.fields();
    dbg.nospace() << ")";
    return dbg.maybeSpace();
}
#endif

/*! Sets the unique identifier of this detail type to \a definitionName.
  \since 1.1
*/
void QOrganizerItemDetailDefinition::setName(const QString& definitionName)
{
    d->m_name = definitionName;
}

/*!
  Sets whether an organizer item can have more than one detail of this type.
  If \a unique is true, only one detail of this type can be added.
  Otherwise, any number can be added.
  \since 1.1
 */
void QOrganizerItemDetailDefinition::setUnique(bool unique)
{
    d->m_unique = unique;
}

/*! Returns the identifier of this detail definition
  \since 1.1
*/
QString QOrganizerItemDetailDefinition::name() const
{
    return d->m_name;
}

/*! Returns the per-organizer item uniqueness of this definition
  \since 1.1
*/
bool QOrganizerItemDetailDefinition::isUnique() const
{
    return d->m_unique;
}

/*! Sets the fields which constitute the data of details of this this definition to \a fields
  \since 1.1
*/
void QOrganizerItemDetailDefinition::setFields(const QMap<QString, QOrganizerItemDetailFieldDefinition>& fields)
{
    d->m_fields = fields;
}

/*! Returns the map of keys to fields which are present in details of this definition
  \since 1.1
*/
QMap<QString, QOrganizerItemDetailFieldDefinition> QOrganizerItemDetailDefinition::fields() const
{
    return d->m_fields;
}

/*! Inserts the field \a field into the map of fields which constitute the data of details of this definition for the given field key \a key.
    If another field for that key already exists in the definition, it will be overwritten.
  \since 1.1
*/
void QOrganizerItemDetailDefinition::insertField(const QString& key, const QOrganizerItemDetailFieldDefinition& field)
{
    d->m_fields.insert(key, field);
}

/*! Removes the field associated with the given field key \a key from the map of fields which constitute the data of details of this definition.
  \since 1.1
*/
void QOrganizerItemDetailDefinition::removeField(const QString& key)
{
    d->m_fields.remove(key);
}

QTM_END_NAMESPACE
