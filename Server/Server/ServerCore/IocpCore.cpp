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
    ::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(shared_ptr<IocpObject> iocpObj)
{
    //현재 상황 : iocpObj가 Session임
    // 
    // Session을 Event에서 물고있도록..
    // => iocpEvent에서 현재 내 세션을 멤버변수로 갖고있겠다.
    // ==> 세션 refCount + 1
    //                   or Listener                                  Key
    return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(uint32 timeOutMs)
{
    //Complition Port에 있는 함수들 실행

    DWORD numOfBytes = 0;
    ULONG_PTR key = 0;
    shared_ptr<IocpObject> iocpObject = nullptr;
    IocpEvent* iocpEvent = nullptr;

    if (
        ::GetQueuedCompletionStatus(
            _iocpHandle,
            &numOfBytes,
            &key,//key
            reinterpret_cast<LPOVERLAPPED*>(&iocpEvent),
            timeOutMs
        ))
    {
        iocpEvent->GetOwner()->DisPatch(iocpEvent, numOfBytes);
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
