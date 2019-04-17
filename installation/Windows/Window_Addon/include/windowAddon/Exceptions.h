#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

///@brief Custom class that inherits from @a std::exception used as the base for all the exceptions of this library.
class CustomException : public std::exception {
public:
	CustomException() {}
	virtual ~CustomException() throw() {}
	CustomException(const std::string & message) {
		this->message = message;
	}

	virtual const char * what() const throw() {
		return message.c_str();
	}

protected:
	std::string message;
};

//Inheritance and c++98 are wonderful together!

///@brief Exception produced by an Allegro error.
class AllegroException : public CustomException {
public:
	AllegroException() {}
	virtual ~AllegroException() throw() {}
	AllegroException(const std::string & message) {
		this->message = "Allegro Exception: " + message;
	}
};

///@brief Exception produced by an Window error such as trying to use an invalid Font.
class WindowException : public CustomException {
public:
	WindowException() {}
	virtual ~WindowException() throw() {}
	WindowException(const std::string & message) {
		this->message = "Window Exception: " + message;
	}
};

///@brief Exception produced by a Turtle error such as trying to use a Turtle that isn't on the Turtle list.
class TurtleException : public CustomException {
public:
	TurtleException() {}
	virtual ~TurtleException() throw() {}
	TurtleException(const std::string & message) {
		this->message = "Turtle Exception: " + message;
	}
};


#endif
