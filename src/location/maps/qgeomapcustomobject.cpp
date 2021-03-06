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

#include "qgeomapcustomobject.h"
#include "qgeomapcustomobject_p.h"
#include "qgeoboundingbox.h"

#include <QGraphicsItem>

QTM_BEGIN_NAMESPACE

/*!
    \class QGeoMapCustomObject
    \brief The QGeoMapCustomObject class is a QGeoMapObject used to draw
    a QGraphicsItem on a map.

    \inmodule QtLocation

    \ingroup maps-mapping-objects
    \since 1.2

    Any arbitrary QGraphicsItem can be associated with a QGeoMapCustomObject, and to
    this end it contains support for interpreting the coordinates of the
    QGraphicsItem in a variety of different ways.

    For example, the following code creates a QGraphicsEllipseItem and a
    QGeoMapCustomObject to display it. The EllipseItem extends from the origin point,
    out 20 meters to the east and 30 metres south.

    \code
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem;
    ellipseItem->setRect(0, 0, 20, 30);

    QGeoMapCustomObject *mapObject = new QGeoMapCustomObject;
    mapObject->setGraphicsItem(ellipseItem);
    mapObject->setUnits(QGeoMapObject::MeterUnit);
    mapObject->setOrigin(QGeoCoordinate(-27.5796, 153.1));
    \endcode

    \section2 Units and coordinates

    The local units and coordinates of the QGraphicsItem are transformed
    onto the map based on the \a units, \a origin, \a transformType and
    \a transform properties. Several systems are available, including
    pixels, meters and seconds of arc.

    It should be noted that both pixel and meter coordinate systems are south-
    oriented (ie, positive Y axis faces south on the map). However, the
    RelativeArcSeconds unit system faces north to align with the standard
    latitude grid. The Y axis can be flipped if necessary by making use of the
    GraphicsItem's \a transform property

    \code
    QTransform northFlip;
    northFlip.scale(0, -1);

    ellipseItem->setTransform(northFlip);
    \endcode

    \section2 Transform methods

    Normally, the GraphicsItem will be transformed into map coordinates using
    a bilinear interpolation. Another option is the ExactTransform, which
    converts the GraphicsItem exactly into map coordinates, but is only available
    for certain subclasses of QGraphicsItem. Other interpolation methods may
    be provided in future for greater accuracy near poles and in different
    map projections, without the limitations of ExactTransform.

    Calling setUnits() or setting the units property will result in the
    default value of transformType being restored. See QGeoMapObject::transformType
    for more details.

    \section2 Caveats

    Other than the coordinate system features, there are a few differences
    with using QGraphicsItems on a map compared to using them on a standard
    QGraphicsScene. One of the most important of these is the use of the
    \a update() function. When an application changes anything that has an
    effect upon the appearance, size, shape etc of the QGraphicsItem, it
    must call \a QGeoMapCustomObject::update() to ensure that the map is updated.

    Another is the use of child items of a QGraphicsItem. These are supported
    in more or less the same manner as in QGraphicsScene, with the exception
    of use in concert with \a ExactTransform -- any object with transformType
    set to \a ExactTransform will not have children of its QGraphicsItem drawn
    on the map.
*/

/*!
    Constructs a new custom object.
*/
QGeoMapCustomObject::QGeoMapCustomObject()
    : d_ptr(new QGeoMapCustomObjectPrivate())
{
}

/*!
    Constructs a new custom object which will draw a QGraphicsItem at an
    offset of \a offset pixels from the coordinate \a coordinate.
    \since 1.2
*/
QGeoMapCustomObject::QGeoMapCustomObject(const QGeoCoordinate &coordinate, const QPoint &offset)
    : d_ptr(new QGeoMapCustomObjectPrivate())
{
    setOrigin(coordinate);
    d_ptr->offset = offset;
}

/*!
    Destroys this custom object.
*/
QGeoMapCustomObject::~QGeoMapCustomObject()
{
    delete d_ptr;
}

/*!
    \reimp
    \since 1.2
*/
QGeoMapObject::Type QGeoMapCustomObject::type() const
{
    return QGeoMapObject::CustomType;
}

/*!
    If the graphics item is modified this
    method should be called immediately afterwards to inform
    the map that an update is required. .

    This method causes the triggerUpdate() signal to be emitted.
    \since 1.2
*/
void QGeoMapCustomObject::update()
{
    emit triggerUpdate();
}

/*!
\fn void QGeoMapCustomObject::triggerUpdate()

    This signal indicates that the graphics item has
    changed and that the map needs to be updated.
    \since 1.2
*/

/*!
    \property QGeoMapCustomObject::graphicsItem
    \brief the graphics item which will
    be drawn by this custom object.

    If the graphics item is 0 then nothing will be drawn.
    \since 1.2
*/

QGraphicsItem* QGeoMapCustomObject::graphicsItem() const
{
    return d_ptr->graphicsItem;
}

void QGeoMapCustomObject::setGraphicsItem(QGraphicsItem *graphicsItem)
{
    if (d_ptr->graphicsItem == graphicsItem)
        return;

    d_ptr->graphicsItem = graphicsItem;

    emit graphicsItemChanged(graphicsItem);
}

/*!
\fn void QGeoMapCustomObject::graphicsItemChanged(QGraphicsItem *graphicsItem)

    This signal is emitted when the graphics item which this custom object
    draws is changed.

    The new value will be \a graphicsItem.
    \since 1.2
*/

/*!
    \property QGeoMapCustomObject::offset
    \brief the offset in pixels at which the graphics
    item will be drawn by this custom object.

    The default value of this property is QPoint(0, 0). If this value is not
    changed the upper left coordinate of the graphics item will be drawn at the
    coordinate specified by QGeoMapCustomObject::coordinate.

    The offset is in pixels and is independent of the zoom level of the map.
    \since 1.2
*/
QPoint QGeoMapCustomObject::offset() const
{
    return d_ptr->offset;
//    QPointF pt = d_ptr->offset;
//
//    QPoint rounded;
//    rounded.setX(int(pt.x() > 0 ? pt.x() + 0.5 : pt.x() - 0.5));
//    rounded.setY(int(pt.y() > 0 ? pt.y() + 0.5 : pt.y() - 0.5));
//
//    return rounded;
}

void QGeoMapCustomObject::setOffset(const QPoint &offset)
{
    if (d_ptr->offset != offset) {
        d_ptr->offset = offset;
        emit offsetChanged(offset);
    }
}

/*!
\fn void QGeoMapCustomObject::offsetChanged(const QPoint &offset)

    This signal is emitted when the on-screen offset from the coordinate
    at which this custom object should be drawn has changed.

    The new value will be \a offset.
    \since 1.2
*/

/*!
    Sets the origin of the object to \a origin.
    \since 1.2
*/
void QGeoMapCustomObject::setOrigin(const QGeoCoordinate &origin)
{
    QGeoMapObject::setOrigin(origin);
}

/*!
    Sets the coordinate units of the object to \a unit.

    Note that setting this property will reset the transformType property to
    the default for the units given. For PixelUnit, this is ExactTransform,
    and for all others, BilinearTransform.
    \since 1.2
*/
void QGeoMapCustomObject::setUnits(const CoordinateUnit &unit)
{
    QGeoMapObject::setUnits(unit);
}

/*!
    Sets the transform type of the object to \a type.
    \since 1.2
*/
void QGeoMapCustomObject::setTransformType(const TransformType &type)
{
    QGeoMapObject::setTransformType(type);
}

/*******************************************************************************
*******************************************************************************/

QGeoMapCustomObjectPrivate::QGeoMapCustomObjectPrivate()
    : graphicsItem(0) {}

QGeoMapCustomObjectPrivate::~QGeoMapCustomObjectPrivate()
{
}

#include "moc_qgeomapcustomobject.cpp"

QTM_END_NAMESPACE

