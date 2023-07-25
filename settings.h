#pragma once

#include "PCH.h"

namespace Settings {

	constexpr auto IniFile = "Data\\F4SE\\Plugins\\ToYourFaceFO4.ini";

	class Manager {

	public:

		[[nodiscard]] static Manager& GetSingleton() noexcept 
		{
			static Manager instance;
			return instance;
		}

		void Read() noexcept;

		[[nodiscard]] const auto& GetMaxDeviationAngle() const noexcept { return fMaxDeviationAngle; }
		[[nodiscard]] const auto& GetAIMinGreetingDistance() const noexcept { return fAIMinGreetingDistance; }

	private:

		Manager() = default;
		~Manager() = default;

		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;

		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;

		float fMaxDeviationAngle{ 30.0f };
		float fAIMinGreetingDistance{ 175.0f };
	};
}