#pragma once

class IocpObject
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class IocpCore
{
public:
	IocpCore();
	~IocpCore();
	
	HANDLE GetHandle() { return _iocpHandle; }

	//Complition Port에 Socket 등록
	bool Register(IocpObject* iocpObj);
	//실행 준비 후 실행
	bool Dispatch(uint32 timeOutMs = INFINITE);


private:
	HANDLE _iocpHandle;
};

