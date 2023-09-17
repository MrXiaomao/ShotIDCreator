
#include "pch.h"
#include "CClientSocket.h"
#include "ShotIDCreatorDlg.h"


CClientSocket::CClientSocket(CShotIDCreatorDlg* dlg)
{
	this->m_pMainDlg = dlg;
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{	
	//接受函数信息
	CSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnSend(int nErrorCode)
{
	const int Len = 30;
	char m_dataToSend[Len] = { 0 };
	//sendto(m_dataToSend, 30, 12100, (SOCKADDR*)&ClientAddr, 0);
	// m_pSocket->SendTo(m_dataToSend, m_dataToSend.GetLength(),  m_peerPortNum, m_strPeerIPaddr);
	//发送函数信息
	CSocket::OnSend(nErrorCode);
}