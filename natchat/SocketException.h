#pragma once
#include <exception>
#include <string>

namespace inner_network
{
	/// <summary>
	/// ���й���socket���쳣��
	/// </summary>
	class SocketException : std::exception
	{
		std::string message;
	public:
		SocketException(const std::string& msg = "Socket error")
			:message(msg) {}
		~SocketException() {}

		const char* what() const noexcept override
		{
			return message.c_str();
		}
	};

}