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
#include <QObject>

#include <cntdb.h>
#include <cntitem.h>
#include <qtcontacts.h>
#include "cnttransformcontactdata.h"

class TestCntTransformContactData : public QObject
{
    Q_OBJECT

private slots:
	void initTestCase();
	void cleanupTestCase();

	void executeCntTransformEmail();
	void executeCntTransformName();
	void executeCntTransformNickname();
	void executeCntTransformPhonenumber();
	void executeCntTransformAddress();
	void executeCntTransformUrl();
	void executeCntTransformBithday();
#ifdef SYMBIAN_BACKEND_USE_CNTMODEL_V2
	void executeCntTransformOnlineAccount();
	void executeCntTransformPresence();	
#endif
	void executeCntTransformOrganisation();
	void executeCntTransformAvatar();
	void executeCntTransformRingtone();
	void executeCntTransformSyncTarget();
	void executeCntTransformGender();
	void executeCntTransformAnniversary();
	void executeCntTransformGeolocation();
	void executeCntTransformNote();
	void executeCntTransformFamily();

private:
    void validateCntTransformEmailL(TPtrC16 field, QString detail);
    void validateCntTransformNameL(TPtrC16 prefixField, QString prefixDetail,
                               TPtrC16 firstnameField, QString firstnameDetail,
                               TPtrC16 middlenameField, QString middlenameDetail,
                               TPtrC16 lastnameField, QString lastnameDetail,
                               TPtrC16 suffixField, QString suffixDetail,
                               TPtrC16 customLabelField, QString customLabelDetail);
    void validateCntTransformNicknameL(TPtrC16 field, QString detail);
    void validateCntTransformPhonenumberL(TPtrC16 field, QString detail);
    void validateCntTransformAddressL(TPtrC16 countryField, QString countryDetail,
                                  TPtrC16 postcodeField, QString postcodeDetail,
                                  TPtrC16 streetField, QString streetDetail,
                                  TPtrC16 localityField, QString localityDetail,
                                  TPtrC16 regionField, QString regionDetail,
                                  TPtrC16 postOfficeBoxField, QString postOfficeBoxDetail);
    void validateCntTransformUrlL(TPtrC16 field, QString detail);
    void validateCntTransformBirthdayL(TTime field, QDate detail);
#ifdef SYMBIAN_BACKEND_USE_CNTMODEL_V2
    void validateCntTransformOnlineAccountL(
        TPtrC16 sipField, QString sipDetail,
        TPtrC16 providerField, QString providerDetail);
    void validateCntTransformPresenceL(TPtrC16 presenceStateField, QString presenceStateDetail,
                                 TPtrC16 presenceStatusMsgField, QString presenceStatusMsgDetail);
#endif
    void validateCntTransformOrganisationL(TPtrC16 companyField, QString companyDetail,
                                       TPtrC16 departmentField, QStringList departmentDetail,
                                       TPtrC16 jobtitleField, QString jobtitleDetail,
                                       TPtrC16 assistantField, QString assistantDetail);
    void validateCntTransformAvatarL(TPtrC16 field, QString detail);
    void validateCntTransformRingtoneL(TPtrC16 audioRingtoneField, QString audioRingtoneDetail,
                                       TPtrC16 videoRingtoneField, QString videoRingtoneDetail);
    void validateCntTransformSyncTargetL(TPtrC16 field, QString detail);
    void validateCntTransformGenderL(TPtrC16 field, QString detail);
    void validateCntTransformAnniversaryL(TTime dateField, QDate dateDetail, TPtrC16 eventField, QString eventDetail);
    void validateCntTransformGeolocationL(TPtrC16 field, double latitudeDetail, double longitudeDetail);
    void validateCntTransformNoteL(TPtrC16 field, QString detail);
    void validateCntTransformFamilyL(TPtrC16 spouseField, QString spouseDetail,
                                 TPtrC16 childField, QString childDetail);
    void validateContextsL(CntTransformContactData* transformContactData) const;
    void validateGetIdForField(
                        const CntTransformContactData& transformContactData,
                        const QString& filedname,
                        const quint32  idValue) const;
    void validateSupportedSortingFieldTypes(
            const CntTransformContactData& transformContactData,
            const QString& filedname,
            const QList<TUid>&  checkSortFieldList )const;
};
