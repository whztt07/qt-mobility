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

#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <qgeoroutingmanager.h>
#include <qgeosearchmanager.h>

#include <qgeoroutereply.h>
#include <qgeoroutereply.h>
#include <qgeosearchreply.h>
#include <qgeomaprouteobject.h>

#include "marker.h"

using namespace QtMobility;

class MapsWidget;

class Navigator : public QObject
{
    Q_OBJECT
public:
    Navigator(QGeoRoutingManager *routingManager, QGeoSearchManager *searchManager,
              MapsWidget *mapsWidget, const QString &address,
              const QGeoRouteRequest &requestTemplate);
    ~Navigator();

    void start();
    QGeoRoute route() const;

signals:
    void finished();
    void searchError(QGeoSearchReply::Error error, QString errorString);
    void routingError(QGeoRouteReply::Error error, QString errorString);

private slots:
    void on_addressSearchFinished();
    void on_routingFinished();

private:
    QString address;
    QGeoRouteRequest request;

    QGeoRoutingManager *routingManager;
    QGeoSearchManager *searchManager;
    MapsWidget *mapsWidget;

    QGeoSearchReply *addressReply;
    QGeoRouteReply *routeReply;

    QGeoMapRouteObject *routeObject;
    Marker *endMarker;
    Marker *startMarker;

    QGeoRoute firstRoute;
};

#endif // NAVIGATOR_H
