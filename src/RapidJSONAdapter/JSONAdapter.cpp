#include "JSONAdapter.h"

#include "JSONDocument.h"
#include "JSONSchemaValidator.h"


namespace systelab { namespace json { namespace rapidjson {

	JSONAdapter::JSONAdapter()
	{
	}

	JSONAdapter::~JSONAdapter() = default;

	std::unique_ptr<IJSONDocument> JSONAdapter::buildEmptyDocument() const
	{
		std::unique_ptr<::RAPIDJSON_NAMESPACE::Document> rapidjsonDocument = std::make_unique<::RAPIDJSON_NAMESPACE::Document>();
		return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
	}

	std::unique_ptr<IJSONDocument> JSONAdapter::buildDocumentFromString(const std::string& content) const
	{
		std::unique_ptr<::RAPIDJSON_NAMESPACE::Document> rapidjsonDocument = std::make_unique<::RAPIDJSON_NAMESPACE::Document>();
		rapidjsonDocument->Parse(content);
		if (!rapidjsonDocument->HasParseError())
		{
			return std::make_unique<JSONDocument>(std::move(rapidjsonDocument));
		}
		else
		{
			return std::unique_ptr<IJSONDocument>();
		}
	}

	std::unique_ptr<IJSONSchemaValidator> JSONAdapter::buildSchemaValidator(const IJSONDocument& jsonDocument) const
	{
		return std::make_unique<JSONSchemaValidator>(jsonDocument);
	}

	std::unique_ptr<IJSONSchemaValidator> JSONAdapter::buildSchemaValidator(const IJSONDocument& jsonDocument,
																			const IJSONRemoteSchemaProvider& remoteSchemaProvider) const
	{
		return std::make_unique<JSONSchemaValidator>(jsonDocument, remoteSchemaProvider);
	}

}}}
