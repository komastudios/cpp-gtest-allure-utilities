#pragma once

#include "JSONAdapterInterface/IJSONSchemaValidator.h"

#include <map>
#include <memory>
#include <rapidjson/schema.h>


namespace systelab { namespace json {
	class IJSONRemoteSchemaProvider;
}}

namespace systelab { namespace json { namespace rapidjson {

	class JSONSchemaValidator : public IJSONSchemaValidator
	{
	private:
		class RapidjsonSchemaRemoteDocumentProvider : public ::RAPIDJSON_NAMESPACE::IRemoteSchemaDocumentProvider
		{
		public:
			RapidjsonSchemaRemoteDocumentProvider(const IJSONRemoteSchemaProvider&);

			virtual const ::RAPIDJSON_NAMESPACE::SchemaDocument* GetRemoteDocument(const char* uri, ::RAPIDJSON_NAMESPACE::SizeType length);

		private:
			const IJSONRemoteSchemaProvider& m_remoteSchemaProvider;
			std::map<std::string, std::unique_ptr<::RAPIDJSON_NAMESPACE::SchemaDocument> > m_remoteSchemaMap;

			std::unique_ptr<::RAPIDJSON_NAMESPACE::SchemaDocument> buildSchemaDocument(const std::string& uri);
		};

	public:
		JSONSchemaValidator(const IJSONDocument&);
		JSONSchemaValidator(const IJSONDocument&, const IJSONRemoteSchemaProvider&);
		virtual ~JSONSchemaValidator();

		bool validate(const IJSONDocument&, std::string& reason) const;

	private:
		std::unique_ptr<RapidjsonSchemaRemoteDocumentProvider> m_rapidjsonRemoteSchemaProvider;
		std::unique_ptr<::RAPIDJSON_NAMESPACE::SchemaDocument> m_schemaDocument;
	};

}}}
