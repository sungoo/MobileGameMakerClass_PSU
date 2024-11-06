#include "pch.h"
#include "IocpCore.h"
#include "Session.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
    //Create Completion Port
    _iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
    ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

//Complition Port 쓰는 이유
//멀티스레드에 적합
//=> APC큐에 저장하지 않고 Complition Port에 저장하고 스레드끼리 자원 공유

IocpCore::~IocpCore()
{
}

bool IocpCore::Register(IocpObject* iocpObj)
{
    //현재 상황 : iocpObj가 Session임
    return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, reinterpret_cast<ULONG_PTR>(&iocpObj), 0);
}

bool IocpCore::Dispatch(uint32 timeOutMs)
{
    //Complition Port에 있는 함수들 실행

    DWORD numOfBytes = 0;
    IocpObject* iocpObject = nullptr;
    IocpEvent* iocpEvent = nullptr;

    if (
        ::GetQueuedCompletionStatus(
            _iocpHandle,
            &numOfBytes,
            reinterpret_cast<PULONG_PTR>(&iocpObject),
            reinterpret_cast<LPOVERLAPPED*>(iocpEvent),
            timeOutMs
        ))
    {
        iocpObject->DisPatch(iocpEvent, numOfBytes);
    }
    else
    {
        int32 errCode = ::WSAGetLastError();

        switch (errCode)
        {
        case WAIT_TIMEOUT:
            return false;
        default:
            //TODO : 왜 안됐는지 코드분석
            iocpObject->DisPatch(iocpEvent, numOfBytes);
            break;
        }
    }

    return true;
}
