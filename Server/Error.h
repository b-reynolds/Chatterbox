#pragma once
#include <string>

enum class CmdStatus
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

enum class CmdType
{
	NONE,
	UNAME,
	MESSAGE,
	PM,
	MKROOM,
	ENTER,
	EXIT
};

inline CmdType stringToCommand(const std::string &string)
{
	if (string == "UNAME")
	{
		return CmdType::UNAME;
	}
	if (string == "MESSAGE")
	{
		return CmdType::MESSAGE;
	}
	if(string == "PM")
	{
		return CmdType::PM;
	}
	if(string == "MKROOM")
	{
		return CmdType::MKROOM;
	}
	if(string == "ENTER")
	{
		return CmdType::ENTER;
	}
	if(string == "EXIT")
	{
		return CmdType::EXIT;
	}
	return CmdType::NONE;
}

inline std::string statusToString(const CmdStatus &status)
{
	switch(status)
	{
		case CmdStatus::SUCCESS:
			return "SUCCESS";
		case CmdStatus::ERR_INVALID:
			return "ERR_INVALID";
		case CmdStatus::ERR_EXISTS:
			return "ERR_EXISTS";
		case CmdStatus::ERR_SHORT:
			return "ERR_SHORT";
		case CmdStatus::ERR_LONG:
			return "ERR_LONG";
		case CmdStatus::ERR_ILLEGAL:
			return "ERR_ILLEGAL";
		case CmdStatus::ERR_RESTRICTED:
			return "ERR_RESTRICTED";
		case CmdStatus::ERR_NOUSR:
			return "ERR_NOUSR";
		default:
			return "FAIL";
	}
}

inline std::string getError(const CmdStatus &status)
{
	switch (status)
	{
		case CmdStatus::ERR_EXISTS:
			return "Username already in use";
		case CmdStatus::ERR_SHORT:
			return "Username too short";
		case CmdStatus::ERR_LONG:
			return "Username too long";
		case CmdStatus::ERR_ILLEGAL:
			return "Username contains illegal characters";
		case CmdStatus::ERR_RESTRICTED:
			return "Username contains restricted word";
		case CmdStatus::ERR_NOUSR:
			return "Specified user does not exist";
		default:
			return "Unknown";
	}
}