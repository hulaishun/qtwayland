/****************************************************************************
**
** Copyright (C) 2014 Jolla Ltd, author: <giulio.camuffo@jollamobile.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDSURFACEVIEW_H
#define QWAYLANDSURFACEVIEW_H

#include <QtCompositor/QWaylandBufferRef>
#include <QtCompositor/qwaylandexport.h>

#include <QtCore/QPointF>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE

class QWaylandSurface;
class QWaylandViewPrivate;
class QWaylandOutput;

class Q_COMPOSITOR_EXPORT QWaylandView : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWaylandView)
    Q_PROPERTY(QObject *renderObject READ renderObject CONSTANT)
    Q_PROPERTY(QWaylandSurface *surface READ surface WRITE setSurface NOTIFY surfaceChanged)
    Q_PROPERTY(QWaylandOutput *output READ output WRITE setOutput NOTIFY outputChanged)
    Q_PROPERTY(QPointF requestedPosition READ requestedPosition WRITE setRequestedPosition NOTIFY requestedPositionChanged)
    Q_PROPERTY(qreal requestedXPosition READ requestedXPosition WRITE setRequestedXPosition NOTIFY requestedXPositionChanged)
    Q_PROPERTY(qreal requestedYPosition READ requestedYPosition WRITE setRequestedYPosition NOTIFY requestedYPositionChanged)
    Q_PROPERTY(bool bufferLock READ isBufferLocked WRITE setBufferLock NOTIFY bufferLockChanged)
public:
    QWaylandView(QObject *renderObject = 0, QObject *parent = 0);
    virtual ~QWaylandView();

    QObject *renderObject() const;

    QWaylandSurface *surface() const;
    void setSurface(QWaylandSurface *surface);

    QWaylandOutput *output() const;
    void setOutput(QWaylandOutput *output);

    QPointF requestedPosition() const;
    void setRequestedPosition(const QPointF &pos);
    qreal requestedXPosition() const;
    void setRequestedXPosition(qreal xPos);
    qreal requestedYPosition() const;
    void setRequestedYPosition(qreal yPos);

    virtual void attach(const QWaylandBufferRef &ref, const QRegion &damage);
    virtual bool advance();
    virtual QWaylandBufferRef currentBuffer();
    virtual QRegion currentDamage();

    bool isBufferLocked() const;
    void setBufferLock(bool locked);

    struct wl_resource *surfaceResource() const;

Q_SIGNALS:
    void surfaceChanged();
    void surfaceDestroyed();
    void outputChanged();
    void requestedPositionChanged();
    void requestedXPositionChanged();
    void requestedYPositionChanged();
    void bufferLockChanged();
};

QT_END_NAMESPACE

#endif