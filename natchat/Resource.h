//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ ���ɵİ����ļ���
// �� natchat.rc ʹ��
//

#define IDM_ABOUTBOX                    0x0010
#define IDD_ABOUTBOX                    100
#define IDS_ABOUTBOX                    101
#define IDD_NATCHAT_DIALOG              102
#define IDP_SOCKETS_INIT_FAILED         103
#define IDR_MAINFRAME                   128
#define IDD_SENDBOX                     130
#define IDD_REFRESH                     132
#define IDC_RECRIVERHOST                1012
#define IDC_IPLIST                      1013
#define IDC_RECEIVERTEXT                1014
#define IDC_RECEIVERTEXT2               1015
#define IDC_RECRIVERIP                  1016
#define IDC_FILETEXT                    1017
#define IDC_EDIT1                       1018
#define IDC_EDIT2                       1019
#define IDC_SENDFILE                    1023
#define IDC_SELECTEDFILE                1024
#define IDC_STATUS                      1025
#define IDC_CHOOSEFILE                  1026
#define IDC_SENDPRIVATE                 1027
#define IDC_CANCEL                      1028
#define IDC_PRIVATEEDIT                 1029
#define IDC_REFRESH                     1030
#define IDC_PRIVATETEXT                 1031
#define IDC_REFRESHING                  1032
#define IDC_SENDANI                     1033
#define IDC_EMOTIONANI                  1034
#define IDC_STATUSTEXT                  1022

/// <summary>
/// ����ļ�����
/// </summary>
#define WM_SEND_FILE_DONE				1101
/// <summary>
/// �ļ�����ʧ��
/// </summary>
#define WM_SEND_FILE_ERROR				1102
/// <summary>
/// ��Ϣ����ʧ��
/// </summary>
#define WM_SEND_MESSAGE_ERROR			1103
/// <summary>
/// ��Ϣ����ʧ��
/// </summary>
#define WM_RECEIVE_MESSAGE_ERROR       1104
/// <summary>
/// �ڽ��յ�������Ⱥ����Ϣ��ʱ�򴥷��������ȡ history �б�ˢ��
/// </summary>
#define WM_RECOMMEND_REFRESH_HISTORIES 1105
/// <summary>
/// �յ���һ���ļ�ʱ���ʹ���Ϣ��ͨ�� LPARAM ����һ�� wchar_t* ��Ϊ�ļ�����
/// ���޸��� g_wsSaveFilePath ֮�󣨴�������Ϣ���������Զ������ˡ�
/// </summary>
#define WM_RECEIVE_FILE					1106
/// <summary>
/// ���յ� TIC ��ʱ�򴥷�������ˢ�� User �б�
/// </summary>
#define WM_RECEIVE_TIC					1111
/// <summary>
/// ���յ� TOC ��ʱ�򴥷������Բ�������ˢ�µļ����ӽ���֮��ͳһˢ�� User �б�
/// </summary>
#define WM_RECEIVE_TOC					1112
/// <summary>
/// �㲥 TIC ʧ�ܡ�˵�����ˢ�°�ť֮��Ĳ���ʧ���ˣ���ʱ��Ӧ��ֹͣ�����ڵ�ˢ��״̬
/// </summary>
#define WM_BROADCAST_TIC_ERROR			1113
/// <summary>
/// ���� TIC �Ĺ���ʧ���ˣ����Բ�����
/// </summary>
#define WM_RECEIVE_TIC_ERROR			1114

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        135
#define _APS_NEXT_COMMAND_VALUE         32771
#define _APS_NEXT_CONTROL_VALUE         1034
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
