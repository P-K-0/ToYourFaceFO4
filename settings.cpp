
#include "settings.h"

namespace Settings {

	void Manager::Read() noexcept
	{
		CSimpleIni ini;

		ini.SetUnicode();
		auto error = ini.LoadFile(IniFile);

		if (error != SI_OK) {

			ini.LoadData(
				"[Main]\n\n"
				"fMaxDeviationAngle = 30\n"
				"fAIMinGreetingDistance = 175\n"
			);

			ini.SaveFile(IniFile);
		}

		fAIMinGreetingDistance = std::stof(ini.GetValue("Main", "fAIMinGreetingDistance", std::to_string(175.0f).c_str()));
		fMaxDeviationAngle = std::stof(ini.GetValue("Main", "fMaxDeviationAngle", std::to_string(30.0f).c_str()));
	}
}