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

#ifndef ICHANNELTUBE_H
#define ICHANNELTUBE_H

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

#include "maemo/interfaces/itypes.h"
#include "maemo/interfaces/iabstract.h"
#include "maemo/interfaces/ichannel.h"
#include "maemo/dbusproxy.h"

namespace DBus
{
    namespace Interfaces
    {
        class IChannelTube : public DBus::IAbstract
        {
            Q_OBJECT

        public:
            static inline const char *staticInterfaceName()
            {
                return "org.freedesktop.Telepathy.Channel.Interface.Tube";
            }

            IChannelTube(
                const QString& busName,
                const QString& objectPath,
                QObject* parent = 0
            );
            IChannelTube(
                const QDBusConnection& connection,
                const QString& busName,
                const QString& objectPath,
                QObject* parent = 0
            );
            IChannelTube(DBus::DBusProxy *proxy);
            explicit IChannelTube(const DBus::Interfaces::IChannel& mainInterface);
            IChannelTube(const DBus::Interfaces::IChannel& mainInterface, QObject* parent);

            Q_PROPERTY(QVariantMap Parameters READ Parameters)
            inline QVariantMap Parameters() const
            {
                return qvariant_cast<QVariantMap>(internalPropGet("Parameters"));
            }

            Q_PROPERTY(uint State READ State)
            inline uint State() const
            {
                return qvariant_cast<uint>(internalPropGet("State"));
            }

        Q_SIGNALS:
            void TubeChannelStateChanged(uint state);

        protected:
            virtual void invalidate(DBus::DBusProxy *, const QString &, const QString &);
        };
    }
}
Q_DECLARE_METATYPE(DBus::Interfaces::IChannelTube*)

#endif //ICHANNELTUBE_H