#pragma once

namespace utils
{
	/// <summary>
	/// ȡ��Editor������
	/// </summary>
	/// <param name="pthis">pthis</param>
	/// <param name="ctl_id">�Ի���ؼ�id</param>
	/// <returns>�����ַ���</returns>
	extern tstring GetDialogEditorString(const CDialogEx* pthis, int ctl_id);

	/// <summary>
	/// ��ȡ��ǰ����ʱ��
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	extern std::wstring getTime(void);

	extern std::string wstring2string(const std::wstring& ws);
}

