#pragma once

#include "../Integrian2D_API.h"
#include "Event/Event.h"

namespace Integrian2D
{
	class IListener;

	class EventQueue final
	{
	public:
		static EventQueue* const GetInstance() noexcept;
		static void Cleanup() noexcept;

		INTEGRIAN2D_API ~EventQueue();

		/* Queue an event to the EventQueue, this EventQueue operates on a principle of FIFO (First In, First Out) */
		INTEGRIAN2D_API void QueueEvent(const Event& event) noexcept;

		/* This function gets called interally and should NOT get called manually 
		   All events that were added before Update() gets called get executed, or their timer gets increased by 1
		   See Event for documentation regarding the event timer */
		void Update() noexcept;

		/* Add a Listener class that should receive events from the EventQueue */
		INTEGRIAN2D_API void AddListener(IListener* const pListener) noexcept;

		/* Remove a Listener class from the EventQueue */
		INTEGRIAN2D_API void RemoveListener(IListener* const pListener) noexcept;

		/* Check if all events have been processed */
		INTEGRIAN2D_API bool AreAllEventsProcessed() const noexcept;

	private:
		friend class Scene;

		class EventQueueImpl;

		EventQueue();

		inline static EventQueue* m_pInstance{};
		EventQueueImpl* m_pEventQueueImpl;
	};
}
