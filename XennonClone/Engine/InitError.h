#pragma once 
#include <exception>
#include <string>

class InitError : public std::exception {
public:
	InitError();
	explicit InitError(const std::string& message);  // add explicit and better parameter name
	virtual ~InitError() noexcept override;
	virtual const char* what() const noexcept override;
private:
	std::string msg_;  // add underscore for private member
};