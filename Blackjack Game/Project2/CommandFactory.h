#pragma once
#include "stdafx.h"

class Command;

class CommandFactory {
private:
	CommandFactory() {} //싱글톤 패턴을 위하여 private에 선언
	
public:
	~CommandFactory(); //instance 메모리 반환을 위한 소멸자

	Command* getCommand(int id, void* inform = NULL) const; //id에 맞는 커맨드를 생성하고 반환함. 필요할 경우 inform의 정보를 인자로 전달
	static CommandFactory* getInstace(); //싱글턴패턴이므로 CommandFactory의 인스턴스를 받기 위한 static함수
	static void setReplay(bool flag);

private:
	static CommandFactory* instance;//
	static bool isReplay;
};
