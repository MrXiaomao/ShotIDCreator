#pragma once
#include <afxsock.h>
class CShotIDCreatorDlg;

class CClientSocket : public CSocket
{
 public:
    CClientSocket(CShotIDCreatorDlg* dlg);
   virtual ~CClientSocket();
   SOCKADDR_IN ClientAddr;
private:
    CShotIDCreatorDlg* m_pMainDlg;

public:
    virtual void OnReceive(int nErrorCode);
    virtual void OnSend(int nErrorCode);
protected:
};