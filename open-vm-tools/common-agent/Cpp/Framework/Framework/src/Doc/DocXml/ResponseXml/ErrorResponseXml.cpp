/*
 *  Author: bwilliams
 *  Created: April 6, 2012
 *
 *  Copyright (C) 2012-2016 VMware, Inc.  All rights reserved. -- VMware Confidential
 *
 *  This code was generated by the script "build/dev/codeGen/genCppXml". Please
 *  speak to Brian W. before modifying it by hand.
 *
 */

#include "stdafx.h"

#include "Doc/DocXml/ResponseXml/ResponseHeaderXml.h"

#include "Doc/ResponseDoc/CErrorResponseDoc.h"
#include "Doc/ResponseDoc/CResponseHeaderDoc.h"
#include "Xml/XmlUtils/CXmlElement.h"
#include "Doc/DocXml/ResponseXml/ErrorResponseXml.h"

using namespace Caf;

void ErrorResponseXml::add(
	const SmartPtrCErrorResponseDoc errorResponseDoc,
	const SmartPtrCXmlElement thisXml) {
	CAF_CM_STATIC_FUNC_VALIDATE("ErrorResponseXml", "add");

	CAF_CM_ENTER {
		CAF_CM_VALIDATE_SMARTPTR(errorResponseDoc);
		CAF_CM_VALIDATE_SMARTPTR(thisXml);

		const std::string clientIdVal =
			BasePlatform::UuidToString(errorResponseDoc->getClientId());
		if (! clientIdVal.empty()) {
			thisXml->addAttribute("clientId", clientIdVal);
		}

		const std::string requestIdVal =
			BasePlatform::UuidToString(errorResponseDoc->getRequestId());
		if (! requestIdVal.empty()) {
			thisXml->addAttribute("requestId", requestIdVal);
		}

		const std::string pmeIdVal = errorResponseDoc->getPmeId();
		if (! pmeIdVal.empty()) {
			thisXml->addAttribute("pmeId", pmeIdVal);
		}

		const SmartPtrCResponseHeaderDoc responseHeaderVal =
			errorResponseDoc->getResponseHeader();
		if (! responseHeaderVal.IsNull()) {
			const SmartPtrCXmlElement responseHeaderXml =
				thisXml->createAndAddElement("responseHeader");
			ResponseHeaderXml::add(responseHeaderVal, responseHeaderXml);
		}

		const std::string errorMessageVal = errorResponseDoc->getErrorMessage();
		if (! errorMessageVal.empty()) {
			const SmartPtrCXmlElement errorMessageXml =
				thisXml->createAndAddElement("errorMessage");
			errorMessageXml->setValue(errorMessageVal);
		}
	}
	CAF_CM_EXIT;
}

SmartPtrCErrorResponseDoc ErrorResponseXml::parse(
	const SmartPtrCXmlElement thisXml) {
	CAF_CM_STATIC_FUNC_VALIDATE("ErrorResponseXml", "parse");

	SmartPtrCErrorResponseDoc errorResponseDoc;

	CAF_CM_ENTER {
		CAF_CM_VALIDATE_SMARTPTR(thisXml);

		const std::string clientIdStrVal =
			thisXml->findOptionalAttribute("clientId");
		UUID clientIdVal = CAFCOMMON_GUID_NULL;
		if (! clientIdStrVal.empty()) {
			BasePlatform::UuidFromString(clientIdStrVal.c_str(), clientIdVal);
		}

		const std::string requestIdStrVal =
			thisXml->findOptionalAttribute("requestId");
		UUID requestIdVal = CAFCOMMON_GUID_NULL;
		if (! requestIdStrVal.empty()) {
			BasePlatform::UuidFromString(requestIdStrVal.c_str(), requestIdVal);
		}

		const std::string pmeIdVal =
			thisXml->findOptionalAttribute("pmeId");

		const SmartPtrCXmlElement responseHeaderXml =
			thisXml->findOptionalChild("responseHeader");
		SmartPtrCResponseHeaderDoc responseHeaderVal;
		if (! responseHeaderXml.IsNull()) {
			responseHeaderVal = ResponseHeaderXml::parse(responseHeaderXml);
		}

		const SmartPtrCXmlElement errorMessageXml =
			thisXml->findOptionalChild("errorMessage");
		std::string errorMessageVal;
		if (! errorMessageXml.IsNull()) {
			errorMessageVal = errorMessageXml->getValue();
		}

		errorResponseDoc.CreateInstance();
		errorResponseDoc->initialize(
			clientIdVal,
			requestIdVal,
			pmeIdVal,
			responseHeaderVal,
			errorMessageVal);
	}
	CAF_CM_EXIT;

	return errorResponseDoc;
}
