#pragma once

namespace utils
{
	/// <summary>
	/// 取得Editor的内容
	/// </summary>
	/// <param name="pthis">pthis</param>
	/// <param name="ctl_id">对话框控件id</param>
	/// <returns>内容字符串</returns>
	extern tstring GetDialogEditorString(const CDialogEx* pthis, int ctl_id);

	/// <summary>
	/// 获取当前日期时间
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	extern std::wstring getTime(void);

	extern std::string wstring2string(const std::wstring& ws);
}

