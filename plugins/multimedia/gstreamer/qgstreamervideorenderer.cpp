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

#include "qgstreamervideorenderer.h"
#include "qvideosurfacegstsink.h"
#include "qabstractvideosurface.h"

#include <QEvent>
#include <QApplication>
#include <QDebug>

#include <gst/gst.h>

QGstreamerVideoRenderer::QGstreamerVideoRenderer(QObject *parent)
    :QVideoRendererControl(parent),m_videoSink(0), m_surface(0)
{
}

QGstreamerVideoRenderer::~QGstreamerVideoRenderer()
{
    if (m_videoSink)
        gst_object_unref(GST_OBJECT(m_videoSink));
}

GstElement *QGstreamerVideoRenderer::videoSink()
{
    if (!m_videoSink && m_surface) {
        m_videoSink = QVideoSurfaceGstSink::createSink(m_surface);
        gst_object_ref(GST_OBJECT(m_videoSink)); //Take ownership
        gst_object_sink(GST_OBJECT(m_videoSink));
    }

    return reinterpret_cast<GstElement*>(m_videoSink);
}


QAbstractVideoSurface *QGstreamerVideoRenderer::surface() const
{
    return m_surface;
}

void QGstreamerVideoRenderer::setSurface(QAbstractVideoSurface *surface)
{
    if (m_surface != surface) {
        //qDebug() << Q_FUNC_INFO << surface;
        if (m_videoSink)
            gst_object_unref(GST_OBJECT(m_videoSink));

        m_videoSink = 0;

        if (m_surface) {
            disconnect(m_surface, SIGNAL(supportedFormatsChanged()),
                       this, SLOT(handleFormatChange()));
        }
        
        m_surface = surface;

        if (surface && !m_surface)
            emit readyChanged(true);

        if (!surface && m_surface)
            emit readyChanged(false);

        if (m_surface) {
            connect(m_surface, SIGNAL(supportedFormatsChanged()),
                    this, SLOT(handleFormatChange()));
        }

        emit sinkChanged();
    }
}

void QGstreamerVideoRenderer::handleFormatChange()
{
    //qDebug() << "Supported formats list has changed, reload video output";

    if (m_videoSink)
        gst_object_unref(GST_OBJECT(m_videoSink));

    m_videoSink = 0;
    emit sinkChanged();
}
