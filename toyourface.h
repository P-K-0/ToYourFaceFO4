#pragma once

#include "PCH.h"

namespace ToYourFace {

	static const auto Pi = static_cast<float>(std::acos(-1));
	static const auto Pi2 = 2.0f * Pi;

	static REL::Relocation<float*> fAIMinGreetingDistance{ REL::ID(855965) };

	struct GetDistanceSqFromReference{

		static inline float distance{};
		static inline float deviation{};

		static float thunk(RE::TESObjectREFR* player, RE::TESObjectREFR* actor, std::uint32_t unk2, std::uint32_t unk3, std::uint32_t unk4)
		{
			auto ret = func(player, actor, unk2, unk3, unk4);

			if (!player || !actor)
				return ret;

			auto dx = actor->data.location.x - player->data.location.x;
			auto dy = actor->data.location.y - player->data.location.y;

			auto angle = std::atan2(dx, dy);

			if (angle < 0.0f)
				angle += Pi2;

			auto dev = std::abs(angle - player->data.angle.z);

			if (dev > Pi)
				dev = Pi2 - dev;

			return dev < deviation ? ret : distance;
		}

		static inline REL::Relocation<decltype(thunk)> func;
		static inline std::ptrdiff_t offset{ 0x3d2 };
		static inline REL::ID id{ 415818 };
	};

	template<typename T, std::size_t N>
	void write_call()
	{
		auto& trampoline = F4SE::GetTrampoline();

		REL::Relocation<std::uintptr_t> fn{ T::id, T::offset };

		T::func = trampoline.write_call<N>(fn.address(), T::thunk);
	}

	[[nodiscard]] auto GetRadMaxDeviationAngle(float angle) noexcept
	{
		return (angle / 180.0f * Pi);
	}

	void Install() noexcept
	{
		static bool installed{};

		if (installed)
			return;

		F4SE::AllocTrampoline(1024);

		auto& settings = Settings::Manager::GetSingleton();

		(*fAIMinGreetingDistance) = settings.GetAIMinGreetingDistance();

		GetDistanceSqFromReference::deviation = GetRadMaxDeviationAngle(settings.GetMaxDeviationAngle());
		GetDistanceSqFromReference::distance = std::powf(settings.GetAIMinGreetingDistance(), 2.0f) + 1.0f;

		write_call<GetDistanceSqFromReference, 5>();
		
		installed = true;
	}
}