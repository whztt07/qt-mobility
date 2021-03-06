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

#ifndef QGEOTILEDMAPPINGMANAGERENGINE_TEST_H
#define QGEOTILEDMAPPINGMANAGERENGINE_TEST_H

#include <qgeoserviceprovider.h>
#include <qgeotiledmappingmanagerengine.h>
#include <qgeotiledmapreply.h>
#include <qgeomapdata.h>
#include <QObject>
#include <QTimer>
#include <QFile>

QTM_USE_NAMESPACE

class QGeoMapReplyTest: public QGeoTiledMapReply
{
    Q_OBJECT

public:
    QGeoMapReplyTest(const QGeoTiledMapRequest &request, QObject *parent = 0) :
        QGeoTiledMapReply(request, parent)
    {
        m_finishedTimer.setSingleShot(true);
        m_finishedTimer.setInterval(1);

        if (request == QGeoTiledMapRequest()) {
            connect(&m_finishedTimer, SIGNAL(timeout()), this, SLOT(replyerror()));
            m_finishedTimer.start();
            return;
        }

        Q_INIT_RESOURCE( geoservicestestmaptiles);
        m_tileSize = QSize(256, 256);
        setCached(true);
        connect(&m_finishedTimer, SIGNAL(timeout()), this, SLOT(replyfinished()));
        m_finishedTimer.start();
    }

    ~QGeoMapReplyTest()
    {
        m_finishedTimer.stop();
    }

    void abort()
    {
        m_finishedTimer.stop();
        QGeoTiledMapReply::abort();
    }

private slots:
    void replyfinished()
    {
        QFile tile(":/tiles/png8.png");
        tile.open(QFile::ReadOnly);
        setMapImageData(tile.readAll());
        tile.close();
        setMapImageFormat("PNG");
        setFinished(true);
    }

    void replyerror()
    {
        setError(QGeoTiledMapReply::UnknownError, "Error");
    }
private:
    QSize m_tileSize;
    QTimer m_finishedTimer;
};

class QGeoTiledMappingManagerEngineTest: public QGeoTiledMappingManagerEngine
{
    Q_OBJECT

public:
    QGeoTiledMappingManagerEngineTest(const QMap<QString, QVariant> &parameters,
        QGeoServiceProvider::Error *error, QString *errorString) :
        QGeoTiledMappingManagerEngine(parameters)
    {
        Q_UNUSED(error)
        Q_UNUSED(errorString)
        setMinimumZoomLevel(0.0);
        setMaximumZoomLevel(18.0);
        setTileSize(QSize(256, 256));
        QList<QGraphicsGeoMap::ConnectivityMode> modes;
        modes << QGraphicsGeoMap::OfflineMode;
        modes << QGraphicsGeoMap::OnlineMode;
        modes << QGraphicsGeoMap::HybridMode;
        setSupportedConnectivityModes(modes);

        QList<QGraphicsGeoMap::MapType> types;
        types << QGraphicsGeoMap::StreetMap;
        types << QGraphicsGeoMap::SatelliteMapDay;
        types << QGraphicsGeoMap::TerrainMap;
        setSupportedMapTypes(types);
    }

    QGeoMapData* createMapData()
    {
        QGeoMapData *data = QGeoTiledMappingManagerEngine::createMapData();
        data->setConnectivityMode(QGraphicsGeoMap::OfflineMode);
        data->setMapType(QGraphicsGeoMap::StreetMap);
        return data;
    }
    QGeoTiledMapReply* getTileImage(const QGeoTiledMapRequest &request)
    {
        return new QGeoMapReplyTest(request);
    }

};

#endif
