#include "NetworkManager.h"
#include <iostream>

NetworkManager::NetworkManager()
	: m_socket(m_context, { udp::v4(), 0 })
	, m_workGuard(asio::make_work_guard(m_context))
{
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
			std::cout << "Received bytes: " << bytesReceived << '\n';
			if (!ec && bytesReceived > 0) {
				uint8_t type = m_buffer[0];
				if (type == 0x00 && m_onConnected) 
					m_onConnected();
			}

			doReceive();
		});
}

void NetworkManager::connect(const std::string& host, short port)
{
	m_serverEndpoint = udp::endpoint(asio::ip::make_address(host), port);
	uint8_t data[1] = { 0x00 };
	send({ data, data + 1 });
	doReceive();
}

void NetworkManager::send(const std::vector<uint8_t>& data)
{
	auto buf = std::make_shared<std::vector<uint8_t>>(data);
	m_socket.async_send_to(asio::buffer(*buf), m_serverEndpoint,
		[this, buf](boost::system::error_code ec, size_t bytesReceived) {});
}

void NetworkManager::onConnected(std::function<void()> onConnected)
{
	m_onConnected = std::move(onConnected);
}

