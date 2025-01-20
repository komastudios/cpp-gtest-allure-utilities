#include "JSONMember.h"

#include "JSONValue.h"


namespace systelab { namespace json { namespace rapidjson {

	JSONMember::JSONMember(JSONDocument& document,
						   const std::string& name,
						   ::RAPIDJSON_NAMESPACE::Value& value,
						   ::RAPIDJSON_NAMESPACE::Document::AllocatorType& allocator)
		:m_name(name)
		,m_value(std::make_unique<JSONValue>(document, value, allocator))
	{
	}

	JSONMember::~JSONMember() = default;

	IJSONValue& JSONMember::getValue() const
	{
		return *m_value;
	}

}}}
