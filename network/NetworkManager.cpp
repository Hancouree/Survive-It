#include "NetworkManager.h"
#include <iostream>

NetworkManager::NetworkManager()
	: m_socket(m_context, { udp::v4(), 0 })
	, m_workGuard(asio::make_work_guard(m_context))
	, m_heartbeatTimer(m_context)
	, m_connected(false)
{
	m_handlers[PACKET_CONNECT] = [this](size_t) { onConnect(); };
	m_handlers[PACKET_STATE] = [this](size_t bytes) { onState(bytes); };

	m_thread = std::thread([this]() { m_context.run(); });
}

NetworkManager::~NetworkManager()
{
	m_workGuard.reset();
	m_context.stop();
	if (m_thread.joinable()) m_thread.join();
}

void NetworkManager::doReceive()
{
	auto endpoint = std::make_shared<udp::endpoint>();
	m_socket.async_receive_from(asio::buffer(m_buffer), *endpoint,
		[this, endpoint](boost::system::error_code ec, size_t bytesReceived) {
			//std::cout << "Received bytes: " << bytesReceived << '\n';
			if (!ec && bytesReceived > 0) {
				uint8_t type = m_buffer[0];
				if (auto it = m_handlers.find(type); it != m_handlers.end())
					it->second(bytesReceived);
			}

			doReceive();
		});
}

void NetworkManager::connect(const std::string& host, short port)
{
	m_serverEndpoint = udp::endpoint(asio::ip::make_address(host), port);
	send({ PACKET_CONNECT });
	doReceive();
	doHeartbeat();
}

void NetworkManager::sendInput(const InputPacket& packet)
{
	std::vector<uint8_t> data;

	auto appendFloat = [&](float v) {
		uint8_t* b = reinterpret_cast<uint8_t*>(&v);
		data.insert(data.end(), b, b + 4);
	};

	data.push_back(packet.type);
	data.push_back(packet.moveDir);
	appendFloat(packet.aimAngle);
	data.push_back(packet.shooting);
	send(data);
}

void NetworkManager::send(const std::vector<uint8_t>& data)
{
	auto buf = std::make_shared<std::vector<uint8_t>>(data);
	m_socket.async_send_to(asio::buffer(*buf), m_serverEndpoint,
		[buf](boost::system::error_code ec, size_t bytesReceived) {});
}

void NetworkManager::doHeartbeat()
{
	m_heartbeatTimer.expires_after(std::chrono::seconds(HEARTBEAT_INTERVAL));
	m_heartbeatTimer.async_wait([this](boost::system::error_code ec) {
		if (ec) return;
		if (m_connected) send({ PACKET_HEARTBEAT });
		doHeartbeat();
	});
}

void NetworkManager::onConnect()
{
	m_connected = true;
	uint8_t uidSize = m_buffer[1];
	std::string uid(m_buffer.begin() + 2, m_buffer.begin() + 2 + uidSize);
	std::cout << "NETWORK: RECEIVED UID: " << uid << "\n";
	if (!m_connectionCallbacks.empty()) {
		for (auto& callback : m_connectionCallbacks) {
			callback(uid);
		}
	}
}

void NetworkManager::onState(size_t bytesReceived)
{
	std::lock_guard<std::mutex> locker(m_mtx);
	m_storedStates.push({ m_buffer.begin(), m_buffer.begin() + bytesReceived });
}

void NetworkManager::onConnected(std::function<void(std::string)> callback)
{
	m_connectionCallbacks.push_back(std::move(callback));
}

std::vector<uint8_t> NetworkManager::pollState()
{
	std::lock_guard<std::mutex> locker(m_mtx);
	if (m_storedStates.empty()) return {};
	auto state = std::move(m_storedStates.front());
	m_storedStates.pop();
	return state;
}

