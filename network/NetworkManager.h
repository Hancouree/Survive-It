#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <functional>
#include <array>
#include <queue>
#include <mutex>

namespace asio = boost::asio;
using udp = asio::ip::udp;

constexpr uint8_t PACKET_CONNECT = 0x00;
constexpr uint8_t PACKET_INPUT = 0x01;
constexpr uint8_t PACKET_STATE = 0x02;
constexpr uint8_t PACKET_HEARTBEAT = 0x03;

constexpr int HEARTBEAT_INTERVAL = 2;

struct InputPacket {
	uint8_t type;
	uint8_t moveDir;
	float aimAngle;
	bool shooting;
};

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void connect(const std::string& host, short port);
	void sendInput(const InputPacket& packet);
	void onConnected(std::function<void(std::string)> onConnected);
	std::vector<uint8_t> pollState();
private:
	void send(const std::vector<uint8_t>& data);
	void doReceive();
	void doHeartbeat();

	//handlers
	void onConnect();
	void onState(size_t bytesReceived);

	asio::io_context m_context;
	udp::socket m_socket;
	udp::endpoint m_serverEndpoint;
	std::array<uint8_t, 512> m_buffer;
	asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;
	std::thread m_thread;
	asio::steady_timer m_heartbeatTimer;
	bool m_connected;
	std::mutex m_mtx;

	std::unordered_map<uint8_t, std::function<void(size_t)>> m_handlers;
	std::vector<std::function<void(std::string)>> m_connectionCallbacks;
	std::queue<std::vector<uint8_t>> m_storedStates;
};

