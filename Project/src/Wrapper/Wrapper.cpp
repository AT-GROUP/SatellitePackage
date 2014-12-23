#include "Wrapper.h"
//#include <msclr/auto_gcroot.h>

#ifdef WRAPPER_LIB

template<class T> msclr::auto_gcroot<T^>& ManagedHolder<T>::object()
{
	return m_pObject;
}

#endif

Wrapper::Wrapper()
{
	createManagedInstances();
}

Wrapper::~Wrapper()
{
	
}

void Wrapper::createManagedInstances()
{
	//pATReasonerHolder = new ManagedHolder<SolverXLib::SolverX>();
    //pTemporalReasonerHolder = new ManagedHolder<MProgram::TemporalReasonerX>();
    //pIMHolder = new ManagedHolder<ModelLib::Model>();
}

void Wrapper::configurate()
{
    //pIMHolder->m_pObject->configurate();
    //pTemporalReasonerHolder->m_pObject->Configurate(1);
	//pATReasonerHolder->m_pObject->Configurate(s_sendingMessage);
}
void Wrapper::processModelTact()
{
	const std::string senderName = "Wrapper";
	const std::string sendingMessage = "aaa";
    //pIMHolder->m_pObject->processNextTact(s_sendingMessage);
}
void Wrapper::processSolversTact()
{

}

