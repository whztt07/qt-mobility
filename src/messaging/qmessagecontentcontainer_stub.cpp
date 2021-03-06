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
#include "qmessagecontentcontainer.h"

QTM_BEGIN_NAMESPACE

QMessageContentContainer::QMessageContentContainer()
{
}

QMessageContentContainer::QMessageContentContainer(const QMessageContentContainer &other)
{
    Q_UNUSED(other)
}

QMessageContentContainer& QMessageContentContainer::operator=(const QMessageContentContainer& other)
{
    Q_UNUSED(other)
    return *this; // stub
}

QMessageContentContainer::~QMessageContentContainer()
{
}

QByteArray QMessageContentContainer::contentType() const
{
    return QByteArray(); // stub
}

QByteArray QMessageContentContainer::contentSubType() const
{
    return QByteArray(); // stub
}

QByteArray QMessageContentContainer::contentCharset() const
{
    return QByteArray(); // stub
}

QByteArray QMessageContentContainer::suggestedFileName() const
{
    return QByteArray(); // stub
}

bool QMessageContentContainer::isContentAvailable() const
{
    return false;
}

int QMessageContentContainer::size() const
{
    return 0;
}

QString QMessageContentContainer::textContent() const
{
    return QString();
}

QByteArray QMessageContentContainer::content() const
{
    return QByteArray(); // stub
}

void QMessageContentContainer::writeTextContent(QTextStream& out) const
{
    Q_UNUSED(out)
}

void QMessageContentContainer::writeContent(QDataStream& out) const
{
    Q_UNUSED(out)
}

QMessageContentContainerIdList QMessageContentContainer::contentIds() const
{
    return QMessageContentContainerIdList(); // stub
}

QMessageContentContainer QMessageContentContainer::find(const QMessageContentContainerId &id) const
{
    Q_UNUSED(id)
    return QMessageContentContainer(); // stub
}

bool QMessageContentContainer::contains(const QMessageContentContainerId &id) const
{
    Q_UNUSED(id)
    return false; // stub
}

QString QMessageContentContainer::headerFieldValue(const QByteArray &name) const
{
    Q_UNUSED(name)
    return QString(); // stub
}

QStringList QMessageContentContainer::headerFieldValues(const QByteArray &name) const
{
    Q_UNUSED(name)
    return QStringList(); // stub
}

QList<QByteArray> QMessageContentContainer::headerFields() const
{
    return QList<QByteArray>(); // stub
}

void QMessageContentContainer::setDerivedMessage(QMessage *derived)
{
    Q_UNUSED(derived)
}

QTM_END_NAMESPACE
