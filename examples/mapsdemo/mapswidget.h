/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAPSWIDGET_H
#define MAPSWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>

#include "qgraphicsgeomap.h"
#include "qgeomappingmanager.h"
#include "qgeocoordinate.h"

using namespace QtMobility;

class MapsWidget;
class MarkerManager;
class Marker;
class StatusBarItem;
class ZoomButtonItem;

class GeoMap : public QGraphicsGeoMap
{
    Q_OBJECT

    Q_PROPERTY(double centerLatitude READ centerLatitude WRITE setCenterLatitude)
    Q_PROPERTY(double centerLongitude READ centerLongitude WRITE setCenterLongitude)

public:
    GeoMap(QGeoMappingManager *manager, MapsWidget *mapsWidget);
    ~GeoMap();

    double centerLatitude() const;
    void setCenterLatitude(double lat);
    double centerLongitude() const;
    void setCenterLongitude(double lon);

private:
    MapsWidget *mapsWidget;

    bool panActive;
    bool markerPressed;
    QGeoMapObject *pressed;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
    void clicked(Marker *marker);
    void panned();
};

class MapsWidgetPrivate;
class MapsWidget : public QWidget
{
    Q_OBJECT

public:
    MapsWidget(QWidget *parent = 0);
    ~MapsWidget();

    void setMarkerManager(MarkerManager *markerManager);
    MarkerManager *markerManager() const;

    QGraphicsGeoMap *map() const;
    StatusBarItem *statusBar() const;

    void animatedPanTo(QGeoCoordinate center);
    void setMyLocation(QGeoCoordinate location, bool center=true);

public slots:
    void initialize(QGeoMappingManager *manager);

signals:
    void markerClicked(Marker *marker);
    void mapPanned();

private:
    MapsWidgetPrivate *d;

    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
};


class StatusBarItemPrivate;
class StatusBarItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)

public:
    StatusBarItem();
    ~StatusBarItem();

    int offset() const;
    void setRect(qreal x, qreal y, qreal w, qreal h);

public slots:
    void setText(QString text);

    void showText(QString text, quint32 timeout=3000);
    void show();
    void hide();

    void setOffset(int offset);

private:
    StatusBarItemPrivate *d;
};

class ZoomButtonItem : public QGraphicsRectItem
{
public:
    ZoomButtonItem(GeoMap *map);

    void setRect(qreal x, qreal y, qreal w, qreal h);

private:
    GeoMap *map;

    QGraphicsSimpleTextItem *plusText;
    QGraphicsSimpleTextItem *minusText;

    bool pressedOverTopHalf;
    bool pressedOverBottomHalf;

    bool isTopHalf(const QPointF &point);
    bool isBottomHalf(const QPointF &point);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAPSWIDGET_H