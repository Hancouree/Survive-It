#pragma once
#include <unordered_map>

class FSM
{
public:
	enum States
	{
		CONNECTING,
		MENU,
		IN_GAME,
	};

	enum Events {
		CONNECTED,
		DISCONNECTED,
		START_GAME,
	};

	FSM();
	void applyEvent(Events e);
	States getState() const noexcept;
private:
	States m_state;
	std::unordered_map<States, std::unordered_map<Events, States>> m_transitions;
};

