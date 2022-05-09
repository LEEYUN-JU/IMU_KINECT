#include "pch.h"
#include "MFC_Server.h"
#include "Clinet_socket.h"
#include "Client_listen.h"
#include "MFC_ServerDlg.h"

Clinet_socket::Clinet_socket()
{
}

Clinet_socket::~Clinet_socket()
{
}

// CClientSocket ��� �Լ�
void Clinet_socket::SetListenSocket(CAsyncSocket* pSocket)
{
	m_pListenSocket = pSocket;
}
// CClientSocket ��� �Լ�


void Clinet_socket::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	Client_listen* pServerSocket = (Client_listen*)m_pListenSocket;
	pServerSocket->CloseClientSocket(this);

	Clinet_socket::OnClose(nErrorCode);
}

void Clinet_socket::OnReceive(int nErrorCode)
{
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	char temp[1024];
	

	GetPeerName(strIPAddress, uPortNumber);

	if (Receive(&temp, sizeof(temp)) > 0) 
	{
		CMFCServerDlg* pMain = (CMFCServerDlg*)AfxGetMainWnd();
		
		strTmp = temp;

		pMain->message_list.InsertString(-1, strTmp);
		pMain->message_list.AddString(L"\n");  // �޽��� ����Ʈ(�޽���â?)�� �Է¹��� �޽��� ����
		pMain->message_list.SetCurSel(pMain->message_list.GetCount() - 1);
		//AfxMessageBox(strTmp);

		//send(*m_pListenSocket, temp, sizeof(temp), 0);
		Client_listen* pServerSocket = (Client_listen*)m_pListenSocket;
		//TCHAR* szUniCode = (TCHAR*)(LPCTSTR)strTmp;
		//pServerSocket->SendAllMessage(szUniCode); // �ٸ� Ŭ���̾�Ʈ�鿡�� �޽��� ����

		pServerSocket->SendAllMessage(temp); // �ٸ� Ŭ���̾�Ʈ�鿡�� �޽��� ����

	}		
	
	CSocket::OnReceive(nErrorCode);
}
