#pragma once

#include "ITestSuiteJSONSerializer.h"
#include "JSONAdapterInterface\IJSONAdapter.h"

#include <memory>
#include <vector>


namespace systelab { namespace json {
	class IJSONAdapter;
	class IJSONValue;
}}

namespace systelab { namespace gtest_allure { namespace model {
	class Action;
	class ExpectedResult;
	class Label;
	class Link;
	class Parameter;
	class TestCase;
	class TestSuite;
	enum class Status;
	enum class Stage;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class TestSuiteJSONSerializer : public ITestSuiteJSONSerializer
	{
	public:
		TestSuiteJSONSerializer(std::unique_ptr<json::IJSONAdapter>);
		~TestSuiteJSONSerializer() override;

		std::string serialize(const model::TestSuite&) const override;

	protected:
		virtual void addTestSuiteToJSON(const model::TestSuite&, json::IJSONValue&) const;
		virtual void addLabelsToJSON(const model::TestSuite&, json::IJSONValue&) const;
		virtual void addLinksToJSON(const std::vector<model::Link>&, json::IJSONValue&) const;
		virtual void addTestCasesToJSON(const std::vector<model::TestCase>&, json::IJSONValue&) const;
		virtual void addTestCaseStepsToJSON(const model::TestCase& testCase, json::IJSONValue&) const;
		virtual void addTestCaseAttachmentsToJSON(const model::TestCase& testCase, json::IJSONValue&) const;

		std::string translateStatusToString(model::Status) const;
		std::string translateStageToString(model::Stage) const;

	private:
		std::unique_ptr<json::IJSONAdapter> m_jsonAdapter;
	};

}}}
