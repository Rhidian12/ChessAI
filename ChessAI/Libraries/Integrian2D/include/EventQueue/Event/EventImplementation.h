#pragma once

#include <string>
#include <memory>

namespace Integrian2D
{
	class IEventData
	{
	public:
		virtual ~IEventData() = default;
	};

	template<typename Type>
	class EventData final : public IEventData
	{
	public:
		EventData(const Type& data)
			: m_Data{ data }
		{}

		const Type& GetData() const noexcept
		{
			return m_Data;
		}

	private:
		Type m_Data;
	};

	class EventImplementation final
	{
	public:
		EventImplementation(const std::string& eventName)
			: m_Event{ eventName }
			, m_pData{}
		{}

		template<typename Type>
		EventImplementation(const std::string& eventName, const Type& data)
			: m_Event{ eventName }
			, m_pData{ new EventData<Type>{data} }
		{}

		const std::string& GetEvent() const noexcept;

		template<typename Type>
		const Type& GetData() const noexcept
		{
			return std::static_pointer_cast<EventData<Type>>(m_pData)->GetData();
		}

	private:
		std::string m_Event;
		std::shared_ptr<IEventData> m_pData;
	};
}