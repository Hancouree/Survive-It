#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <functional>
#include <array>

namespace asio = boost::asio;
using udp = asio::ip::udp;

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void connect(const std::string& host, short port);
	void send(const std::vector<uint8_t>& data);
	void onConnected(std::function<void()> onConnected);
private:
	void doReceive();

	asio::io_context m_context;
	udp::socket m_socket;
	udp::endpoint m_serverEndpoint;
	std::array<uint8_t, 512> m_buffer;
	asio::executor_work_guard<asio::io_context::executor_type> m_workGuard;
	std::thread m_thread;
	std::function<void()> m_onConnected;
};

