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

#include "qgeomapcircleobject.h"
#include "qgeomapcircleobject_p.h"

#include "qgeocoordinate.h"

#include <QDebug>

QTM_BEGIN_NAMESPACE

/*!
    \class QGeoMapCircleObject
    \brief The QGeoMapCircleObject class is a QGeoMapObject used to draw the region
    within a given distance of a coordinate.

    \inmodule QtLocation
    \since 1.1

    \ingroup maps-mapping-objects

    The circle is specified by either a valid QGeoBoundingCircle instance or a
    valid QGeoCoordinate instance and a qreal with value greater than 0.0,
    which represent the center of the circle and the radius of the circle in
    metres respectively.

    The circle may appear as an ellipse on maps which use the Mercator
    projection. This is done so that the circle accurately covers all points at
    a distance of the radius or less from the center.
*/

/*!
    Constructs a new circle object.
*/
QGeoMapCircleObject::QGeoMapCircleObject()
    : d_ptr(new QGeoMapCircleObjectPrivate())
{
    setUnits(QGeoMapObject::MeterUnit);
    setTransformType(QGeoMapObject::ExactTransform);
}

/*!
    Constructs a new circle object based on the circle \a circle.
    \since 1.1
*/
QGeoMapCircleObject::QGeoMapCircleObject(const QGeoBoundingCircle &circle)
    : d_ptr(new QGeoMapCircleObjectPrivate())
{
    d_ptr->circle = circle;
    setUnits(QGeoMapObject::MeterUnit);
    setTransformType(QGeoMapObject::ExactTransform);
}

/*!
    Constructs a new circle object with a center at coordinate \a center
    and a radius in meters of \a radius.
    \since 1.1
*/
QGeoMapCircleObject::QGeoMapCircleObject(const QGeoCoordinate &center, qreal radius)
    : d_ptr(new QGeoMapCircleObjectPrivate())
{
    d_ptr->circle = QGeoBoundingCircle(center, radius);
    setUnits(QGeoMapObject::MeterUnit);
    setTransformType(QGeoMapObject::ExactTransform);
    setOrigin(center);
}

/*!
    Destroys this circle object.
*/
QGeoMapCircleObject::~QGeoMapCircleObject()
{
    delete d_ptr;
}

/*!
    \reimp
    \since 1.1
*/
QGeoMapObject::Type QGeoMapCircleObject::type() const
{
    return QGeoMapObject::CircleType;
}

/*!
    \property QGeoMapCircleObject::pen
    \brief the pen that will be used to draw this object.

    The pen is used to draw an outline around the circle. The circle is
    filled using the QGeoMapCircleObject::brush property.

    The pen will be treated as a cosmetic pen, which means that the width
    of the pen will be independent of the zoom level of the map.
    \since 1.1
*/
void QGeoMapCircleObject::setPen(const QPen &pen)
{
    QPen newPen = pen;
    newPen.setCosmetic(true);
    const QPen oldPen = d_ptr->pen;

    if (oldPen == newPen)
        return;

    d_ptr->pen = newPen;
    emit penChanged(newPen);
}

QPen QGeoMapCircleObject::pen() const
{
    return d_ptr->pen;
}

/*!
  \reimp
  \since 1.2
  */
bool QGeoMapCircleObject::contains(const QGeoCoordinate &coordinate) const
{
    return d_ptr->circle.contains(coordinate);
}

/*!
    \property QGeoMapCircleObject::brush
    \brief the brush that will be used to draw this object.

    The brush is used to fill in circle.

    The outline around the perimeter of the circle is drawn using the
    QGeoMapCircleObject::pen property.
    \since 1.1
*/
void QGeoMapCircleObject::setBrush(const QBrush &brush)
{
    if (d_ptr->brush != brush) {
        d_ptr->brush = brush;
        emit brushChanged(brush);
    }
}

QBrush QGeoMapCircleObject::brush() const
{
    return d_ptr->brush;
}

/*!
    \property QGeoMapCircleObject::pointCount
    \brief the number of vertices used in an approximate polygon.

    \since 1.2

    For a circle using ExactTransform, this property describes the number
    of sides that should be used to generate a polygonal approximation which
    is then transformed vertex-by-vertex into screen coordinates.
*/
quint32 QGeoMapCircleObject::pointCount() const
{
    return d_ptr->pointCount;
}

void QGeoMapCircleObject::setPointCount(quint32 pointCount)
{
    d_ptr->pointCount = pointCount;
}

/*!
    Returns a QGeoBoundingCircle instance which corresponds to the circle that
    will be drawn by this object.

    This is equivalent to
    \code
        QGeoMapCircleObject *object;
        // setup object
        QGeoBoundingCircle(object->center(), object->radius());
    \endcode
    \since 1.1
*/
QGeoBoundingCircle QGeoMapCircleObject::circle() const
{
    return d_ptr->circle;
}

/*!
    Sets the circle that will be drawn by this object to \a circle.

    This is equivalent to
    \code
        QGeoMapCircleObject *object;
        // setup object
        object->setCenter(circle.center());
        object->setRadius(circle.radius());
    \endcode
    \since 1.1
*/
void QGeoMapCircleObject::setCircle(const QGeoBoundingCircle &circle)
{
    QGeoBoundingCircle oldCircle = d_ptr->circle;

    if (oldCircle == circle)
        return;

    d_ptr->circle = circle;
    setOrigin(circle.center());
    setRadius(circle.radius());

    if (oldCircle.center() != d_ptr->circle.center())
        emit centerChanged(d_ptr->circle.center());

    if (oldCircle.radius() != d_ptr->circle.radius())
        emit radiusChanged(d_ptr->circle.radius());
}

/*!
    \property QGeoMapCircleObject::center

    \brief the coordinate of the center of the circle to be
    drawn by this circle object.

    The default value of this property is an invalid coordinate.  While the
    value of this property is invalid the circle object will not be displayed.
    \since 1.1
*/
void QGeoMapCircleObject::setCenter(const QGeoCoordinate &center)
{
    if (d_ptr->circle.center() != center) {
        d_ptr->circle.setCenter(center);
        setOrigin(center);
        emit centerChanged(center);
    }
}

QGeoCoordinate QGeoMapCircleObject::center() const
{
    return d_ptr->circle.center();
}

/*!
    \property QGeoMapCircleObject::radius
    \brief the radius in metres of the circle that will be
    drawn by this circle object.

    The default value of this property is -1.0. While the value of this
    property is not greater than 0 the circle object will not be displayed.
    \since 1.1
*/
void QGeoMapCircleObject::setRadius(qreal radius)
{
    if (d_ptr->circle.radius() != radius) {
        d_ptr->circle.setRadius(radius);
        emit radiusChanged(radius);
    }
}

qreal QGeoMapCircleObject::radius() const
{
    return d_ptr->circle.radius();
}

/*!
\fn void QGeoMapCircleObject::centerChanged(const QGeoCoordinate &center)

    This signal is emitted when the center of the circle object has
    changed.

    The new value is \a center.
    \since 1.1
*/

/*!
\fn void QGeoMapCircleObject::radiusChanged(qreal radius)

    This signal is emitted when the radius of the circle object has
    changed.

    The new value is \a radius.
    \since 1.1
*/

/*!
\fn void QGeoMapCircleObject::penChanged(const QPen &pen)

    This signal is emitted when the pen used to draw the edge of
    the circle object has changed.

    The new value is \a pen.
    \since 1.1
*/

/*!
\fn void QGeoMapCircleObject::brushChanged(const QBrush &brush)

    This signal is emitted when the brush used to fill the inside of
    the circle object has changed.

    The new value is \a brush.
    \since 1.1
*/

/*******************************************************************************
*******************************************************************************/

QGeoMapCircleObjectPrivate::QGeoMapCircleObjectPrivate() :
    pointCount(120)
{
    pen.setCosmetic(true);
}

QGeoMapCircleObjectPrivate::~QGeoMapCircleObjectPrivate()
{
}

#include "moc_qgeomapcircleobject.cpp"

QTM_END_NAMESPACE

