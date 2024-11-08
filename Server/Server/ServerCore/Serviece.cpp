#include "pch.h"
#include "Serviece.h"

Serviece::Serviece(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
	: _type(type)
	, _netAddress(address)
	, _iocpCore(core)
	, _sessionFactory(factory)
	, _maxSessionCount(maxSessionCount)
{
}

Serviece::~Serviece()
{
}

void Serviece::CloseService()
{
	//TODO
}

shared_ptr<Session> Serviece::CreateSesseion()
{
	shared_ptr<Session> session = _sessionFactory();

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Serviece::AddSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void Serviece::ReleaseSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

ClientService::ClientService(NetAddress target, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
	:Serviece(ServiceType::CLIENT, target, core, factory, maxSessionCount)
{
}

ClientService::~ClientService()
{
}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	//TODO
	return true;
}

ServerService::ServerService(NetAddress target, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount)
	:Serviece(ServiceType::SERVER, target, core, factory, maxSessionCount)
{
}

ServerService::~ServerService()
{
	//TODO
}

bool ServerService::Start()
{
	if (CanStart() == false)
		return false;

	_listener = MakeShared<Listener>();
	if (_listener == nullptr)
		return false;

	shared_ptr<ServerService> service = static_pointer_cast<ServerService>(shared_from_this());
	if (_listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	Serviece::CloseService();
}
