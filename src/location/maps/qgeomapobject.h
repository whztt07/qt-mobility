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

#ifndef QGEOMAPOBJECT_H
#define QGEOMAPOBJECT_H

#include "qmobilityglobal.h"

#include <QList>
#include <QObject>

class QPainter;
class QRectF;
class QGraphicsItem;

QTM_BEGIN_NAMESPACE

class QGeoCoordinate;
class QGeoBoundingBox;
class QGeoMapObjectPrivate;
class QGeoMapContainer;
class QGeoMapObjectInfo;

class QGeoMapData;

class Q_LOCATION_EXPORT QGeoMapObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int zValue READ zValue WRITE setZValue NOTIFY zValueChanged)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool selected READ isSelected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QGeoCoordinate origin READ origin NOTIFY originChanged)
    Q_PROPERTY(CoordinateUnit units READ units NOTIFY unitsChanged)
    Q_PROPERTY(TransformType transformType READ transformType NOTIFY transformTypeChanged)

public:
    enum Type {
        NullType,
        GroupType,
        RectangleType,
        CircleType,
        PolylineType,
        PolygonType,
        PixmapType,
        TextType,
        RouteType,
        CustomType
    };

    enum CoordinateUnit {
        PixelUnit,
        MeterUnit,
        RelativeArcSecondUnit,
        AbsoluteArcSecondUnit
    };

    enum TransformType {
        BilinearTransform,
        ExactTransform
    };

    QGeoMapObject(QGeoMapData *mapData = 0);
    virtual ~QGeoMapObject();

    virtual Type type() const;

    void setZValue(int zValue);
    int zValue() const;

    void setVisible(bool visible);
    bool isVisible() const;

    void setSelected(bool selected);
    bool isSelected() const;

    virtual QGeoBoundingBox boundingBox() const;
    virtual bool contains(const QGeoCoordinate &coordinate) const;

    bool operator<(const QGeoMapObject &other) const;
    bool operator>(const QGeoMapObject &other) const;

    virtual void setMapData(QGeoMapData *mapData);
    virtual QGeoMapData* mapData() const;

    QGeoMapObjectInfo *info() const;

    QGeoCoordinate origin() const;
    CoordinateUnit units() const;
    TransformType transformType() const;

protected:
    void setOrigin(const QGeoCoordinate &origin);
    void setUnits(const CoordinateUnit &unit);
    void setTransformType(const TransformType &type);

Q_SIGNALS:
    void zValueChanged(int zValue);
    void visibleChanged(bool visible);
    void selectedChanged(bool selected);

    void originChanged(QGeoCoordinate origin);
    void unitsChanged(QGeoMapObject::CoordinateUnit units);
    void transformTypeChanged(QGeoMapObject::TransformType transformType);

private:
    QGeoMapObjectPrivate *d_ptr;
    Q_DECLARE_PRIVATE(QGeoMapObject)
    Q_DISABLE_COPY(QGeoMapObject)

    friend class QGeoMapDataPrivate;
    friend class QGeoMapGroupObject;
};

QTM_END_NAMESPACE

#endif
