#include "FSM.h"

FSM::FSM() : m_state(CONNECTING)
{
    m_transitions = {
        { CONNECTING, {
            { CONNECTED, MENU }
        }},
        { MENU, {
            { START_GAME, IN_GAME },
            { DISCONNECTED, CONNECTING }
        }}
    };
}

void FSM::applyEvent(Events e)
{
    if (m_transitions[m_state].contains(e)) { m_state = m_transitions[m_state][e]; }
}

FSM::States FSM::getState() const noexcept
{
    return m_state;
}
