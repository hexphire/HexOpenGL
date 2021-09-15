#pragma once

#include <functional>

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test(){}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

	};

	class TestMenu : public Test
	{
	public:
		TestMenu() {}
		~TestMenu() {}

		virtual void OnUpdate(float deltaTime) override;
	private:
		Test* m_currentTest;
		std::vector <std::pair<std::string, std::is_function<Test* ()>>> m_Tests;

	};
}