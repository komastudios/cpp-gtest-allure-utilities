#include "JSONDocument.h"

#include "JSONValue.h"

#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


namespace systelab { namespace json { namespace rapidjson {

	JSONDocument::JSONDocument(std::unique_ptr<::RAPIDJSON_NAMESPACE::Document> document)
		:m_document(std::move(document))
		,m_rootValue(std::make_unique<JSONValue>(*this, *m_document, m_document->GetAllocator()))
		,m_freeValues()
	{
	}

	JSONDocument::~JSONDocument() = default;

	IJSONValue& JSONDocument::getRootValue()
	{
		return *m_rootValue;
	}

	const IJSONValue& JSONDocument::getRootValue() const
	{
		return *m_rootValue;
	}

	std::string JSONDocument::serialize(bool pretty) const
	{
		::RAPIDJSON_NAMESPACE::StringBuffer jsonBuffer;
		jsonBuffer.Clear();

		std::string serializedDocument;
		if (pretty)
		{
			::RAPIDJSON_NAMESPACE::PrettyWriter<::RAPIDJSON_NAMESPACE::StringBuffer> jsonWriter(jsonBuffer);
			jsonWriter.SetMaxDecimalPlaces(6);
			m_document->Accept(jsonWriter);
			serializedDocument = jsonBuffer.GetString();
		}
		else
		{
			::RAPIDJSON_NAMESPACE::Writer<::RAPIDJSON_NAMESPACE::StringBuffer> jsonWriter(jsonBuffer);
			jsonWriter.SetMaxDecimalPlaces(6);
			m_document->Accept(jsonWriter);
			serializedDocument = jsonBuffer.GetString();
		}

		return serializedDocument;
	}

	void JSONDocument::addFreeValue(std::unique_ptr<::RAPIDJSON_NAMESPACE::Value> value)
	{
		m_freeValues.push_back(std::move(value));
	}

	std::unique_ptr<::RAPIDJSON_NAMESPACE::Value> JSONDocument::removeFreeValue(const ::RAPIDJSON_NAMESPACE::Value& value)
	{
		std::unique_ptr<::RAPIDJSON_NAMESPACE::Value> freeValueFound;

		auto it = m_freeValues.begin();
		while (!freeValueFound && (it != m_freeValues.end()))
		{
			if (it->get() == &value)
			{
				std::unique_ptr<::RAPIDJSON_NAMESPACE::Value> foundValue;
				foundValue.swap(*it);
				m_freeValues.erase(it);
				freeValueFound = std::move(foundValue);
			}
			else
			{
				it++;
			}
		}

		return freeValueFound;
	}

}}}
