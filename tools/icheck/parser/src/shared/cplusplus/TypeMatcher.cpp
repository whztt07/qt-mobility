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

#include "TypeMatcher.h"
#include "CoreTypes.h"
#include "Symbols.h"
#include "Names.h"
#include "Literals.h"

using namespace CPlusPlus;

TypeMatcher::TypeMatcher()
{
}

TypeMatcher::~TypeMatcher()
{
}

bool TypeMatcher::isEqualTo(const Name *name, const Name *otherName) const
{
    if (name == otherName)
        return true;

    else if (! name || ! otherName)
        return false;

    return name->isEqualTo(otherName);
}

bool TypeMatcher::match(const UndefinedType *, const UndefinedType *)
{
    return true;
}

bool TypeMatcher::match(const VoidType *, const VoidType *)
{
    return true;
}

bool TypeMatcher::match(const IntegerType *type, const IntegerType *otherType)
{
    if (type == otherType)
        return true;

    else if (type->kind() != otherType->kind())
        return false;

    return true;
}

bool TypeMatcher::match(const FloatType *type, const FloatType *otherType)
{
    if (type == otherType)
        return true;

    else if (type->kind() != otherType->kind())
        return false;

    return true;
}

bool TypeMatcher::match(const PointerToMemberType *type, const PointerToMemberType *otherType)
{
    if (type == otherType)
        return true;

    else if (! isEqualTo(type->memberName(), otherType->memberName()))
        return false;

    else if (! type->elementType().match(otherType->elementType(), this))
        return false;

    return true;
}

bool TypeMatcher::match(const PointerType *type, const PointerType *otherType)
{
    if (type == otherType)
        return true;

    else if (! type->elementType().match(otherType->elementType(), this))
        return false;

    return true;
}

bool TypeMatcher::match(const ReferenceType *type, const ReferenceType *otherType)
{
    if (type == otherType)
        return true;

    else if (! type->elementType().match(otherType->elementType(), this))
        return false;

    return true;
}

bool TypeMatcher::match(const ArrayType *type, const ArrayType *otherType)
{
    if (type == otherType)
        return true;

    else if (type->size() != otherType->size())
        return false;

    else if (! type->elementType().match(otherType->elementType(), this))
        return false;

    return true;
}

bool TypeMatcher::match(const NamedType *type, const NamedType *otherType)
{
    if (type == otherType)
        return true;

    else if (! isEqualTo(type->name(), otherType->name()))
        return false;

    return true;
}

bool TypeMatcher::match(const Function *type, const Function *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const Enum *type, const Enum *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const Namespace *type, const Namespace *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ForwardClassDeclaration *type, const ForwardClassDeclaration *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const Class *type, const Class *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ObjCClass *type, const ObjCClass *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ObjCProtocol *type, const ObjCProtocol *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ObjCForwardClassDeclaration *type, const ObjCForwardClassDeclaration *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ObjCForwardProtocolDeclaration *type, const ObjCForwardProtocolDeclaration *otherType)
{
    if (type != otherType)
        return false;

    return true;
}

bool TypeMatcher::match(const ObjCMethod *type, const ObjCMethod *otherType)
{
    if (type != otherType)
        return false;

    return true;
}
