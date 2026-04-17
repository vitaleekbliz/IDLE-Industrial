#pragma once

namespace Engine
{
	class BitEngine
	{
	public:
		static BitEngine& Get();

		void Init();
		void Close();

	private:
		BitEngine();
		~BitEngine();
	};
} // namespace Engine