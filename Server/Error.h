#pragma once
#include <string>

enum Status
{
	FAIL,
	SUCCESS,
	ERR_INVALID,
	ERR_EXISTS,
	ERR_SHORT,
	ERR_LONG,
	ERR_ILLEGAL,
	ERR_RESTRICTED,
	ERR_NOUSR
};

enum CommandType { NONE, UNAME, MESSAGE, PM, MKROOM, ENTER, EXIT };


inline CommandType stringToCommand(const std::string &string)
{
	if (string == "UNAME")
	{
		return UNAME;
	}
	if (string == "MESSAGE")
	{
		return MESSAGE;
	}
	if(string == "PM")
	{
		return PM;
	}
	if(string == "MKROOM")
	{
		return MKROOM;
	}
	if(string == "ENTER")
	{
		return ENTER;
	}
	if(string == "EXIT")
	{
		return EXIT;
	}
	return NONE;
}

inline std::string statusToString(const Status &status)
{
	switch(status)
	{
		case SUCCESS:
			return "SUCCESS";
		case ERR_INVALID:
			return "ERR_INVALID";
		case ERR_EXISTS:
			return "ERR_EXISTS";
		case ERR_SHORT:
			return "ERR_SHORT";
		case ERR_LONG:
			return "ERR_LONG";
		case ERR_ILLEGAL:
			return "ERR_ILLEGAL";
		case ERR_RESTRICTED:
			return "ERR_RESTRICTED";
		case ERR_NOUSR:
			return "ERR_NOUSR";
		default:
			return "FAIL";
	}
}

inline std::string getError(const Status &status)
{
	switch (status)
	{
		case ERR_EXISTS:
			return "Username already in use";
		case ERR_SHORT:
			return "Username too short";
		case ERR_LONG:
			return "Username too long";
		case ERR_ILLEGAL:
			return "Username contains illegal characters";
		case ERR_RESTRICTED:
			return "Username contains restricted word";
		case ERR_NOUSR:
			return "Specified user does not exist";
		default:
			return "Unknown";
	}
}