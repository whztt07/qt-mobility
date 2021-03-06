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

#ifndef QDECLARATIVEGEOSEARCHMODEL_H
#define QDECLARATIVEGEOSEARCHMODEL_H

#include "qdeclarativegeoserviceprovider_p.h"

#include <qgeosearchreply.h>

#include <QtDeclarative/qdeclarative.h>
#include <QDeclarativeParserStatus>
#include <QAbstractListModel>

QTM_BEGIN_NAMESPACE

class QGeoServiceProvider;
class QGeoSearchManager;
class QDeclarativeGeoPlace;

class QDeclarativeGeoSearchModel : public QAbstractListModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_ENUMS(Status)

    Q_PROPERTY(QDeclarativeGeoServiceProvider *plugin READ plugin WRITE setPlugin NOTIFY pluginChanged)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_INTERFACES(QDeclarativeParserStatus)

public:
    enum Status {
        Null,
        Ready,
        Loading,
        Error
    };

    enum Roles {
        PlaceRole = Qt::UserRole + 499,
        LandmarkRole = Qt::UserRole + 500
    };

    explicit QDeclarativeGeoSearchModel(QObject* parent = 0);
    virtual ~QDeclarativeGeoSearchModel();

    // From QDeclarativeParserStatus
    virtual void classBegin();
    virtual void componentComplete();

    // From QAbstractListModel
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setPlugin(QDeclarativeGeoServiceProvider *plugin);
    QDeclarativeGeoServiceProvider* plugin() const;

    Status status() const;

    QString error() const;

Q_SIGNALS:
    void pluginChanged(QDeclarativeGeoServiceProvider *plugin);
    void statusChanged(QDeclarativeGeoSearchModel::Status status);
    void errorChanged(const QString &error);
    void placesChanged();

private Q_SLOTS:
    void searchFinished(QGeoSearchReply *reply);
    void searchError(QGeoSearchReply *reply,
                     QGeoSearchReply::Error error,
                     const QString &errorString);

protected:
    QGeoSearchManager* searchManager();

    QList<QGeoPlace> places() const;

    void setStatus(Status status);

    void setError(const QString &error);

private:
    void setPlaces(const QList<QGeoPlace> &places);

    QDeclarativeGeoServiceProvider* plugin_;
    QGeoServiceProvider* serviceProvider_;
    QGeoSearchManager* searchManager_;

    Status status_;
    QString error_;
    QList<QGeoPlace> places_;
};


QTM_END_NAMESPACE

#endif
